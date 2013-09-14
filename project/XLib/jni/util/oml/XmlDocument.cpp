#include "XmlDocument.h"
#include <stdio.h>
#include <string.h>

struct XmlHead
{
    unsigned short magic;
    unsigned short version;
    unsigned short ss;
    unsigned short len;
};

#define MAGIC 0xeaab

XmlDocument::XmlDocument()
{
    m_pBuf = NULL;
    m_iLen = 0;
    m_pRoot = NULL;
    m_pSs = NULL;
}

void XmlDocument::LoadFile(const char *pFileName)
{
    FILE *pf = fopen(pFileName, "rb");
    if (!pf) {
        return;
    }
    fseek(pf, 0, SEEK_END);
    m_iLen = (int)ftell(pf);
    m_pBuf = new char[m_iLen];
    fseek(pf, 0, SEEK_SET);
    fread(m_pBuf, 1, m_iLen, pf);
    fclose(pf);
    Parse();
}

void XmlDocument::Parse()
{
    XmlHead *hd = (XmlHead*)m_pBuf;
    if (hd->magic != MAGIC) {
        return;
    }
    m_pSs = m_pBuf + hd->ss;
    m_pRoot = new XmlElement();
    m_pRoot->Load(m_pBuf + sizeof(XmlHead), m_pSs);
}

void XmlDocument::LoadBuffer(char *pBuf, int iLen)
{

}

XmlElement* XmlDocument::GetRoot()
{
    return m_pRoot;
}

XmlDocument::~XmlDocument()
{
    delete[] m_pBuf;
    delete m_pRoot;
}
