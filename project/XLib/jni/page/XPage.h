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
    virtual ~XPage();

    //每个Page的子类都需要有一个static的New函数
    PAGE_NEW(XPage)

    //返回创建出来的根Widget
    virtual XWidget *OnCreate();
    virtual void OnDestroy();

    virtual void OnStart();
    virtual void OnStop();
    virtual void OnBackPressed();

//    virtual void OnResume() {}
//    virtual void OnPause() {}

    void *GetRealPage() {return m_pRealPage;}
    void SetRealPage(void *p) {m_pRealPage = p;}
    string &GetName() {return m_cName;}
    int GetId() {return m_id;}
    XWidget *GetRoot() {return m_pRoot;}

    /**
     * 通过id来查找widget，返回平台相关的widget
     * Note: 你不应该缓存此函数的返回值，否则在某些android平台上可能会存在问题
     */
    void *FindById(const string &id, XWidget *parent = NULL);

    //设置标题栏上的标题
    void SetTitle(const string &title);
    void SetProperty(const string &name, const XVariant &val);
    int GetStyle() {return m_iStyle;}

    /**
     * 设置监听器
     * @param name 监听器名字，多个名字之间用|分隔. 如： "click|press"
     */
    void SetListener(XWidget *pw, const string &name);
    void ClearListener(XWidget *pw, const string &name);

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
