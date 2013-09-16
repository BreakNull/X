#include "XmlDocument.h"
#include <stdio.h>
#include <string.h>
#include "XLog.h"

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

bool XmlDocument::LoadFile(const char *pFileName)
{
    FILE *pf = fopen(pFileName, "rb");
    if (!pf) {
        LOGE("Open file '%s' error", pFileName);
        return false;
    }
    fseek(pf, 0, SEEK_END);
    m_iLen = (int)ftell(pf);
    m_pBuf = new char[m_iLen];
    fseek(pf, 0, SEEK_SET);
    int i = 0;
    while (i != m_iLen) {
        int r = fread(m_pBuf, 1, m_iLen-i, pf);
        if (r <= 0) {
            break;
        }
        i += r;
    }
    fclose(pf);
    if (i == m_iLen && m_iLen != 0) {
        return Parse();
    }

    LOGE("Read file '%s' error, file length=%d", pFileName, m_iLen);
    return false;
}

bool  XmlDocument::Parse()
{
    XmlHead *hd = (XmlHead*)m_pBuf;
    if (hd->magic != MAGIC) {
        LOGE("file magic number error");
        return false;
    }
    if (m_iLen != hd->len) {
        LOGE("file length error,header's len=%d, file real's len=%d", hd->len, m_iLen);
        return false;
    }
    m_pSs = m_pBuf + hd->ss;
    m_pRoot = new XmlElement();
    m_pRoot->Load(m_pBuf + sizeof(XmlHead), m_pSs);
    return true;
}

bool XmlDocument::LoadBuffer(char *pBuf, int iLen)
{
    if (pBuf == NULL || iLen <= 0) {
        LOGE("ilegal arguments. pBuf=%p, iLen=%d", pBuf, iLen);
        return false;
    }
    m_iLen = iLen;
    m_pBuf = pBuf;
    return Parse();
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
