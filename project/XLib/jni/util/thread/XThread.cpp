#include "XThread.h"
#include "XLog.h"
#include "XDateTime.h"
#include "XTimer.h"
#include <string.h>
#ifdef _FOR_ANDROID_
#include "jni.h"
#include "XJniMgr.h"
#endif

XThread::XThread()
{
	m_tid = NULL;
	m_bSignalFlg = false;
    m_bQuitFlg = false;

	int ret = pthread_attr_init(&m_attr);
	ret = pthread_attr_setstacksize(&m_attr, 64*1024);
	
	if (0 != ret)
	{
		LOGE("thread m_attr stacksize init failed %d\n", ret);
	}

	ret = pthread_mutex_init(&m_mutex, NULL);
	if (0 != ret)
	{
		LOGE("thread m_mutex init failed %d\n", ret);
	}

	ret = pthread_cond_init(&m_cond, NULL);
	if (0 != ret)
	{
		//AIL_PRintF(("thread m_cond init failed %d\n", ret));
	}
}
   
XThread::~XThread()
{

}
   
void 
XThread::StartThread(const char *name)
{
	if (m_tid) return;

	if (name == NULL)
	{
		name = "Unknown Thread";
	}

	strncpy(m_szThreadName, name, THREAD_INFO_NAME_LEN);
	m_szThreadName[THREAD_INFO_NAME_LEN - 1] = ('\0');

	m_bQuitFlg = false;
	m_bSignalFlg = false;
	
	int ret = pthread_create(&m_tid,&m_attr,ThreadProc, this);

	if (0 == ret)
	{
		LOGE("<<<< StartThread error\n");
	}
}
   
bool 
XThread::StopThread(int msec)
{
	if (!m_tid)
	{
		return true;
	}

	m_bQuitFlg = true;

	Notify();

	if (!m_tid)
	{
		return true;
	}

	int ret = pthread_join(m_tid, NULL);

	if (0 == ret)
	{
		return true;
	}
	else
	{
		LOGE("<<<< Stop thread [%s] (%lu, 0x%x) join failed %d [%s].", m_szThreadName, m_dwThreadID, m_dwThreadID, ret, strerror(ret));
		return false;
	}
} 
   
bool 
XThread::Wait(int msec)
{
	int ret = 0;
	pthread_mutex_lock(&m_mutex);

	if (m_bSignalFlg == false)
	{
		if (INFINITE != msec)
		{
#ifdef _FOR_IPHONE_
			struct timespec nptime;
			nptime.tv_sec = msec/1000;
			nptime.tv_nsec = msec%1000*1000000;

			ret = pthread_cond_timedwait_relative_np(&m_cond, &m_mutex, &nptime);

#else //_FOR_ANDROID_
			struct timespec nptime;
			XTime::GetTimeSpec(&nptime, msec);

			ret = pthread_cond_timedwait(&m_cond, &m_mutex, &nptime);
#endif
		}
		else
		{
			ret = pthread_cond_wait(&m_cond, &m_mutex);
		}
	}

	m_bSignalFlg = false;

	pthread_mutex_unlock(&m_mutex);

	unsigned long *pAddr = NULL; //[0] timer id; [1] timer pointer.
	while(1)
	{
		m_cSyncMSg.SyncStart();
		pAddr = (unsigned long*)m_cMsgQue.front();
		m_cSyncMSg.SyncEnd();
		if (pAddr != NULL)
		{
            if (XTimer::IsValid(*pAddr) == true)
            {
                reinterpret_cast<XTimer*>(*(pAddr+1))->DoAction();
			}
			delete pAddr;
		}
		else
		{
			break;
		}
	}

	// ETIMEDOUT
	if (0 == ret)
	{
		return true;
	}
	else
	{
		return false;
	}
}
   
void
XThread::Notify()
{
	pthread_mutex_lock(&m_mutex);
	m_bSignalFlg = true;
	int ret = pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
}

void* 
XThread::ThreadProc(void* pParam)
{
	int dwThreadID;
	XThread* pthread = (XThread*)pParam;
	
#ifdef _FOR_ANDROID_
	dwThreadID = gettid();
    JavaVM *pVM = XJniMgr::Instance()->GetJavaVM();
    JNIEnv *pEnv = NULL;
    pVM->AttachCurrentThread(&pEnv, NULL);
#else
	dwThreadID =  (int)pthread->m_tid;
#endif

	
	pthread->SetThreadID(dwThreadID);

	if (NULL == pthread) {
        return NULL;
    }

	int dwRunRet = pthread->Run();
	return NULL;
}

bool 
XThread::NotifyMsg(void* pAddr)
{
	m_cSyncMSg.SyncStart();
	m_cMsgQue.push_back(pAddr);
	m_cSyncMSg.SyncEnd();

	pthread_mutex_lock(&m_mutex);
	m_bSignalFlg = true;
	int ret = pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);

	return true;
}


