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
    ,m_pStyle(NULL)
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
    LOGD("XPageXml::Parse begin ===>");
    if (!m_pDoc) {
        LOGE("XPageXml::LoadFile m_pDoc is NULL");
        return;
    }
    TiXmlElement *pRoot = m_pDoc->RootElement();
    TiXmlElement *pE = pRoot->FirstChildElement();
    for (; NULL != pE; pE = pE->NextSiblingElement()) {
        if (strcmp(pE->Value(),"MainView") == 0)
            ParseMainView(pE);
        else if (strcmp(pE->Value(),"Style") == 0)
            ParseStyle(pE);
    }
    LOGD("XPageXml::Parse end <===");
}

void XPageXml::ParseMainView(TiXmlElement *pElem)
{
    //LOGD("XPageXml::ParseMainView begin");
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
    //parse MainView attr
    ParseAttr(m_page, pElem);
    if (m_pMainView->IsContainer()) {
        ParseContainer(m_pMainView, p);
    } else {
        ParseWidget(m_pMainView, p);
    }
    //LOGD("XPageXml::ParseMainView end");
}

void XPageXml::ParseStyle(TiXmlElement *pElem)
{
    TiXmlAttribute *pAttr = pElem->FirstAttribute();
    if (NULL != pAttr) {
        if (strcmp(pAttr->Name(), "src") != 0) {
            LOGE("Invalid Style attribute '%s'", pAttr->Name());
            return;
        }
        m_pStyle = new XStyle(m_pStyle, pAttr->Value());
        m_pStyle->LoadFile(pAttr->Value());
    } else {
        const char *pTxt = pElem->GetText();
        LOGD("style txt=%s", pTxt);
        m_pStyle = new XStyle(m_pStyle, "<TAIL>");
        m_pStyle->LoadData((char*)pTxt);
    }
}

void XPageXml::ParseAttr(XWidget *pw, TiXmlElement *pElem)
{
    const char *pLis = pElem->Attribute("listen");
    if (pLis != NULL) {
        m_page->SetListener(pw, pLis);
    }

    vector<XStyleAttr> vec;
    MergeAttr(pElem, vec);
    for (int i = 0; i < vec.size(); ++i) {
        XStyleAttr &a = vec.at(i);
        pw->SetProperty(a.m_pName, a.m_pValue);
    }
}

void XPageXml::ParseAttr(XPage *pw, TiXmlElement *pElem)
{
    vector<XStyleAttr> vec;
    MergeAttr(pElem, vec);
    for (int i = 0; i < vec.size(); ++i) {
        XStyleAttr &a = vec.at(i);
        pw->SetProperty(a.m_pName, a.m_pValue);
    }
}

void XPageXml::MergeAttr(TiXmlElement *pE, vector<XStyleAttr> &vec)
{
    const char *pClass = NULL, *pId = NULL;
    XStyleSpec *pss = NULL;

    pClass = pE->Attribute("class");
    pId = pE->Attribute("id");

    if (m_pStyle) {
        pss = m_pStyle->Search(pE->Value(), pClass, pId);
        vec = pss->GetAttrs();
    }

    TiXmlAttribute *pAttr = pE->FirstAttribute();
    for (; pAttr != NULL; pAttr = pAttr->Next()) {
        int idx = -1;
        if (pss != NULL) {
            idx = pss->IndexOf(pAttr->Name());
        }
        if (idx >= 0) {
            XStyleAttr &a = vec.at(idx);
            a.m_pValue = pAttr->Value();
        } else {
            XStyleAttr a;
            a.m_pName = pAttr->Name();
            a.m_pValue = pAttr->Value();
            vec.push_back(a);
        }
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
        if (pC->IsContainer()) {
            ParseContainer(pC, pE);
        } else {
            ParseWidget(pC, pE);
        }
        pw->AddChild(pC);
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





