#ifndef CXX_XTHREAD_H
#define CXX_XTHREAD_H

#include <pthread.h>
#include <list>
#include "XMutex.h"
using namespace std;

#ifndef INFINITE 
#define INFINITE 0xffffffffL
#endif

class XThread
{
public:
    typedef void (*Runnable)(void *params);

    XThread(Runnable r = NULL, void *params = NULL);
    
    virtual ~XThread();
    
    void StartThread();
    
    void StopThread();
    
    void Wait(int msec = INFINITE);

    void Notify();

    bool Join();

    int GetThreadID() {return m_dwThreadID;}
    
protected:
    static void *ThreadProc(void* pParam);
    virtual	void Run() {}

    Runnable m_runable;
    void *m_pParams;
    bool m_bQuit;
    volatile bool m_bWaiting;
    int	m_dwThreadID;
    pthread_t       m_tid;
    pthread_attr_t  m_attr;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
};

#endif

