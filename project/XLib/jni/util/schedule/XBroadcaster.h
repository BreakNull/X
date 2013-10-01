#ifndef XBROADCASTER_H
#define XBROADCASTER_H

#include "XThread.h"
#include "XMutex.h"
class XWatcherItem;
class XEvent;
class XWatcher;
typedef void (*XFuncWatcher)(XEvent *);

#include <vector>
using namespace std;

/**
 * 事件广播中心，用户可以注册、接收处理感兴趣的事件
 */
class XBroadcaster : public XThread
{
public:
    static XBroadcaster *Instance();

    /*
     * 向广播中心发送异步事件
     */
    void PostEvent(XEvent *pEvt);

    /*
     * 向广播中心发送同步事件
     */
    void SendEvent(XEvent *pEvt);

    /*
     * 注册一个事件观察者
     * @param iEvtType 感兴趣的事件类型
     */
    bool RegistWatcher(XWatcher *pW, int iEvtType);
    bool RegistWatcher(XFuncWatcher func, int iEvtType);

    /*
     * 撤消注册一个事件观察者
     */
    bool UnRegistWatcher(XWatcher *pW, int iEvtType);
    bool UnRegistWatcher(XFuncWatcher func, int iEvtType);

protected:
    virtual	void Run();
    XEvent *GetNext();
    void DealEvent(XEvent *pEvt);
    XWatcherItem *FindWatcher(int iType, bool add);

private:
    XBroadcaster();
    static XBroadcaster *s_ins;
    vector<XEvent*> m_events;
    XMutex m_sync;
    vector<void*> m_watchers;
};


/**
 * 广播事件
 */
class XEvent
{
public:
    /*
     * @param iEvtType  事件类型。 小于0的分配给框架使用， 大于0的分配给用户使用
     */
    XEvent(int iEvtType);

protected:
    //event type
    int m_iType;
};

/**
 * 观察者
 */
class XWatcher
{
public:
    XWatcher();

    //处理感兴趣的事件
    virtual void OnEvent(XEvent *pEvt) = 0;
};

#endif // XBROADCASTER_H
