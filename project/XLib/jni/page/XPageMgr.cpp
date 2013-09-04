#include "XPageMgr.h"
#include "string.h"
#include "XPlatform.h"
#include "XLog.h"

XPageMgr *XPageMgr::s_ins;

XPageMgr::XPageMgr()
{
}

XPageMgr *XPageMgr::Instance()
{
    if (!s_ins) {
        s_ins = new XPageMgr;
    }
    return s_ins;
}

void XPageMgr::LoadNewPage(const char *pName, int anim)
{
    XPlatform::Instance()->LoadNewPage(pName, anim);
}

void XPageMgr::LoadExistPage(const char *pName, int anim)
{
    XPlatform::Instance()->LoadExistPage(pName, anim);
}

void XPageMgr::LoadExistPage(int pageId, int anim)
{
    XPlatform::Instance()->LoadExistPage(pageId, anim);
}

void XPageMgr::GoBack()
{
    XPlatform::Instance()->GoBack();
}

void XPageMgr::AddPage(int id, XPage *p)
{
    if (!p) {
        LOGE("p is NULL");
        return;
    }
    m_cPages.insert(std::pair<int,XPage*>(id, p));
}

XPage *XPageMgr::RemovePage(int id)
{
    XPage *p = GetPage(id);
    if (!p) {
        return NULL;
    }
    m_cPages.erase(id);
    return p;
}

XPage *XPageMgr::GetPage(int id)
{
    std::map<int, XPage*>::iterator it = m_cPages.find(id);
    if (it == m_cPages.end()) {
        return NULL;
    }
    return (*it).second;
}



