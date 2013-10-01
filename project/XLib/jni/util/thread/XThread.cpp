#include "XThread.h"
#include "XLog.h"
#include "XDateTime.h"
#include <string.h>

#ifdef _FOR_ANDROID_
#include "jni.h"
#include "XJniMgr.h"
#endif

XThread::XThread(XRunnable r, void *params)
{
    m_runable = r;
    m_pParams = params;
    m_tid = NULL;
    m_bQuit = false;
    m_bWaiting = false;

	int ret = pthread_attr_init(&m_attr);
	ret = pthread_attr_setstacksize(&m_attr, 64*1024);
	
    if (0 != ret) {
		LOGE("thread m_attr stacksize init failed %d\n", ret);
	}

	ret = pthread_mutex_init(&m_mutex, NULL);
    if (0 != ret) {
		LOGE("thread m_mutex init failed %d\n", ret);
	}

	ret = pthread_cond_init(&m_cond, NULL);
    if (0 != ret) {
        LOGE("thread m_cond init failed %d\n", ret);
	}
}
   
XThread::~XThread()
{
}
   
void XThread::StartThread()
{
    if (m_tid) {
        return;
    }
    m_bQuit = false;
    m_bWaiting = false;
	
    int ret = pthread_create(&m_tid, &m_attr, ThreadProc, this);

    if (0 == ret) {
        LOGE("StartThread error");
	}
}
   
void XThread::StopThread()
{
    if (!m_tid) {
        return;
	}
    m_bQuit = true;
	Notify();
}

bool XThread::Join()
{
    int ret = pthread_join(m_tid, NULL);
    return 0 == ret;
}

void XThread::Wait(int msec)
{
    int ret = 0;
    if (m_bWaiting) {
        return;
    }
    m_bWaiting = true;

    if (INFINITE != msec) {
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
    else {
        ret = pthread_cond_wait(&m_cond, &m_mutex);
    }
    m_bWaiting = false;
}
   
void XThread::Notify()
{
    if (m_bWaiting) {
        pthread_cond_signal(&m_cond);
    }
}

void *XThread::ThreadProc(void* pParam)
{
	int dwThreadID;
    XThread* pthread = reinterpret_cast<XThread*>(pParam);
	
#ifdef _FOR_ANDROID_
	dwThreadID = gettid();
    JavaVM *pVM = XJniMgr::Instance()->GetJavaVM();
    JNIEnv *pEnv = NULL;
    pVM->AttachCurrentThread(&pEnv, NULL);
#else
	dwThreadID =  (int)pthread->m_tid;
#endif

	
    pthread->m_dwThreadID = dwThreadID;

    if (pthread->m_runable) {
        pthread->m_runable(pthread->m_pParams);
    } else {
        pthread->Run();
    }
    return NULL;
}


