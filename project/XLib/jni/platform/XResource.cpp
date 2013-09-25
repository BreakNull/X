#include "XResource.h"
#include <string.h>
#include <stdio.h>
#include "XApp.h"
#include "XPlatform.h"
#include "XLog.h"

XResource::XResource(const string &url)
    :m_iDatLen(0)
    ,m_pDat(NULL)
    ,m_eDt(DT_NONE)
    ,m_bLoaded(false)
{
    const char *p = url.c_str();
    if (memcmp("plt:", p, 4) == 0) {
        m_eDt = DT_PLT;
        m_cAbsPath = p + 4;
    } else if (memcmp("loc:", p, 4) == 0) {
        m_eDt = DT_LOC;
        if (p[4] == '/') {
            m_cAbsPath = p + 4;
        } else {
            p = p + 4;
            m_cAbsPath = XApp::Instance()->GetWorkDir() + "/" + p;
        }
    }
}

void *XResource::GetData()
{
    Load();
    return m_pDat;
}

int XResource::GetDataLen()
{
    Load();
    return m_iDatLen;
}

void XResource::Load()
{
    if (m_bLoaded) {
        return;
    }
    m_bLoaded = true;
    if (m_eDt == DT_PLT) {
        LoadFromPlt();
    } else if (m_eDt == DT_LOC) {
        LoadFromFile();
    }
}

void XResource::LoadFromFile()
{
    FILE *f = fopen(m_cAbsPath.c_str(), "rb");
    bool err = false;
    if (!f) {
        LOGE("Open file '%s' fail.", m_cAbsPath.c_str());
        return;
    }
    fseek(f, 0, SEEK_END);
    m_iDatLen = ftell(f);
    if (m_iDatLen <= 0) {
        m_iDatLen = 0;
        return;
    }
    fseek(f, 0, SEEK_SET);
    m_pDat = malloc(m_iDatLen + 1);
    int iRead = 0;
    while (iRead < m_iDatLen) {
        int x = fread((char*)m_pDat + iRead, 1, m_iDatLen - iRead, f);
        iRead += x;
        if (x == 0)
            break;
        else if (x < 0) {
            err = true;
            break;
        }
    }
    if (err) {
        free(m_pDat);
        m_pDat = NULL;
        m_iDatLen = 0;
    } else {
        char *p = (char*)m_pDat;
        p[m_iDatLen] = 0;
    }
}

void XResource::LoadFromPlt()
{
    m_pDat = XPlatform::Instance()->GetPlatformRes(m_cAbsPath.c_str(), &m_iDatLen);
}
