#ifndef XLINELAYOUT_H
#define XLINELAYOUT_H

#include "XWidget.h"

class XLineLayout : public XWidget
{
public:
    XLineLayout(XPage *p);
    WIDGET_NEW(XLineLayout)

    virtual void Create();

    virtual void SetProperty(XPage *p, const string &name, const XVariant &v);
    virtual XVariant GetProperty(const string &name);

    virtual bool IsContainer();
};

#endif // LINELAYOUT_H
