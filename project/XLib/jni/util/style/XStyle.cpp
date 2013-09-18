#include "XStyle.h"
#include <string.h>
#include "XLog.h"
#include <stdio.h>
#include "XResource.h"

extern void print(XStyleSpec *p);

XStyleSpec::XStyleSpec(char *pName)
    :m_pName(pName)
{
}

XStyleSpec::~XStyleSpec()
{
}


int XStyleSpec::IndexOf(const char *pAttrName)
{
    if (NULL == pAttrName)
        return NULL;
    for (int i = 0; i < m_attrs.size(); ++i) {
        XStyleAttr &attr = m_attrs.at(i);
        if (attr.m_pName && strcmp(attr.m_pName, pAttrName) == 0) {
            return i;
        }
    }
    return -1;
}

void XStyleSpec::Add(char *pName, char *pVal)
{
    XStyleAttr attr;
    attr.m_pName = pName;
    attr.m_pValue = pVal;
    m_attrs.push_back(attr);
}

void XStyleSpec::Merge(XStyleSpec *pMiro)
{
    if (NULL == pMiro)
        return;
    for (int i = 0; i < pMiro->m_attrs.size(); ++i) {
        XStyleAttr attr = pMiro->m_attrs.at(i);
        if (IndexOf(attr.m_pName) == -1) {
            m_attrs.push_back(attr);
        }
    }
}

//--------------------------------------------

XStyle::XStyle(XStyle *parent, const char *pName)
    :m_pData(NULL)
    ,m_iDataLen(0)
    ,m_bCache(false)
{
    m_parent = parent;
    m_pName = pName;
}

XStyle::~XStyle()
{
    if (m_pData) {
        free(m_pData);
    }
    for (int i = 0; i < m_specs.size(); ++i) {
        delete m_specs.at(i);
    }
}

void XStyle::LoadData(char *pData)
{
    if (NULL == pData) {
        return;
    }
    m_pData = pData;
    m_iDataLen = strlen(pData);
    Parse();
}

void XStyle::LoadFile(const char *pFileName)
{
    //LOGD("Load style file '%s'", pFileName);
    if (NULL == pFileName) {
        return;
    }
    string path("loc:");
    path += pFileName;
    XResource res(path);
    m_pData = (char*)res.GetData();
    m_iDataLen = res.GetDataLen();
    Parse();
}

void XStyle::Parse()
{
    char *ps = m_pData;
    char *pe = ps;

    //parse '@'
    while (true) {
        if (IsEnd(ps)) {
            break;
        }
        ps = SkipSpace(ps);
        ps = SkipComment(ps);
        if (NULL == ps) {
            return;
        }
        if (*ps != '@') {
            break;
        }
        pe = NextCR(ps);
        if (pe == NULL || IsEnd(pe)) {
            return;
        }
        ParseAt(ps);
        ps = pe + 1;
    }

    //parse style spec
    while (true) {
        ps = SkipSpace(ps);
        ps = SkipComment(ps);
        if (NULL == ps) {
            return;
        }
        if (IsEnd(ps)) {
            break;
        } else {
            char *sq = Sq(ps);
            if (sq == NULL) {
                if (*ps == 0) {
                    break;
                } else {
                    //error
                    LOGE("Error: %s", ps);
                    break;
                }
            }
            ++sq;
            char *eq = Eq(sq);
            if (eq == NULL) {
                //error
                LOGE("Error: %s", ps);
                break;
            }
            if (ParseQu(ps, sq, eq)) {
                ps = eq + 1;
            } else {
                break;
            }
        }
    }
}

bool XStyle::IsEnd(char *p, char *pe)
{
    if (pe == NULL)
        pe = m_pData + m_iDataLen;
    return p >= pe;
}

char *XStyle::NextCR(char *p)
{
    if (IsEnd(p))
        return NULL;
    char *px = strchr(p, '\n');
    if (NULL != px) {
        *px = '\0';
    }
    char *pm = (px == NULL ? (p+strlen(p) - 1) : (px - 1));
    while ((pm >= m_pData) && IsSpace(*pm)) {
        *pm = 0;
        --pm;
    }
    return px;
}

char *XStyle::SkipSpace(char *p)
{
    while (IsSpace(*p)) {
        ++p;
    }
    return p;
}

char *XStyle::Sq(char *p)
{
    char *px = strchr(p, '{');
    if (NULL != px) {
        *px = '\0';
    }
    return px;
}

char *XStyle::Eq(char *p)
{
    char *px = strchr(p, '}');
    if (NULL != px) {
        *px = '\0';
    }
    return px;
}

void XStyle::ParseAt(char *ps)
{
    TrimRight(ps);
    ++ps;
    if (strcmp(ps, "cache") == 0) {
        m_bCache = true;
    }
}

