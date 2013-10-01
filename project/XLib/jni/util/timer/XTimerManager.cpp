#include "XTimerManager.h"
#include "XDateTime.h"
#include "XLog.h"
#include "XTimer.h"

#ifndef INFINITE 
#define INFINITE 0xffffffffL
#endif

XTimerManager::XTimerManager()
{
}

XTimerManager::~XTimerManager()
{
}

void XTimerManager::Run()
{
    while (!m_bQuit) {
        m_cMutex.Lock();
        bool bEmpty = m_cReqList.empty();
        m_cMutex.Unlock();
        if (bEmpty) {
            Wait();
        }
        //TODO:
    }
}

void XTimerManager::RegisterTimer(XTimer* timer)
{
    if (timer == NULL) {
        return;
    }
    m_cMutex.Lock();
    timer->m_id = NextID();
    m_cReqList.push_back(timer);
    m_cMutex.Unlock();
}

void XTimerManager::RemoveTimer(XTimer* timer)
{
    if (timer == NULL) {
        return;
    }
    m_cMutex.Lock();
    list<XTimer*>::iterator it = m_cReqList.begin();
    for (; it != m_cReqList.end(); ++it) {
        XTimer *pT = *it;
        if (timer == pT) {
            m_cReqList.erase(it);
            break;
        }
    }
    m_cMutex.Unlock();
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

