#ifndef XPAGEMANAGER_H
#define XPAGEMANAGER_H

class XPage;
#include <vector>
using namespace std;

/**
 * 页面管理器
 * 管理页面的历史，删除历史页面，跳转到新或旧页面等
 */
class XPageMgr
{
public:
    enum ANIM {
        A_USE_HISTORY = -1, //often used for loadExistPage
        A_NONE = 0,
        A_LEFT_IN = 	1 << 0,
        A_LEFT_OUT = 	1 << 1,
        A_RIGHT_IN = 	1 << 2,
        A_RIGHT_OUT = 	1 << 3,
        A_TOP_IN = 		1 << 4,
        A_TOP_OUT = 	1 << 5,
        A_BOTTOM_IN = 	1 << 6,
        A_BOTTOM_OUT = 	1 << 7,
        A_FADE_IN = 	1 << 8,
        A_FADE_OUT = 	1 << 9,

        A_MASK_IN = 0x55555555,
        A_MASK_OUT = 0xAAAAAAAA
    };

    enum FLAGS {
        F_NONE = 0,
        F_NO_HISTORY = 1
    };

    static XPageMgr *Instance();

    void LoadNewPage(const char *pName, int anim = A_NONE, int flags = F_NONE);
    void LoadExistPage(const char *pName, int anim = A_NONE);
    void LoadExistPage(int pageId, int anim = A_NONE);
    void GoBack();

    int IndexOf(int id);
    int IndexOf(const char *pName);
    //all page's count
    int Count();
    XPage *At(int idx);
    XPage *Get(int id);
    XPage *FindInAll(int id);
    void Remove(int idx);

private:
    class PageInfo {
    public:
        PageInfo() {Reset();}
        void Reset();
        XPage *m_page;
        int m_iAnim;
        int m_iFlags;
    };
    int GetReverseAnim(int anim);
    int GetInAnim(int anim) {return anim & A_MASK_IN;}
    int GetOutAnim(int anim) {return anim & A_MASK_OUT;}
    friend class XJniPage;
    void AddPage(XPage *p);
    XPageMgr();
    static XPageMgr *s_ins;
    vector<PageInfo> m_cPages;
    vector<XPage*> m_cDelPages;
    PageInfo m_curPi;
};

#endif // PAGEMANAGER_H
