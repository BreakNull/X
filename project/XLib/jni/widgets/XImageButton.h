#ifndef XIMAGEBUTTON_H
#define XIMAGEBUTTON_H

#include "XWidget.h"

class XImageButton : public XWidget
{
public:
    XImageButton();

    WIDGET_NEW(XImageButton)

    virtual void Create(XPage *p, int flags);
    virtual void SetProperty(const string &name, const XVariant &v);
};

#endif // IMAGEBUTTON_H
