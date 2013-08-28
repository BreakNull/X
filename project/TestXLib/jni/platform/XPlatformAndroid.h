#ifndef XPLATFORMANDROID_H
#define XPLATFORMANDROID_H

#include "XPlatform.h"

class XPlatformAndroid : public XPlatform
{
public:
    XPlatformAndroid();

    virtual void *NewButton(XPage *p);
    virtual void *NewLabel(XPage *p);

    virtual string GetId(XWidget *p);
    virtual void SetId(XWidget *p, const string &id);

    //virtual XResource *GetBgImg(XWidget *p);
    virtual void SetBgImg(XWidget *p, XResource *r);

    //virtual int GetBgColor(XWidget *p);
    virtual void SetBgColor(XWidget *p, int color);

    virtual bool IsClickable(XWidget *p);
    virtual void SetClickable(XWidget *p, bool b);

    virtual bool IsFocusable(XWidget *p);
    virtual void SetFocusable(XWidget *p, bool b);

    virtual void SetPadding(XWidget *p, int left, int top, int right, int bottom);

    virtual bool IsVisible(XWidget *p);
    virtual void SetVisible(XWidget *p, bool b);

    //virtual int GetMinWidth(XWidget *p);
    virtual void SetMinWidth(XWidget *p, int w);

    //virtual int GetMinHeight(XWidget *p);
    virtual void SetMinHeight(XWidget *p, int h);

    //virtual int GetX(XWidget *p);
    //virtual int GetY(XWidget *p);

    virtual int GetPaddingLeft(XWidget *p);
    virtual int GetPaddingRight(XWidget *p);
    virtual int GetPaddingTop(XWidget *p);
    virtual int GetPaddingBottom(XWidget *p);

    virtual int GetWidth(XWidget *p);
    virtual int GetHeight(XWidget *p);

    //---------Button----------
    virtual void SetButtonText(XWidget *p, const char *pcTxt);
    virtual string GetButtonText(XWidget *p);

private:
    char m_pClassName[30];
    void *m_pClass;
};

#endif // XPLATFORMANDROID_H
