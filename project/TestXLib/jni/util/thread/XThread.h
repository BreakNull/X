#ifndef CXX_XTHREAD_H
#define CXX_XTHREAD_H

#include <pthread.h>
#include <list>
#include "XSyncObj.h"
using namespace std;

#define THREAD_INFO_NAME_LEN         (64)

#ifndef INFINITE 
#define INFINITE 0xffffffffL
#endif

class XThread
{
public:
    XThread();
    
    virtual ~XThread();
    
    void StartThread(const char *name = "Unknown Thread");
    
    bool StopThread(int msec = INFINITE); 
    
    bool Wait(int msec = INFINITE);
    
    void Notify();

	virtual	int  Run() = 0;

	int GetThreadID() {return m_dwThreadID;}	void SetThreadID(int thread_id) {m_dwThreadID = thread_id;}
	bool NotifyMsg(void* pAddr);
private:
	static void* ThreadProc(void* pParam);
    
private:
	bool			m_bQuitFlg;
    bool         m_bSignalFlg;
	char			m_szThreadName[THREAD_INFO_NAME_LEN];
	int			m_dwThreadID;
    pthread_t       m_tid;
    pthread_attr_t  m_attr;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;

	list<void*> m_cMsgQue;
	XSyncObj m_cSyncMSg;
};

#endif

