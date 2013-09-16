#ifndef XMLELEMENT_H
#define XMLELEMENT_H

class XmlAttr
{
public:
    XmlAttr(const char *pName, const char *pValue);
    const char *GetName() {return m_pName;}
    const char *GetValue() {return m_pValue;}

private:
    const char *m_pName;
    const char *m_pValue;
};

class XmlElement
{
public:
    XmlElement();
    ~XmlElement();

    const char *GetName();
    int ChildCount();
    int AttrCount();
    XmlElement* ChildAt(int idx);
    XmlAttr AttrAt(int idx);
    XmlElement *GetChild(const char * name);
    const char *GetAttr(const char* name);
    const char *GetText();

private:
    friend class XmlDocument;
    void Load(char *pData, char *pSs);
    int GetDataLen();

private:
    char *m_pData;
    char *m_pSs;
    short m_sChildSize;
    short m_sAttrSize;
    bool m_bHasTxt;
    XmlElement *m_pChildren;
};

#endif // XMLELEMENT_H
