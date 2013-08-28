#include "XPageManager.h"
#include "string.h"

XPageManager *XPageManager::s_ins;

XPageManager::XPageManager()
{
}

XPageManager *XPageManager::Instance()
{
    if (!s_ins) {
        s_ins = new XPageManager;
    }
    return s_ins;
}

void XPageManager::AddPage(int id, XPage *p)
{
    if (!p) {
        //Log error
        return;
    }
    m_cPages.insert(std::pair<int,XPage*>(id, p));
}

XPage *XPageManager::RemovePage(int id)
{
    XPage *p = GetPage(id);
    if (!p) {
        return NULL;
    }
    m_cPages.erase(id);
    return p;
}

XPage *XPageManager::GetPage(int id)
{
    std::map<int, XPage*>::iterator it = m_cPages.find(id);
    if (it == m_cPages.end()) {
        return NULL;
    }
    return (*it).second;
}



