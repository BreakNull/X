#include "XPageXml.h"
#include "tinyxml.h"
#include "XLog.h"
#include "XWidgetFactory.h"
#include "XPage.h"
#include "XWidget.h"
#include "XButton.h"
#include "XLog.h"

XPageXml::XPageXml(XPage *p)
    :m_pDoc(NULL)
    ,m_pMainView(NULL)
    ,m_page(p)
{
}

XPageXml::~XPageXml()
{
    delete m_pDoc;
}

XPageXml *XPageXml::Clone(XPage *p)
{
    return new XPageXml(p);
}

bool XPageXml::LoadData(char *pXmlData)
{
    LOGD("XPageXml::LoadData");
    m_pDoc = new TiXmlDocument();
    const char *p = m_pDoc->Parse(pXmlData, NULL, TIXML_ENCODING_UTF8);
    if (p && *p == '\0') {
        return true;
    } else {
        LOGE("XPageXml::Load() error p=[%s]", p);
        return false;
    }
}

bool XPageXml::LoadFile(const char *pFileName)
{
    LOGD("XPageXml::LoadFile fileName='%s'", pFileName);
    m_pDoc = new TiXmlDocument();
    bool b = m_pDoc->LoadFile(pFileName, TIXML_ENCODING_UTF8);
    if (!b) {
        LOGE("XPageXml::LoadFile error fileName='%s'", pFileName);
    }
    return b;
}

XWidget *XPageXml::GetMainView()
{
    return m_pMainView;
}

void XPageXml::Parse()
{
    LOGD("XPageXml::Parse");
    if (!m_pDoc) {
        LOGE("XPageXml::LoadFile m_pDoc is NULL");
        return;
    }
    TiXmlElement *pRoot = m_pDoc->RootElement();

    TiXmlNode *pMainViewNode = pRoot->FirstChild("MainView");
    if (pMainViewNode) {
        ParseMainView(static_cast<TiXmlElement*>(pMainViewNode));
    }
}

void XPageXml::ParseMainView(TiXmlElement *pElem)
{
    LOGD("XPageXml::ParseMainView begin");
    TiXmlElement *p = pElem->FirstChildElement();
    if (!p) {
        LOGE("XPageXml::ParseMainView note <MainView> has no child");
        return;
    }
    m_pMainView = XWidgetFactory::Instance()->New(p->Value(), m_page);
    if (!m_pMainView) {
        LOGE("XPageXml::ParseMainView() Not find %s::New() in XWidgetFactory", p->Value());
        return;
    }
    m_pMainView->Create();
    if (m_pMainView->IsContainer()) {
        ParseContainer(m_pMainView, p);
    } else {
        ParseWidget(m_pMainView, p);
    }
    LOGD("XPageXml::ParseMainView end");
}

void XPageXml::ParseAttr(XWidget *pw, TiXmlElement *pElem)
{
    TiXmlAttribute *pAttr = pElem->FirstAttribute();
    for (; pAttr != NULL; pAttr = pAttr->Next()) {
        pw->SetProperty(pAttr->Name(), pAttr->Value());
    }
}

void XPageXml::ParseContainer(XWidget *pw, TiXmlElement *pElem)
{
    ParseAttr(pw, pElem);

    TiXmlElement *pE = pElem->FirstChildElement();
    for (; NULL != pE; pE = pE->NextSiblingElement()) {
        XWidget *pC = XWidgetFactory::Instance()->New(pE->Value(), m_page);
        if (NULL == pC) {
            break;
        }
        pC->Create();
        pw->AddChild(pC);
        if (pC->IsContainer()) {
            ParseContainer(pC, pE);
        } else {
            ParseWidget(pC, pE);
        }
    }
}

void XPageXml::ParseWidget(XWidget *pw, TiXmlElement *pElem)
{
    ParseAttr(pw, pElem);

    if (pElem->Value() == "Btn") {
        ParseButton(pw, pElem);
    }
    else if (pElem->Value() == "Lab") {
        ParseLabel(pw, pElem);
    }
}

void XPageXml::ParseButton(XWidget *pw, TiXmlElement *pElem)
{
}

void XPageXml::ParseLabel(XWidget *pw, TiXmlElement *pElem)
{
}





