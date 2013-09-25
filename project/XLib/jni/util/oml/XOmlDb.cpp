#include "XOmlDb.h"
#include <string.h>
#include <string>
#include "XLog.h"
#include "XApp.h"

using namespace std;

#define MAGIC 0x3abdef97

struct DbHead
{
    int m_iMagic;
    int m_iNum;
};

struct DbHeadItem
{
    int m_iPos;
    int m_iLen;
    char m_pcName[24];
};

XOmlDb *XOmlDb::s_pIns = NULL;

XOmlDb::XOmlDb()
    :m_iNum(0)
    ,m_pItems(NULL)
{
}

XOmlDb *XOmlDb::Instance()
{
    if (!s_pIns) {
        s_pIns = new XOmlDb();
    }
    return s_pIns;
}

void *XOmlDb::ReadContent(const char *pName, int *pLen)
{
    if (pName == NULL || pLen == NULL) {
        LOGE("Invalid params pName=%p, pLen=%p", pName, pLen);
        return NULL;
    }
    string dbName = XApp::Instance()->GetOmlDbFilePath();
    FILE *pf = fopen(dbName.c_str(), "rb");
    if (!pf) {
        LOGE("open file %s error", dbName.c_str());
        return NULL;
    }
    if (!ReadHead(pf)) {
        return NULL;
    }

    DbHeadItem *pIt = Find(pName);
    if (!pIt) {
        LOGE("not find page '%s'", pName);
        fclose(pf);
        return NULL;
    }
    *pLen = pIt->m_iLen;
    fseek(pf, pIt->m_iPos, SEEK_SET);
    void *pBuf = malloc(pIt->m_iLen);
    fread(pBuf, 1, pIt->m_iLen, pf);
    fclose(pf);

    return pBuf;
}

bool XOmlDb::ReadHead(FILE *pf)
{
    if (NULL != m_pItems) {
        return true;
    }
    DbHead head = {0};
    fread(&head, sizeof(head), 1, pf);
    if (head.m_iMagic != MAGIC) {
        LOGE("magic error");
        return false;
    }
    if (head.m_iNum < 0 || head.m_iNum > 100) {
        LOGE("num error");
        return false;
    }
    m_iNum = head.m_iNum;
    m_pItems = new DbHeadItem[m_iNum];
    fread(m_pItems, sizeof(DbHeadItem), m_iNum, pf);
    return true;
}

DbHeadItem *XOmlDb::Find(const char *pName)
{
    for (int i = 0; i < m_iNum; ++i) {
        if (strcmp(pName, m_pItems[i].m_pcName) == 0) {
            return m_pItems + i;
        }
    }
    return NULL;
}
