#ifndef XWIDGET_H
#define XWIDGET_H

#include <string>
#include <vector>
#include <map>
#include "XVariant.h"

using namespace std;
class XPage;

#define WIDGET_NEW(x) static XWidget *New(XPage *p) {return new x(p);}

/**
 * Widget *pw = new XXX();
 * pw->Create();
 *
 *
 *
 * 支持的property有：
 *      id: string
 *      alpha: float 透明度 0.0 ~ 1.0  0.0为完全透明
 *      bgimg: resource  背景图片
 *      bgcolor: 背景色
 *      clickable: boolean 是否启用click事件
 *      focusable: boolean 是否可以获得焦点
 *      padding: int(left),int(top),int(right),int(bottom) 内边距
 *      visible: boolean 是否可见
 *      minw: int 最小宽度
 *      minh: int 最小高度
 *      x: int
 *      y: int
 *      w: int 宽度, only getter
 *      h: int 高度, only getter
 */
class XWidget
{
public:
    XWidget(XPage *p);

    //每个Widget的子类都需要有一个static的New函数
    WIDGET_NEW(XWidget)

    /*
     * 创建出对应到平台的实际widget
     * 在创建一个带有ID的widget时， 需要将id设置到实际平台widget的tag中
     */
    virtual void Create();

    virtual void SetProperty(XPage *p, const string &name, const XVariant &v);
    virtual XVariant GetProperty(const string &name);
    virtual void SetListener(XPage *page, const string &name);

    bool IsRoot();
    void SetRoot(bool b);

    /*
     *是否是一个容器，容器可以包含子Widget
     */
    virtual bool IsContainer();

    string GetId();

    XWidget *GetRootWidget();
    XWidget *GetParent();
    void SetParent(XWidget *parent);

    XWidget *GetChild(const string &id);
    vector<XWidget*> *GetChildren();
    void *GetRealWidget() {return m_pRealWidget;}

    /*
     * 如果idx小于0， 则表示将pChild添加到容器的未尾
     */
    void AddChild(XWidget *pChild, int idx = -1);

private:
    //disable
    XWidget(const XWidget&);
    XWidget operator=(const XWidget&);

protected:
    void *m_pRealWidget;    //实际的Widget
    string m_cId;           //Widget的ID
    vector<XWidget*> *m_pChildren;  //子Widget
    XWidget *m_pParent;
    XPage *m_pPage;
};

#endif // WIDGET_H
