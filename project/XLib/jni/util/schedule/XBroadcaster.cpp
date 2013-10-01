#include "XBroadcaster.h"

XBroadcaster *XBroadcaster::s_ins;

class XWatcherItem
{
public:
    XWatcherItem(int i) : m_iType(i){}
    int m_iType;
    vector<void*> m_list;
    vector<void*> m_funclist;
};

XBroadcaster::XBroadcaster()
{
}

XBroadcaster *XBroadcaster::Instance()
{
    if (!s_ins) {
        s_ins = new XBroadcaster();
        s_ins->StartThread();
    }
    return s_ins;
}

void XBroadcaster::PostEvent(XEvent *pEvt)
{
    if (NULL == pEvt) {
        return;
    }
    m_sync.Lock();
    m_events.push_back(pEvt);
    m_sync.Unlock();

    Notify();
}

void XBroadcaster::SendEvent(XEvent *pEvt)
{
    DealEvent(pEvt);
}

void XBroadcaster::Run()
{
    while (!m_bQuit) {
        if (m_events.empty()) {
            Wait();
        }
        if (m_bQuit) {
            break;
        }
        XEvent *pEvt = GetNext();
        DealEvent(pEvt);
    }
}

XEvent *XBroadcaster::GetNext()
{
    m_sync.Lock();
    XEvent *pEvt = m_events.at(0);
    m_events.erase(m_events.begin());
    m_sync.Unlock();
    return pEvt;
}

void XBroadcaster::DealEvent(XEvent *pEvt)
{
    if (NULL == pEvt) {
        return;
    }
}

XWatcherItem *XBroadcaster::FindWatcher(int iType, bool add)
{
    for (int i = 0; i < m_watchers.size(); ++i) {
        XWatcherItem *pItem = reinterpret_cast<XWatcherItem*>(m_watchers.at(i));
        if (pItem->m_iType == iType) {
            return pItem;
        }
    }
    if (add) {
        XWatcherItem *pItem = new XWatcherItem(iType);
        m_watchers.push_back(reinterpret_cast<void*>(pItem));
        return pItem;
    }
    return NULL;
}

static bool IsExist(vector<void*> &v, void *p)
{
    for (int i = 0; i < v.size(); ++i) {
        if (v.at(i) == p) {
            return true;
        }
    }
    return false;
}

bool XBroadcaster::RegistWatcher(XWatcher *pW, int iEvtType)
{
    if (NULL == pW) {
        return false;
    }
    XWatcherItem *pItem = FindWatcher(iEvtType, true);
    if (NULL == pItem) {
        return false;
    }

    if (IsExist(pItem->m_list, reinterpret_cast<void*>(pW))) {
        return false;
    }
    pItem->m_list.push_back(reinterpret_cast<void*>(pW));
    return true;
}

bool XBroadcaster::RegistWatcher(XFuncWatcher func, int iEvtType)
{
    if (NULL == func) {
        return false;
    }
    XWatcherItem *pItem = FindWatcher(iEvtType, true);
    if (NULL == pItem) {
        return false;
    }

    if (IsExist(pItem->m_funclist, reinterpret_cast<void*>(func))) {
        return false;
    }
    pItem->m_funclist.push_back(reinterpret_cast<void*>(func));
    return true;
}


bool XBroadcaster::UnRegistWatcher(XWatcher *pW, int iEvtType)
{
    if (NULL == pW) {
        return false;
    }
    XWatcherItem *pItem = FindWatcher(iEvtType, false);
    if (NULL == pItem) {
        return false;
    }
    for (int i = 0; i < pItem->m_list.size(); ++i) {
        if (pItem->m_list.at(i) == reinterpret_cast<void*>(pW)) {
            pItem->m_list.erase(pItem->m_list.begin() + i);
            return true;
        }
    }
    return false;
}

bool XBroadcaster::UnRegistWatcher(XFuncWatcher func, int iEvtType)
{
    if (NULL == func) {
        return false;
    }
    XWatcherItem *pItem = FindWatcher(iEvtType, false);
    if (NULL == pItem) {
        return false;
    }
    for (int i = 0; i < pItem->m_funclist.size(); ++i) {
        if (pItem->m_funclist.at(i) == reinterpret_cast<void*>(func)) {
            pItem->m_funclist.erase(pItem->m_funclist.begin() + i);
            return true;
        }
    }
    return false;
}


XEvent::XEvent(int iEvtType)
    :m_iType(iEvtType)
{
}
