#ifndef XBROADCASTER_H
#define XBROADCASTER_H

class XEvent;
class XWatcher;
typedef void (*XFuncWatcher)(XEvent *);

#include <map>
using namespace std;

/**
 * 事件广播中心，用户可以注册、接收处理感兴趣的事件
 */
class XBroadcaster
{
public:
    static XBroadcaster *Instance();

    /*
     * 向广播中心发送事件， 返回是否发送成功
     * @param bSync 是否同步发送
     */
    bool PostEvent(XEvent *pEvt, bool bSync);

    /*
     * 注册一个事件观察者
     * @param iEvtType 感兴趣的事件类型
     */
    bool RegistWatcher(XWatcher *pW, int iEvtType);
    bool RegistWatcher(XFuncWatcher func, int iEvtType);

    /*
     * 撤消注册一个事件观察者
     */
    bool UnRegistWatcher(XWatcher *pW);
    bool UnRegistWatcher(XFuncWatcher func);

private:
    XBroadcaster();
    static XBroadcaster *s_ins;
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
