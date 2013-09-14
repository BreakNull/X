#include "XmlElement.h"
#include <string.h>

XmlAttr::XmlAttr(const char *pName, const char *pValue)
{
    m_pName = pName;
    m_pValue = pValue;
}

XmlElement::XmlElement()
{
    m_pData = NULL;
    m_pSs = NULL;
    m_bHasTxt = false;
    m_sAttrSize = 0;
    m_sChildSize = 0;
    m_pChildren = NULL;
}

void XmlElement::Load(char *pData, char *pSs)
{
    m_pData = pData;
    m_pSs = pSs;

    m_sAttrSize = *(short*)(pData + 2);
    m_sChildSize = *(short*)(pData + 4 + m_sAttrSize * 4);
    m_pChildren = new XmlElement[m_sChildSize];

    if (m_sAttrSize > 0) {
        short sTxt = *(short*)(pData + 4 + (m_sAttrSize-1)*4);
        if (strcmp(pSs+sTxt, "#txt") == 0) {
            m_bHasTxt = true;
        }
    }

    char *pd = m_pData + 4 + m_sAttrSize * 4 + 2;
    int sz = 0;
    for (int i = 0; i < m_sChildSize; ++i) {
        XmlElement *pc = ChildAt(i);
        pc->Load(pd + sz, m_pSs);
        sz += pc->GetDataLen();
    }
}

const char *XmlElement::Name()
{
    short idx = *(short*)m_pData;
    return m_pSs + idx;
}

int XmlElement::ChildSize()
{
    return m_sChildSize;
}

int XmlElement::AttrSize()
{
    return m_sAttrSize - (m_bHasTxt ? 1 : 0);
}

XmlElement *XmlElement::ChildAt(int idx)
{
    if (idx < 0 || idx >= m_sChildSize) {
        return NULL;
    }
    return m_pChildren + idx;
}

XmlAttr XmlElement::AttrAt(int idx)
{
    short *p = (short*)(m_pData + 4 + idx * 4);
    XmlAttr attr(m_pSs + p[0], m_pSs + p[1]);
    return attr;
}

XmlElement *XmlElement::GetChild(const char * name)
{
    for (int i = 0; i < m_sChildSize; ++i) {
        if (strcmp(m_pChildren[i].Name(), name) == 0) {
            return m_pChildren + i;
        }
    }
    return NULL;
}

const char *XmlElement::GetAttr(const char* name)
{
    int num = AttrSize();
    for (int i = 0; i < num; ++i) {
        short *s = (short*)(m_pData + 4 + i * 4);
        if (strcmp(m_pSs + s[0], name) == 0) {
            return m_pSs + s[1];
        }
    }
    return NULL;
}

const char *XmlElement::GetText()
{
    if (!m_bHasTxt) {
        return NULL;
    }

    char *p = m_pData + 4 + m_sAttrSize * 4 - 2;
    short s = *(short*)p;
    return m_pSs + s;
}

int XmlElement::GetDataLen()
{
    int len = 4 + m_sAttrSize * 4 + 2;
    for (int i = 0; i < m_sChildSize; ++i) {
        len += m_pChildren[i].GetDataLen();
    }
    return len;
}

