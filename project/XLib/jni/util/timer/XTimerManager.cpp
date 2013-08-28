#include "XTimerManager.h"
#include "XDateTime.h"
#include "XLog.h"
#include "XTimer.h"

#ifndef INFINITE 
#define INFINITE 0xffffffffL
#endif

bool XTimerRequest::operator == (const XTimerRequest& req) const
{
	int ret = subtimespec((timespec*)&timeout_tick, (timespec*)&req.timeout_tick);
	
	if (0 == ret)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XTimerRequest::operator < (const XTimerRequest& req) const
{
	int ret = subtimespec((timespec*)&timeout_tick, (timespec*)&req.timeout_tick);
	if (ret < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XTimerRequest::operator <= (const XTimerRequest& req) const
{
	if ((*this < req) || (*this == req))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XTimerRequest::operator > (const XTimerRequest& req) const
{
	int ret = subtimespec((timespec*)&timeout_tick, (timespec*)&req.timeout_tick);;
	if (ret > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XTimerRequest::operator >= (const XTimerRequest& req) const
{
	if ((*this > req) || (*this == req))
	{
		return true;
	}
	else
	{
		return false;
	}
}

XTimerManager::XTimerManager()
{
	int ret = 0;
	ret = pthread_mutex_init(&mutex, NULL);
	if (0 != ret)
	{
		LOGE("thread mutex init failed %d\n", ret);
	}
	ret = pthread_cond_init(&m_cond, NULL);
	if (0 != ret)
	{
		LOGE("thread cond init failed %d\n", ret);
	}
	m_dNextid		= 0;
	memset(timer_table, 0, NTIMER_MAX_NUM);
	need_sanity_reply = false;
	m_bQuitflg = false;
	m_bSignalflg = false;

	StartThread("TimerManager Thread");
}

XTimerManager::~XTimerManager()
{
	if (0 == m_tid) return;
	m_bQuitflg = true;
	int ret = pthread_cond_signal(&m_cond);
	ret = pthread_join(m_tid, NULL);
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}

int XTimerManager::NextID()
{
	for (int i = 0; i < NTIMER_MAX_NUM; i++)
	{
		m_dNextid++;
		m_dNextid %= NTIMER_MAX_NUM;
		if (m_dNextid != 0 && timer_table[m_dNextid] == 0)
		{
			return m_dNextid;
		}
	}
	return 0;
}

void XTimerManager::Notify()
{
	pthread_mutex_lock(&m_mutex);
	m_bSignalflg = true;
	int ret;
	ret = pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
}

int XTimerManager::Run()
{
	int ret = 0;
	XTimerRequest*	tmp_req = NULL;
	XTimerRequest	current_time;
	int			sleep_time = INFINITE;
	while (!CheckQuit())
	{
		pthread_mutex_lock(&m_mutex);
		if (m_bSignalflg == false)
		{
			if (INFINITE != sleep_time && sleep_time != 0)
			{
#if defined (_FOR_ANDROID_)
				struct timespec abstime;
				XTime::GetTimeSpec(&abstime, sleep_time);
				ret = pthread_cond_timedwait(&m_cond, &m_mutex, &abstime);
#elif defined _FOR_IPHONE_
				struct timespec nptime;
				nptime.tv_sec = sleep_time/1000;
				nptime.tv_nsec = sleep_time%1000*1000000;
				ret = pthread_cond_timedwait_relative_np(&m_cond, &m_mutex, &nptime);
#else
#endif
			}
			else
			{
				ret = pthread_cond_wait(&m_cond, &m_mutex);
			}
		}
		m_bSignalflg = false;
		pthread_mutex_unlock(&m_mutex);

		SyncStart();

		if (m_cReqList.size())
		{
			while ((tmp_req = m_cReqList.front()))
			{
				gettimespec(&current_time.timeout_tick, 0);

				if (*tmp_req <= current_time)
				{
					if (!(tmp_req->timer->m_bIterate && tmp_req->timer->signal))
					{

						tmp_req->timer->signal = 1;

						unsigned long *ptr = new unsigned long[2];
						ptr[0] = tmp_req->timer->m_dTimerid;
						ptr[1] = (unsigned long)tmp_req->timer;
						((XThread*)(tmp_req->pthread))->NotifyMsg((void*)ptr);
					}
					if (tmp_req->timer->m_bIterate)
					{
						gettimespec(&tmp_req->timeout_tick, tmp_req->timer->msec);
						AddRequest(tmp_req);
					}

					sleep_time = INFINITE;
				}
				else
				{
					m_cReqList.push_back(tmp_req);
					sleep_time = subtimespec(&tmp_req->timeout_tick, &current_time.timeout_tick)+1;
					break;
				}
			}
		}
		else
		{
			sleep_time = INFINITE;
		}
		
		SyncEnd();
	}
}

void XTimerManager::AddRequest(XTimerRequest* new_req)
{
	int pos;
	XTimerRequest* tmp_req = NULL;
	list<XTimerRequest*>::iterator iter = m_cReqList.begin();

	for(; iter != m_cReqList.end(); ++iter)
	{
		tmp_req = *iter;
		if(*new_req < *tmp_req)
			break;
	}

	iter = m_cReqList.insert(iter, new_req);
	if(iter == m_cReqList.begin())
	{
		Notify();
	}
}

void XTimerManager::RemoveRequest(int id)
{
	XTimerRequest* tmp_req = NULL;
	list<XTimerRequest*>::iterator iter = m_cReqList.begin();

	for(; iter != m_cReqList.end(); ++iter)
	{
		tmp_req = *iter;
		if(tmp_req->timer->m_dTimerid == id)
		{
			m_cReqList.erase(iter);
			break;
		}
	}

}

bool XTimerManager::RegisterTimer(XTimer* timer)
{
	SyncStart();
	
	gettimespec(&timer->m_pRequest->timeout_tick, timer->msec);
	timer->m_pRequest->pthread = this;
	timer->m_dTimerid = NextID();
	
	bool ret = (timer->m_dTimerid != 0);
	
	if (ret == true)
	{
		timer_table[timer->m_dTimerid] = 1;
		AddRequest(timer->m_pRequest);
	}
	SyncEnd();
	
	return ret;
}

void XTimerManager::RemoveTimer(XTimer* timer)
{
	SyncStart();

	timer_table[timer->m_dTimerid] = 0;
	RemoveRequest(timer->m_dTimerid);
	timer->m_dTimerid = 0;

	SyncEnd();
}

bool XTimerManager::IsValid(int id)
{
	if (id <= 0 || id >= NTIMER_MAX_NUM)
	{
		return false;
	}
	else
	{
		return timer_table[id];
	}
}

void XTimerManager::SetInvalid(int id)
{
	if (id > 0 && id < NTIMER_MAX_NUM)
	{
		timer_table[id] = 0;
	}
}

bool XTimerManager::RequestSanity()
{
	SyncStart();
	need_sanity_reply = true;
	SyncEnd();
	int ret;
	ret = pthread_cond_signal(&m_cond);
	return false;
}

void gettimespec(struct timespec *time,  int msec)
{
#if defined(_FOR_IPHONE_)
	struct timeval now;
	gettimeofday(&now, NULL);
	time->tv_sec = now.tv_sec + msec/1000;
	time->tv_nsec = now.tv_usec*1000 + (msec%1000)*1000000;
#else
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	time->tv_sec = now.tv_sec + msec/1000;
	time->tv_nsec = now.tv_nsec + (msec%1000)*1000000;
#endif
}

void settimespec(struct timespec *time,  int msec)
{
	time->tv_sec += msec/1000;
	time->tv_nsec += (msec%1000)*1000000;
}

int subtimespec(struct timespec *time1, struct timespec *time2)
{
	int ms = time1->tv_sec*1000 + time1->tv_nsec/1000000 -
		(time2->tv_sec*1000 + time2->tv_nsec/1000000);

	return ms;
}

