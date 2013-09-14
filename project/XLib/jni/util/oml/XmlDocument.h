#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include "XmlElement.h"

class XmlDocument
{
public:
    XmlDocument();
    void LoadFile(const char *pFileName);
    void LoadBuffer(char *pBuf, int iLen);
    XmlElement* GetRoot();
    ~XmlDocument();

private:
    void Parse();

private:
    char *m_pBuf;
    int m_iLen;
    XmlElement *m_pRoot;
    char *m_pSs;
};

#endif // XMLDOCUMENT_H
