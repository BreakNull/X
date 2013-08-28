#ifndef XPLATFORM_H
#define XPLATFORM_H

class XWidget;
class XResource;
class XPage;
#include "XUiThread.h"
#include <string>
using namespace std;

class XPlatform
{
public:
    static XPlatform *Instance();
    virtual ~XPlatform() {}

    /*
     * 创建出与平台相关的Widget
     */
    virtual void *NewButton(XPage *p) = 0;
    virtual void *NewLabel(XPage *p) = 0;
    virtual void *NewLineLayout(XPage *p) = 0;

    virtual string GetId(XWidget *p) = 0;
    virtual void SetId(XWidget *p, const string &id) = 0;

    //virtual XResource *GetBgImg(XWidget *p) = 0;
    virtual void SetBgImg(XWidget *p, XResource *r) = 0;

    //virtual int GetBgColor(XWidget *p) = 0;
    virtual void SetBgColor(XWidget *p, int color) = 0;

    virtual bool IsClickable(XWidget *p) = 0;
    virtual void SetClickable(XWidget *p, bool b) = 0;

    virtual bool IsFocusable(XWidget *p) = 0;
    virtual void SetFocusable(XWidget *p, bool b) = 0;

    virtual void SetPadding(XWidget *p, int left, int top, int right, int bottom) = 0;

    virtual bool IsVisible(XWidget *pb) = 0;
    virtual void SetVisible(XWidget *p, bool b) = 0;

    //virtual int GetMinWidth(XWidget *p) = 0;
    virtual void SetMinWidth(XWidget *p, int w) = 0;

    //virtual int GetMinHeight(XWidget *p) = 0;
    virtual void SetMinHeight(XWidget *p, int h) = 0;

    //virtual int GetX(XWidget *p) = 0;
    //virtual int GetY(XWidget *p) = 0;

    virtual int GetPaddingLeft(XWidget *p) = 0;
    virtual int GetPaddingRight(XWidget *p) = 0;
    virtual int GetPaddingTop(XWidget *p) = 0;
    virtual int GetPaddingBottom(XWidget *p) = 0;

    virtual int GetWidth(XWidget *p) = 0;
    virtual int GetHeight(XWidget *p) = 0;

    virtual void SetTitle(XPage *p, const string &title) = 0;

    //---------Button----------
    virtual void SetButtonText(XWidget *p, const char *pcTxt) = 0;
    virtual string GetButtonText(XWidget *p) = 0;

    //-------LineLayout--------
    virtual void SetOrientation(XWidget *p, bool vertical) = 0;

    virtual void AddChild(XWidget *p, XWidget *c, int idx) = 0;

    //------ui thread---------
    virtual bool PostRunnable(XUiThread::Runnable r) = 0;
    virtual bool PostRunnable(XUiThread::Runnable r, int delayMs) = 0;

protected:
    XPlatform();

private:
    static XPlatform *s_ins;
};

#endif // PLATFORM_H
