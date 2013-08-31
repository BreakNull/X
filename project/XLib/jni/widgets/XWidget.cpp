#include "XWidget.h"
#include "XLog.h"
#include "XPlatform.h"
#include<ctype.h>

XWidget::XWidget(XPage *p)
    :m_pRealWidget(NULL)
    ,m_pParent(NULL)
    ,m_pPage(p)
    ,m_pChildren(NULL)
{
}

XWidget::~XWidget()
{
    if (NULL != m_pChildren) {
        for (int i = 0; i < m_pChildren->size(); ++i) {
            delete m_pChildren->at(i);
        }
        delete m_pChildren;
    }
}

void XWidget::Create()
{
    //TODO:
}

static bool GetColor(const string &s, int *val)
{
    int d = 0;
    const char *p = s.c_str();
    int len = strlen(p);
    if (len != 6 && len != 8) {
        return false;
    }
    for (int i = 0; *p && i < len; ++i,++p) {
        int cur = 0;
        if (*p >= '0' && *p <= '9') {
            cur = *p - '0';
        } else if (*p >= 'a' && *p <= 'z') {
            cur = *p - 'a' + 10;
        } else if (*p >= 'A' && *p <= 'Z') {
            cur = *p - 'A' + 10;
        } else {
            return false;
        }
        d = d*16 + cur;
    }
    if (len == 6) {
        d |= 0xff000000;
    }
    *val = d;
    return true;
}

void XWidget::SetProperty(const string &name, const XVariant &v)
{
    //TODO:
    if (name == "x") {

    } else if (name == "y") {

    } else if (name == "w") {

    } else if (name == "h") {

    } else if (name == "id") {
        m_cId = v.ToString();
        XPlatform::Instance()->SetId(this, m_cId);
    } else if (name == "bgcolor") {
        string s = v.ToString();
        int d = 0;
        if (!GetColor(s, &d)) {
            LOGE("The color '%s' is invalid", s.c_str());
            return;
        }
        XPlatform::Instance()->SetBgColor(this, d);
    }
}

XVariant XWidget::GetProperty(const string &name)
{
    //TODO:
    if (name == "x") {

    } else if (name == "y") {

    } else if (name == "w") {

    } else if (name == "h") {

    } else if (name == "id") {
        return XVariant(m_cId.c_str());
    }

    //not find this property
    return XVariant();
}

bool XWidget::IsRoot()
{
    //TODO:
    return false;
}

void XWidget::SetRoot(bool b)
{
    //TODO:
}

bool XWidget::IsContainer()
{
    return false;
}

string XWidget::GetId()
{
    XVariant v = GetProperty("id");
    return v.ToString();
}

XWidget *XWidget::GetRootWidget()
{
    if (this->IsRoot()) {
        return this;
    }

    XWidget *p = m_pParent;
    while (p) {
        if (p->IsRoot()) {
            return p;
        }
        p = p->m_pParent;
    }

    return NULL;
}

XWidget *XWidget::GetParent()
{
    return m_pParent;
}

void XWidget::SetParent(XWidget *parent)
{
    //TODO:
}

XWidget *XWidget::GetChild(const string &id)
{
    if (NULL == m_pChildren) {
        return NULL;
    }

    for (int i = 0; i < (int)m_pChildren->size(); ++i) {
        XWidget *p = m_pChildren->at(i);
        if (id == p->GetId()) {
            return p;
        }
    }
    return NULL;
}

vector<XWidget*> *XWidget::GetChildren()
{
    return m_pChildren;
}

void XWidget::AddChild(XWidget *pChild, int idx)
{
    if ((pChild == NULL) || (!IsContainer())) {
        return;
    }
    if (NULL == m_pChildren) {
        m_pChildren = new vector<XWidget*>();
    }
    if (idx < 0) {
        m_pChildren->push_back(pChild);
    } else {
        m_pChildren->insert(m_pChildren->begin() + idx, pChild);
    }
    XPlatform::Instance()->AddChild(this, pChild, idx);
}


