#include "XPage.h"
#include "Init.h"
#include "XPageXml.h"
#include "XLog.h"
#include "XPlatform.h"
#include "XWidget.h"
#include "XPageMgr.h"

XPage::XPage(void *pRealXPage, const string &name, int id)
    :m_pRealPage(pRealXPage)
    ,m_cName(name)
    ,m_id(id)
    ,m_pXml(NULL)
    ,m_pRoot(NULL)
    ,m_iStyle(0)
{
}

XPage::~XPage()
{
    delete m_pXml;
    delete m_pRoot;
}

XWidget *XPage::OnCreate()
{
    //LOGD("XPage::OnCreate page name is '%s'", m_cName.c_str());
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
    //LOGD("XPage::OnDestroy page name is '%s'", m_cName.c_str());
    delete m_pXml;
    m_pXml = NULL;
    XPageMgr::Instance()->RemovePage(m_id);
    delete this;
}

void XPage::OnStart()
{
    //LOGD("XPage::OnStart page name is '%s'", m_cName.c_str());
    //TODO:
}

void XPage::OnStop()
{
    //LOGD("XPage::OnStop page name is '%s'", m_cName.c_str());
    //TODO:
}

void XPage::OnBackPressed()
{
    XPlatform::Instance()->GoBack();
}

void *XPage::FindById(const string &id, XWidget *parent)
{
    XWidget *p = (NULL == parent ? m_pRoot : parent);
    if (NULL == p) {
        LOGE("There has not any widgets in this page");
        return NULL;
    }
    return XPlatform::Instance()->FindById(id.c_str(), p);
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

void XPage::SetProperty(const string &name, const XVariant &val)
{
    //LOGD("attr [%s]=[%s]", name.c_str(), val.ToString().c_str());
    if (name == "title") {
        SetTitle(val.ToString());
    } else if (name == "notitle") {
        if (val.ToString() == "true")
            m_iStyle |= S_NO_TITLE;
    } else if (name == "fullscreen") {
        if (val.ToString() == "true")
            m_iStyle |= S_FULL_SCREEN;
    }
}

void XPage::SetListener(XWidget *pw, const string &name)
{
    XPlatform::Instance()->SetListener(this, pw, name);
}

void XPage::ClearListener(XWidget *pw, const string &name)
{
    XPlatform::Instance()->ClearListener(this, pw, name);
}




