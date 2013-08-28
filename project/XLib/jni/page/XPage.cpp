#include "XPage.h"
#include "Init.h"
#include "XPageXml.h"
#include "XLog.h"
#include "XPlatform.h"

XPage::XPage(void *pRealXPage, const string &name, int id)
    :m_pRealPage(pRealXPage)
    ,m_cName(name)
    ,m_id(id)
    ,m_pXml(NULL)
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
        return m_pXml->GetMainView();
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

bool XPage::OnCreateOptionsMenu(XMenu *pMenu)
{
    //TODO:
    return true;
}

void XPage::SetTitle(const string &title)
{
    XPlatform::Instance()->SetTitle(this, title);
}




