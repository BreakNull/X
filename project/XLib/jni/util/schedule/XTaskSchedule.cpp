#include "XTaskSchedule.h"
#include "string.h"


XTask::XTask(int priority)
{
    if (priority > 100)
        m_iPriority = 100;
    else if (priority < -100)
        m_iPriority = -100;
    else
        m_iPriority = priority;
}

XTaskSchedule::XTaskSchedule()
{
}

XTaskSchedule *XTaskSchedule::GetDefault()
{
    static XTaskSchedule *s_ins = NULL;
    if (!s_ins) {
        s_ins = new XTaskSchedule;
        s_ins->StartThread("{Default TaskSchedule Thread}");
    }
    return s_ins;
}

void XTaskSchedule::Schedule(XTask *pTask)
{
    if (NULL == pTask) {
        return;
    }
    m_sync.SyncStart();
    m_taskList.push_back(pTask);
    m_sync.SyncEnd();
    Notify();
}

int  XTaskSchedule::Run()
{
    while (!m_bQuitFlg) {
        if (m_taskList.empty()) {
            Wait();
        }
        if (m_bQuitFlg) {
            break;
        }
        XTask *pTask = GetNext();
        if(pTask) {
            pTask->Run();
        }
    }
    return 0;
}

XTask *XTaskSchedule::GetNext()
{
    m_sync.SyncStart();
    XTask *pNext = NULL;
    int pri = -1000;
    list<XTask*>::iterator it = m_taskList.begin();
    list<XTask*>::iterator next;

    for (; it != m_taskList.end(); ++it) {
        XTask *p = *it;
        if (p->GetPriority() > pri) {
            pri = p->GetPriority();
            next = it;
            pNext = p;
        }
    }
    if (NULL != pNext) {
        m_taskList.erase(next);
    }
    m_sync.SyncEnd();
    return pNext;
}



