#include "XPage.h"
#include "Init.h"
#include "XPageXml.h"
#include "XLog.h"
#include "XPlatform.h"
#include "XWidget.h"

XPage::XPage(void *pRealXPage, const string &name, int id)
    :m_pRealPage(pRealXPage)
    ,m_cName(name)
    ,m_id(id)
    ,m_pXml(NULL)
    ,m_pRoot(NULL)
{
}

XWidget *XPage::OnCreate()
{
    LOGD("XPage::OnCreate page name is '%s'", m_cName.c_str());
    if (::GetXPageXml()) {
        delete m_pXml;
        m_pXml = ::GetXPageXml()->Clone(this);
        //TODO:
        string root("/sdcard/");
        string fn = root + m_cName + ".xml";
        if (m_pXml->LoadFile(fn.c_str())) {
            m_pXml->Parse();
        }
        m_pRoot = m_pXml->GetMainView();
        return m_pRoot;
    }

    return NULL;
}

void XPage::OnDestroy()
{
    LOGD("XPage::OnDestroy page name is '%s'", m_cName.c_str());
    delete m_pXml;
    m_pXml = NULL;
    //TODO:
}

void XPage::OnStart()
{
    LOGD("XPage::OnStart page name is '%s'", m_cName.c_str());
    //TODO:
}

void XPage::OnStop()
{
    LOGD("XPage::OnStop page name is '%s'", m_cName.c_str());
    //TODO:
}

XWidget *XPage::FindById(const string &id, XWidget *parent)
{
    XWidget *p = (NULL == parent ? m_pRoot : parent);
    if (NULL == p) {
        LOGE("There has not any widgets in this page");
        return NULL;
    }
    if (p->GetId() == id) {
        return p;
    }
    for (int i = 0; i < p->GetChildren()->size(); ++i) {
        XWidget *pChild = p->GetChildren()->at(i);
        if (NULL == pChild) {
            LOGE("There has NULL widget in this page");
            continue;
        }
        if (pChild->GetId() == id) {
            return pChild;
        } else if (pChild->IsContainer()) {
            return FindById(id, pChild);
        }
    }
    return NULL;
}

bool XPage::OnCreateOptionsMenu(XMenu *pMenu)
{
    //TODO:
    return true;
}

void XPage::SetTitle(const string &title)
{
    XPlatform::Instance()->SetTitle(this, title);
}




