#ifndef XSTYLE_H
#define XSTYLE_H

#include <string.h>
#include <vector>
//#include <map>
//#include <string>
using namespace std;

struct XStyleAttr {
    XStyleAttr(){m_pName = m_pValue = NULL;}
    const char *m_pName;
    const char *m_pValue;
};

class XStyleSpec {
public:
    XStyleSpec(char *pName);
    ~XStyleSpec();

    vector<XStyleAttr> &GetAttrs() {return m_attrs;}
    char *GetName() {return m_pName;}
    int IndexOf(const char *pAttrName);
    void Add(char *pName, char *pVal);
    void Reset() {m_attrs.clear(); m_pName = NULL;}
    void Merge(XStyleSpec *pMiro);

private:
    vector<XStyleAttr> m_attrs;
    char *m_pName;
};

class XStyle
{
public:
    XStyle(XStyle *parent, const char *pName);
    ~XStyle();

    /**
     * @param pData The data will be change
     */
    void LoadData(char *pData);
    void LoadFile(const char *pFileName);
    vector<XStyleSpec*> &GetSpecs() {return m_specs;}
    const char *GetName() {return m_pName;}

    /**
     * Note: The returned XStyleSpec, you can't delete it.
     *       Its a tmp XStyleSpec object, this means you can't save it to used for later.
     */
    XStyleSpec *Search(const char *pTagName, const char *pClassName, const char *pId);

protected:
    void Parse();
    bool IsEnd(char *p, char *pe = NULL);
    char *NextCR(char *p);
    bool IsSpace(char p) {return p == ' ' || p == '\t' || p == '\r' || p == '\n';}
    char *SkipSpace(char *p);
    char *Sq(char *p);
    char *Eq(char *p);
    bool ParseQu(char *pName, char *pS, char *pE);
    void ParseAt(char *ps);
    void TrimRight(char *p);
    char *Mh(char *p);
    char *SkipComment(char *p);
    XStyleSpec *FindByTag(const char *p);
    XStyleSpec *FindByClass(const char *p);
    XStyleSpec *FindById(const char *p);
    //XStyleSpec *FindInCache(const char *pTagName, const char *pClassName);
    //string GenKey(const char *pTagName, const char *pClassName);

private:
    XStyle *m_parent;
    const char *m_pName;
    char *m_pData;
    int m_iDataLen;
    vector<XStyleSpec*> m_specs;
    bool m_bCache;
    bool m_bFree;
    //map<string, XStyleSpec*> m_cache;
};

#endif // XSTYLE_H