bool XStyle::ParseQu(char *pName, char *pS, char *pE)
{
    pName = SkipSpace(pName);
    TrimRight(pName);
    char *ps = pS;
    char *pe = NULL;

    if (*pName == 0) {
        //no name
        return false;
    }
    XStyleSpec *pSpec = new XStyleSpec(pName);

    while (true) {
        ps = SkipSpace(ps);
        pe = NextCR(ps);

        if (IsEnd(pe, pE) || IsEnd(ps, pE)) {
            break;
        }
        if (pe == ps || *ps == '\0') {
            //empty line
            continue;
        }

        char *pm = Mh(ps);
        if (pm == NULL) {
            LOGE("Error: %s", ps);
            goto _err;
        }
        TrimRight(ps);
        pm = SkipSpace(pm);
        TrimRight(pm);
        pSpec->Add(ps, pm);
        if (pe == NULL)
            break;
        ps = pe + 1;
    }
    m_specs.push_back(pSpec);
    return true;

_err:
    delete pSpec;
    return false;
}

void XStyle::TrimRight(char *p)
{
    char *pe = p + strlen(p) - 1;
    while (pe >= p && IsSpace(*pe)) {
        *pe = 0;
        --pe;
    }
}

char *XStyle::Mh(char *p)
{
    char *px = strchr(p, ':');
    if (px) {
        *px = 0;
        ++px;
    }
    return px;
}

char *XStyle::SkipComment(char *p)
{
    while (true) {
        p = SkipSpace(p);
        if (*p != '/') {
            return p;
        }
        if (p[1] == '*') {
            char *px = strstr(p + 1, "*/");
            if (px == NULL) {
                LOGE("The style [%s] has no matched '*/'", p);
                return NULL;
            }
            p = px + 2;
        } else if (p[1] == '/') {
            char *px = strchr(p + 1, '\n');
            if (px == NULL) {
                return NULL;
            }
            p = px + 1;
        } else {
            LOGE("The style [%s] has error, invalid '/'", p);
            return NULL;
        }
    }
    return p;
}

static XStyleSpec s_cur(NULL);

XStyleSpec *XStyle::FindByTag(const char *p)
{
    for (int i = 0; i < m_specs.size(); ++i) {
        XStyleSpec *px = m_specs.at(i);
        if (strcmp(px->GetName(), p) == 0) {
            return px;
        }
    }
    return NULL;
}

XStyleSpec *XStyle::FindByClass(const char *p)
{
    char bn[40] = {0};
    sprintf(bn, ".%s", p);
    return FindByTag(bn);
}

XStyleSpec *XStyle::FindById(const char *p)
{
    char bn[40] = {0};
    sprintf(bn, "#%s", p);
    return FindByTag(bn);
}

XStyleSpec *XStyle::Search(const char *pTagName, const char *pClassName, const char *pId)
{
    int num = 0;
    XStyle *paths[20] = {0};
    XStyle *ps = this;

    s_cur.Reset();
    for (; NULL != ps; ps = ps->m_parent) {
        paths[num++] = ps;
    }

    if (NULL != pId) {
        for (int i = 0; i < num; ++i) {
            XStyleSpec *pxss = paths[i]->FindById(pId);
            if (pxss) {
                s_cur.Merge(pxss);
            }
        }
    }

    /*
    if (pTagName || pClassName) {
        XStyleSpec *pxss = FindInCache(pTagName, pClassName);
        if (pxss) {
            s_cur.Merge(pxss);
            return &s_cur;
        }
    }
    */

    if (NULL != pClassName) {
        for (int i = 0; i < num; ++i) {
            XStyleSpec *pxss = paths[i]->FindByClass(pClassName);
            if (pxss) {
                s_cur.Merge(pxss);
            }
        }
    }

    if (NULL != pTagName) {
        for (int i = 0; i < num; ++i) {
            XStyleSpec *pxss = paths[i]->FindByTag(pTagName);
            if (pxss) {
                s_cur.Merge(pxss);
            }
        }
    }

    return &s_cur;
}

/*
XStyleSpec *XStyle::FindInCache(const char *pTagName, const char *pClassName)
{
    string key = GenKey(pTagName, pClassName);
    if (key.empty()) {
        return NULL;
    }

    map<string, XStyleSpec*>::iterator it = m_cache.find(key);
    if (it == m_cache.end()) {
        return NULL;
    }
    return (*it).second;
}

string XStyle::GenKey(const char *pTagName, const char *pClassName)
{
    string key;
    if (pTagName) {
        key = pTagName;
    }
    if (pClassName) {
        key.append("/.");
        key.append(pClassName);
    }
    return key;
}
*/

