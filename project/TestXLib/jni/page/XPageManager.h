#ifndef XPAGEMANAGER_H
#define XPAGEMANAGER_H

class XPage;
#include <map>
using namespace std;

/**
 * 页面管理器
 * 管理页面的历史，删除历史页面，跳转到新或旧页面等
 */
class XPageManager
{
public:
    static XPageManager *Instance();

    void AddPage(int id, XPage *p);
    XPage *RemovePage(int id);
    XPage *GetPage(int id);

private:
    XPageManager();
    static XPageManager *s_ins;
    std::map<int, XPage*> m_cPages;
};

#endif // PAGEMANAGER_H
