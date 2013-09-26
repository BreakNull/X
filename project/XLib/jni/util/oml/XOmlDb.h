#ifndef XOMLDB_H
#define XOMLDB_H

#include <stdio.h>
#include <string>
class DbHeadItem;

class XOmlDb
{
public:
    static XOmlDb *Instance();
    //read content from oml db file, you should free the return value
    void *ReadContent(const char *pName, int *pLen);

private:
    XOmlDb();
    bool ReadHead(FILE *pf);
    DbHeadItem *Find(const char *pName);
    std::string GetOmlDbFilePath();
    void CopyOmlDbFile();

    static XOmlDb *s_pIns;
    int m_iNum;
    DbHeadItem *m_pItems;
    bool m_bInited;
};

#endif // OMLDB_H
