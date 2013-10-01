#include "XPageXml.h"
#include "XmlDocument.h"
#include "XLog.h"
#include "XWidgetFactory.h"
#include "XPage.h"
#include "XWidget.h"
#include "XButton.h"
#include "XLog.h"
#include "XOmlDb.h"

XPageXml::XPageXml()
    :m_pDoc(NULL)
    ,m_pStyle(NULL)
{
}

XPageXml::~XPageXml()
{
    delete m_pDoc;
    delete m_pStyle;
}

bool XPageXml::LoadBuffer(char *pXmlData, int len)
{
    //LOGD("XPageXml::LoadData");
    m_pDoc = new XmlDocument();
    bool b = m_pDoc->LoadBuffer(pXmlData, len);
    if (b) {
        Parse();
    }
    return b;
}

bool XPageXml::LoadFile(const char *pFileName)
{
    //LOGD("XPageXml::LoadFile fileName='%s'", pFileName);
    m_pDoc = new XmlDocument();
    bool b =m_pDoc->LoadFile(pFileName);
    if (b) {
        Parse();
    }
    return b;
}

XWidget *XPageXml::CreateRefView(const char *pRefName, XPage *page)
{
    if (pRefName == NULL) {
        LOGE("ref name is NULL");
        return NULL;
    }
    XmlElement *pRoot = m_pDoc->GetRoot();
    XmlElement *pElem = pRoot->GetChild(pRefName);
    if (pElem == NULL) {
        LOGE("Not find ref '%s'", pRefName);
        return NULL;
    }
    XmlElement *p = pElem->ChildAt(0);
    if (!p) {
        LOGE("Note <RefView name='%s'> has no child", pRefName);
        return NULL;
    }
    XWidget *pW = XWidgetFactory::Instance()->New(p->GetName());
    if (!pW) {
        LOGE("Not find %s::New() in XWidgetFactory", p->GetName());
        return NULL;
    }
    pW->Create(page, XWidget::F_NEW_REF);
    if (pW->IsContainer()) {
        ParseContainer(pW, p, page);
    } else {
        ParseWidget(pW, p, page);
    }
    return pW;
}

XWidget *XPageXml::CreateMainView(XPage *page)
{
    XmlElement *pRoot = m_pDoc->GetRoot();
    XmlElement *pElem = pRoot->GetChild("MainView");
    if (pElem == NULL) {
        LOGE("Not find <MainView>");
        return NULL;
    }
    ParsePageAttr(page, pElem);

    XmlElement *p = pElem->ChildAt(0);
    if (!p) {
        LOGE("Note <MainView> has no child");
        return NULL;
    }
    XWidget *pW = XWidgetFactory::Instance()->New(p->GetName());
    if (!pW) {
        LOGE("Not find %s::New() in XWidgetFactory", p->GetName());
        return NULL;
    }
    pW->Create(page, XWidget::F_NEW_REF);
    if (pW->IsContainer()) {
        ParseContainer(pW, p, page);
    } else {
        ParseWidget(pW, p, page);
    }
    return pW;
}


void XPageXml::Parse()
{
    XmlElement *pRoot = m_pDoc->GetRoot();
    for (int i = 0; i < pRoot->ChildCount(); ++i) {
        XmlElement *pE = pRoot->ChildAt(i);
        if (strcmp(pE->GetName(),"Style") == 0)
            ParseStyle(pE);
    }
}

void XPageXml::ParseStyle(XmlElement *pElem)
{
    if (pElem->AttrCount() != 0) {
        XmlAttr attr = pElem->AttrAt(0);
        if (strcmp(attr.GetName(), "src") != 0) {
            LOGE("Invalid Style attribute '%s'", attr.GetName());
            return;
        }
        int len = 0;
        void *pDat = XOmlDb::Instance()->ReadContent(attr.GetValue(), &len);
        if (!pDat) {
            LOGE("can't read css '%s'", attr.GetValue());
            return;
        }
        m_pStyle = new XStyle(m_pStyle, attr.GetValue());
        m_pStyle->LoadData((char*)pDat, true);
    } else {
        const char *pTxt = pElem->GetText();
        m_pStyle = new XStyle(m_pStyle, "<TAIL>");
        m_pStyle->LoadData((char*)pTxt, false);
    }
}

void XPageXml::ParseAttr(XWidget *pw, XmlElement *pElem, XPage *page)
{
    const char *pLis = pElem->GetAttr("listen");
    if (pLis != NULL) {
        page->SetListener(pw, pLis);
    }

    vector<XStyleAttr> vec;
    MergeAttr(pElem, vec);
    for (int i = 0; i < vec.size(); ++i) {
        XStyleAttr &a = vec.at(i);
        pw->SetProperty(a.m_pName, a.m_pValue);
    }
}

void XPageXml::ParsePageAttr(XPage *pw, XmlElement *pElem)
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

void XPageXml::ParseContainer(XWidget *pw, XmlElement *pElem, XPage *page)
{
    ParseAttr(pw, pElem, page);

    for (int i = 0; i < pElem->ChildCount(); ++i) {
        XmlElement *pE = pElem->ChildAt(i);
        XWidget *pC = XWidgetFactory::Instance()->New(pE->GetName());
        if (NULL == pC) {
            LOGE("new widget '%s' error", pE->GetName());
            break;
        }
        pC->Create(page, XWidget::F_NONE);
        if (pC->IsContainer()) {
            ParseContainer(pC, pE, page);
        } else {
            ParseWidget(pC, pE, page);
        }
        pw->AddChild(pC);
        delete pC;
    }
}

void XPageXml::ParseWidget(XWidget *pw, XmlElement *pElem, XPage *page)
{
    ParseAttr(pw, pElem, page);
}






