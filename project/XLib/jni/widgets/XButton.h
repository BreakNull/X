#ifndef XBUTTON_H
#define XBUTTON_H

#include "XWidget.h"


class XButton : public XWidget
{
public:
    XButton(XPage *p);

    WIDGET_NEW(XButton)

    virtual void Create(int flags);

    virtual void SetProperty(const string &name, const XVariant &v);
    virtual XVariant GetProperty(const string &name);
};

#endif // BUTTON_H
