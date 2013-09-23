#include "XPageXml.h"
#include "XmlDocument.h"
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
    delete m_pStyle;
}

XPageXml *XPageXml::Clone(XPage *p)
{
    return new XPageXml(p);
}

bool XPageXml::LoadBuffer(char *pXmlData, int len)
{
    //LOGD("XPageXml::LoadData");
    m_pDoc = new XmlDocument();
    return m_pDoc->LoadBuffer(pXmlData, len);
}

bool XPageXml::LoadFile(const char *pFileName)
{
    //LOGD("XPageXml::LoadFile fileName='%s'", pFileName);
    m_pDoc = new XmlDocument();
    return m_pDoc->LoadFile(pFileName);
}

XWidget *XPageXml::GetMainView()
{
    return m_pMainView;
}

void XPageXml::Parse()
{
    //LOGD("XPageXml::Parse begin ===>");
    if (!m_pDoc) {
        LOGE("XPageXml::LoadFile m_pDoc is NULL");
        return;
    }
    XmlElement *pRoot = m_pDoc->GetRoot();
    for (int i = 0; i < pRoot->ChildCount(); ++i) {
        XmlElement *pE = pRoot->ChildAt(i);
        if (strcmp(pE->GetName(),"MainView") == 0)
            ParseMainView(pE);
        else if (strcmp(pE->GetName(),"Style") == 0)
            ParseStyle(pE);
    }
    //LOGD("XPageXml::Parse end <===");
}

void XPageXml::ParseMainView(XmlElement *pElem)
{
    //LOGD("XPageXml::ParseMainView begin");
    XmlElement *p = pElem->ChildAt(0);
    if (!p) {
        LOGE("XPageXml::ParseMainView note <MainView> has no child");
        return;
    }
    m_pMainView = XWidgetFactory::Instance()->New(p->GetName(), m_page);
    if (!m_pMainView) {
        LOGE("XPageXml::ParseMainView() Not find %s::New() in XWidgetFactory", p->GetName());
        return;
    }
    m_pMainView->Create(XWidget::F_NEW_REF);
    //parse MainView attr
    ParseAttr(m_page, pElem);
    if (m_pMainView->IsContainer()) {
        ParseContainer(m_pMainView, p);
    } else {
        ParseWidget(m_pMainView, p);
    }
    //LOGD("XPageXml::ParseMainView end");
}

void XPageXml::ParseStyle(XmlElement *pElem)
{
    if (pElem->AttrCount() != 0) {
        XmlAttr attr = pElem->AttrAt(0);
        if (strcmp(attr.GetName(), "src") != 0) {
            LOGE("Invalid Style attribute '%s'", attr.GetName());
            return;
        }
        m_pStyle = new XStyle(m_pStyle, attr.GetValue());
        m_pStyle->LoadFile(attr.GetValue());
    } else {
        const char *pTxt = pElem->GetText();
        m_pStyle = new XStyle(m_pStyle, "<TAIL>");
        m_pStyle->LoadData((char*)pTxt, false);
    }
}

void XPageXml::ParseAttr(XWidget *pw, XmlElement *pElem)
{
    const char *pLis = pElem->GetAttr("listen");
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

void XPageXml::ParseAttr(XPage *pw, XmlElement *pElem)
{
    vector<XStyleAttr> vec;
    MergeAttr(pElem, vec);
    for (int i = 0; i < vec.size(); ++i) {
        XStyleAttr &a = vec.at(i);
        pw->SetProperty(a.m_pName, a.m_pValue);
    }
}

void XPageXml::MergeAttr(XmlElement *pE, vector<XStyleAttr> &vec)
{
    const char *pClass = NULL, *pId = NULL;
    XStyleSpec *pss = NULL;

    pClass = pE->GetAttr("class");
    pId = pE->GetAttr("id");

    if (m_pStyle) {
        pss = m_pStyle->Search(pE->GetName(), pClass, pId);
        vec = pss->GetAttrs();
    }

    for (int i = 0; i < pE->AttrCount(); ++i) {
        XmlAttr attr = pE->AttrAt(i);
        int idx = -1;
        if (pss != NULL) {
            idx = pss->IndexOf(attr.GetName());
        }
        if (idx >= 0) {
            XStyleAttr &a = vec.at(idx);
            a.m_pValue = attr.GetValue();
        } else {
            XStyleAttr a;
            a.m_pName = attr.GetName();
            a.m_pValue = attr.GetValue();
            vec.push_back(a);
        }
    }
}

void XPageXml::ParseContainer(XWidget *pw, XmlElement *pElem)
{
    ParseAttr(pw, pElem);

    for (int i = 0; i < pElem->ChildCount(); ++i) {
        XmlElement *pE = pElem->ChildAt(i);
        XWidget *pC = XWidgetFactory::Instance()->New(pE->GetName(), m_page);
        if (NULL == pC) {
            LOGE("new widget '%s' error", pE->GetName());
            break;
        }
        pC->Create(XWidget::F_NONE);
        if (pC->IsContainer()) {
            ParseContainer(pC, pE);
        } else {
            ParseWidget(pC, pE);
        }
        pw->AddChild(pC);
        delete pC;
    }
}

void XPageXml::ParseWidget(XWidget *pw, XmlElement *pElem)
{
    ParseAttr(pw, pElem);
}






