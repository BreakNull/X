#ifndef XPAGEMANAGER_H
#define XPAGEMANAGER_H

class XPage;
#include <map>
using namespace std;

/**
 * 页面管理器
 * 管理页面的历史，删除历史页面，跳转到新或旧页面等
 */
class XPageMgr
{
public:
    static XPageMgr *Instance();

    void LoadNewPage(const char *pName, int anim);
    void LoadExistPage(const char *pName, int anim);
    void LoadExistPage(int pageId, int anim);
    void GoBack();

    void AddPage(int id, XPage *p);
    XPage *RemovePage(int id);
    XPage *GetPage(int id);

private:
    XPageMgr();
    static XPageMgr *s_ins;
    std::map<int, XPage*> m_cPages;
};

#endif // PAGEMANAGER_H
