#ifndef XPAGE_H
#define XPAGE_H

#include <string>
class XWidget;
class XMenu;
class XPageXml;
class XVariant;

using namespace std;

#define PAGE_NEW(x) static XPage *New(void *p, const string &n, int id) {return new x(p,n,id);}

/**
 * 页面，所有的页面都继承自此类
 */
class XPage
{
public:
    enum STYLE {
        S_NO_TITLE = (1 << 0),
        S_FULL_SCREEN = (1 << 1)
    };

    XPage(void *pRealPage, const string &name, int id);

    //每个Page的子类都需要有一个static的New函数
    PAGE_NEW(XPage)

    //返回创建出来的根Widget
    virtual XWidget *OnCreate();
    virtual void OnDestroy();

    virtual void OnStart();
    virtual void OnStop();

//    virtual void OnResume() {}
//    virtual void OnPause() {}

    void *GetRealPage() {return m_pRealPage;}
    string &GetName() {return m_cName;}
    int &GetId() {return m_id;}
    XWidget *FindById(const string &id, XWidget *parent = NULL);

    //设置标题栏上的标题
    void SetTitle(const string &title);
    virtual void SetProperty(const string &name, const XVariant &val);
    int GetStyle() {return m_iStyle;}

    virtual void OnClick(const std::string &widgetId) {}
    // 返回true时，显示此菜单， 否则不显示。此函数只会被调用一次的
    virtual bool OnCreateOptionsMenu(XMenu *pMenu);
    virtual void OnTimeChanged(const std::string &widgetId, int hour, int minute) {}
    virtual void OnDateChanged(const std::string &widgetId, int y, int m, int d) {}
    virtual void OnOptionsItemSelected(int menuId) {}

protected:
    int m_id;           //页面id
    string m_cName;     //页面类型名称
    void *m_pRealPage;  //实际的平台相关的页面
    XPageXml *m_pXml;
    XWidget *m_pRoot;
    int m_iStyle;       //样式
};

#endif // PAGE_H
