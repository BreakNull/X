#ifndef XPAGEXML_H
#define XPAGEXML_H

class TiXmlDocument;
class TiXmlElement;
class XWidget;
class XPage;
class TiXmlAttribute;
#include "XStyle.h"

class XPageXml
{
public:
    XPageXml(XPage *p);
    virtual ~XPageXml();
    virtual XPageXml *Clone(XPage *p);

    bool LoadData(char *pXmlData);
    bool LoadFile(const char *pFileName);
    virtual void Parse();
    XWidget *GetMainView();

protected:
    void ParseMainView(TiXmlElement *pElem);
    void ParseStyle(TiXmlElement *pElem);

    void ParseAttr(XWidget *pw, TiXmlElement *pElem);
    void ParseAttr(XPage *pw, TiXmlElement *pElem);
    void MergeAttr(TiXmlElement *pE, vector<XStyleAttr> &vec);
    virtual void ParseContainer(XWidget *pw, TiXmlElement *pElem);
    virtual void ParseWidget(XWidget *pw, TiXmlElement *pElem);
    void ParseButton(XWidget *pw, TiXmlElement *pElem);
    void ParseLabel(XWidget *pw, TiXmlElement *pElem);

    TiXmlDocument *m_pDoc;
    XPage *m_page;
    XWidget *m_pMainView;
    XStyle *m_pStyle;
};

#endif // XMLPARSER_H
