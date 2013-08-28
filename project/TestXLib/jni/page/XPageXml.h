#ifndef XPAGEXML_H
#define XPAGEXML_H

class TiXmlDocument;
class TiXmlElement;
class XWidget;
class XPage;

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
    void ParseContainer(XWidget *pw, TiXmlElement *pElem);
    void ParseWidget(XWidget *pw, TiXmlElement *pElem);
    void ParseButton(XWidget *pw, TiXmlElement *pElem);
    void ParseLabel(XWidget *pw, TiXmlElement *pElem);
    virtual void ParseUnknowWidget(XWidget *, TiXmlElement *) {}

    TiXmlDocument *m_pDoc;
    XPage *m_page;
    XWidget *m_pMainView;
};

#endif // XMLPARSER_H
