#include "XPageMgr.h"
#include "string.h"
#include "XPlatform.h"
#include "XLog.h"
#include "XPage.h"
#include <stdlib.h>

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

void XPageMgr::LoadNewPage(const char *pName, int anim, int flags)
{
    XPage *pCur = m_curPi.m_page;
    m_curPi.Reset();
    m_curPi.m_iAnim = anim;
    m_curPi.m_iFlags = flags;
    XPlatform::Instance()->LoadNewPage(pCur, pName, anim);
}

void XPageMgr::LoadExistPage(const char *pName, int anim)
{
    int i = IndexOf(pName);
    if (i < 0) {
        LOGE("Not find page '%s'", pName);
        return;
    }
    PageInfo &pi = m_cPages.at(i);
    LoadExistPage(pi.m_page->GetId(), anim);
}

void XPageMgr::LoadExistPage(int pageId, int anim)
{
    int idx = IndexOf(pageId);
    if (idx < 0) {
        LOGE("Not find page id =%d", pageId);
        return;
    }
    XPage *pCur = m_curPi.m_page;
    PageInfo &info = m_cPages.at(idx);

    if (anim == A_USE_HISTORY) {
        anim = GetInAnim(info.m_iAnim) | GetOutAnim(m_curPi.m_iAnim);
    }
    m_curPi = info;
    XPlatform::Instance()->LoadExistPage(pCur, info.m_page->GetName().c_str(), pageId, anim);

    for (int i = m_cPages.size() - 1; i > idx; --i) {
        Remove(i);
    }
}

void XPageMgr::GoBack()
{
    LOGD("page size:%d", m_cPages.size());
    if (m_cPages.size() <= 1) {
        exit(0);
        return;
    }
    PageInfo &info = m_cPages.at(m_cPages.size() - 2);
    LoadExistPage(info.m_page->GetId(), A_USE_HISTORY);
}

int XPageMgr::GetReverseAnim(int anim)
{
    if (anim == A_NONE) {
        return A_NONE;
    }
    int r = 0;
    for (int i = 0; i < 30; ++i) {
        if ((anim & (1 << i)) != 0) {
            r |= (i % 2) == 0 ? (1<<i+1) : (1<<i-1);
        }
    }
    return r;
}

void XPageMgr::AddPage(XPage *p)
{
    if (!p) {
        LOGE("p is NULL");
        return;
    }
    m_curPi.m_page = p;
    m_cPages.push_back(m_curPi);
}

void XPageMgr::Remove(int idx)
{
    if (idx < 0 || idx >= m_cPages.size()) {
        return;
    }
    PageInfo &p = m_cPages.at(idx);
    m_cPages.erase(m_cPages.begin() + idx);

    m_cDelPages.push_back(p.m_page);

    if (m_cDelPages.size() > 2) {
        XPage *page = m_cDelPages.at(m_cDelPages.size() - 1);
        page->OnDestroy();
        delete page;
    }
}

XPage *XPageMgr::At(int idx)
{
    if (idx >= 0 && idx < m_cPages.size()) {
        return m_cPages.at(idx).m_page;
    }
    return NULL;
}

XPage *XPageMgr::Get(int id)
{
    int i = IndexOf(id);
    return At(i);
}

XPage *XPageMgr::FindInAll(int id)
{
    XPage *p = At(IndexOf(id));
    if (p != NULL) {
        return p;
    }
    for (int i = 0; i < m_cDelPages.size(); ++i) {
        p = m_cDelPages.at(i);
        if(p->GetId() == id) {
            return p;
        }
    }
    return NULL;
}

int XPageMgr::IndexOf(int id)
{
    for (int i = 0; i < m_cPages.size(); ++i) {
        if(At(i)->GetId() == id) {
            return i;
        }
    }
    return -1;
}

int XPageMgr::IndexOf(const char *pName)
{
    if (pName == NULL) {
        return -1;
    }
    for (int i = 0; i < m_cPages.size(); ++i) {
        if(At(i)->GetName() == pName) {
            return i;
        }
    }
    return -1;
}

int XPageMgr::Count()
{
    return m_cPages.size();
}

void XPageMgr::PageInfo::Reset()
{
    m_page = NULL;
    m_iAnim = XPageMgr::A_NONE;
    m_iFlags = XPageMgr::F_NONE;
}


