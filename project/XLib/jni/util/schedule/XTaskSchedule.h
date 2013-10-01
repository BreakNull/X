#ifndef TASKSCHEDULE_H
#define TASKSCHEDULE_H
#include "XThread.h"
#include <list>
using namespace std;

/**
 * 可以向这个任务调度器中一些发送任务， 之后，
 * 这些任务将会在新线程中一个一个的按顺序及优先级执行
 */


class XTask
{
public:
    /*
     * @priority 任务优先级，优先级都是相对的
     *           值越大，优先级越高，就会越先被调度执行
     *           默认优先级为0，表示普通优先级。
     *           priority取值范围是[-100, 100]
     *
     */
    XTask(int priority = 0);
    int GetPriority() {return m_iPriority;}
    ~XTask();
    virtual void Run() = 0;

protected:
    int m_iPriority;
};


class XTaskSchedule : public XThread
{
public:
    XTaskSchedule();

    /**
     * 获得一个默认的调度器
     */
    static XTaskSchedule *GetDefault();

    /**
     * 调度一个任务， 此任务将会在某个时候被执行
     * 当任务被执行完成之后，会delete此Task
     */
    void Schedule(XTask *pTask);

protected:
    virtual	void  Run();
    XTask *GetNext();

    list<XTask*> m_taskList;
    XMutex m_sync;
};

#endif // TASKSCHEDULE_H
