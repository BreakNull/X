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
    virtual ~XWidget();

    //每个Widget的子类都需要有一个static的New函数
    WIDGET_NEW(XWidget)

    enum FLAGS {
        F_NONE = 0,
        F_NEW_REF =  1      //used for new a global ref for java object
    };

    /*
     * 创建出对应到平台的实际widget
     * 在创建一个带有ID的widget时， 需要将id设置到实际平台widget的tag中
     */
    virtual void Create(int flags);

    virtual void SetProperty(const string &name, const XVariant &v);
    virtual XVariant GetProperty(const string &name);

    bool IsRoot();
    void SetRoot(bool b);

    /*
     *是否是一个容器，容器可以包含子Widget
     */
    virtual bool IsContainer();

    XPage *GetXPage();

    void *GetChild(const string &id);
    int GetChildCount();
    void *GetChildAt(int idx);

    void *GetRealWidget() {return m_pRealWidget;}
    void SetRealWidget(void *p) {m_pRealWidget = p;}

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
    XPage *m_pPage;
    int m_iFlags;
};

#endif // WIDGET_H
