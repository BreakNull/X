#ifndef XIMAGEBUTTON_H
#define XIMAGEBUTTON_H

#include "XWidget.h"

class XImageButton : public XWidget
{
public:
    XImageButton(XPage *p);

    WIDGET_NEW(XImageButton)

    virtual void Create(int flags);
    virtual void SetProperty(const string &name, const XVariant &v);
};

#endif // IMAGEBUTTON_H
