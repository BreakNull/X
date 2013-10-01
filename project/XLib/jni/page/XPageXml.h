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
    XPageXml();
    virtual ~XPageXml();

    bool LoadBuffer(char *pXmlData, int len);
    bool LoadFile(const char *pFileName);

    XWidget *CreateMainView(XPage *page);
    XWidget *CreateRefView(const char *pRefName, XPage *page);

protected:
    void Parse();
    void ParseStyle(XmlElement *pElem);

    void ParseAttr(XWidget *pw, XmlElement *pElem, XPage *page);
    void ParsePageAttr(XPage *pw, XmlElement *pElem);
    void MergeAttr(XmlElement *pE, vector<XStyleAttr> &vec);

    void ParseContainer(XWidget *pw, XmlElement *pElem, XPage *page);
    void ParseWidget(XWidget *pw, XmlElement *pElem, XPage *page);

    XmlDocument *m_pDoc;
    XStyle *m_pStyle;
};

#endif // XMLPARSER_H
