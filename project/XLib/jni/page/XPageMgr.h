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
    enum AnimType {
        A_USE_HISTORY = -1, //often used for loadExistPage
        A_NONE = 0,
        A_LEFT_IN_RIGHT_OUT = 1,
        A_RIGHT_IN_LEFT_OUT = 2,
        A_BOTTOM_IN_TOP_OUT = 3,
        A_TOP_IN_BOTTOM_OUT = 4
    };

    static XPageMgr *Instance();

    void LoadNewPage(const char *pName, AnimType anim = A_NONE);
    void LoadExistPage(const char *pName, AnimType anim = A_NONE);
    void LoadExistPage(int pageId, AnimType anim = A_NONE);
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
