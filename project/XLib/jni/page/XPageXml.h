#ifndef XPAGEXML_H
#define XPAGEXML_H

class XmlDocument;
class XmlElement;
class XWidget;
class XPage;
class XmlAttr;
#include "XStyle.h"

class XPageXml
{
public:
    XPageXml(XPage *p);
    virtual ~XPageXml();
    virtual XPageXml *Clone(XPage *p);

    bool LoadBuffer(char *pXmlData, int len);
    bool LoadFile(const char *pFileName);
    virtual void Parse();
    XWidget *GetMainView();

protected:
    void ParseMainView(XmlElement *pElem);
    void ParseStyle(XmlElement *pElem);

    void ParseAttr(XWidget *pw, XmlElement *pElem);
    void ParseAttr(XPage *pw, XmlElement *pElem);
    void MergeAttr(XmlElement *pE, vector<XStyleAttr> &vec);
    virtual void ParseContainer(XWidget *pw, XmlElement *pElem);
    virtual void ParseWidget(XWidget *pw, XmlElement *pElem);

    XmlDocument *m_pDoc;
    XPage *m_page;
    XWidget *m_pMainView;
    XStyle *m_pStyle;
};

#endif // XMLPARSER_H
