#include "XPage.h"
#include "Init.h"
#include "XPageXml.h"
#include "XLog.h"
#include "XPlatform.h"
#include "XWidget.h"
#include "XPageMgr.h"
#include "XOmlDb.h"

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
    delete m_pXml;
    m_pXml = new XPageXml();

    int len = 0;
    void *pData = XOmlDb::Instance()->ReadContent(m_cName.c_str(), &len);
    if (pData) {
        m_pXml->LoadBuffer((char*)pData, len);
    }
    m_pRoot = m_pXml->CreateMainView(this);
    return m_pRoot;
}

void XPage::OnDestroy()
{
    LOGD("page name is '%s' id=%d", m_cName.c_str(), m_id);
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
    XPageMgr::Instance()->GoBack();
}

void *XPage::FindById(const string &id)
{
    return XPlatform::Instance()->FindById(id.c_str(), m_pRoot);
}

bool XPage::OnCreateOptionsMenu(XMenu *pMenu)
{
    //TODO:
    return true;
}

void XPage::SetTitle(const string &title)
{
    m_cTitle = title;
    XPlatform::Instance()->SetTitle(this, title);
}

void XPage::ResetTitle()
{
    XPlatform::Instance()->SetTitle(this, m_cTitle);
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




