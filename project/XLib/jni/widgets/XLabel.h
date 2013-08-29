#ifndef XLABEL_H
#define XLABEL_H

#include "XWidget.h"


/**
 * 支持的property有：
 *      text: string 标签上的文本
 *
 */
class XLabel : public XWidget
{
public:
    XLabel(XPage *p);

    WIDGET_NEW(XLabel)

    virtual void Create();

    virtual void SetProperty(const string &name, const XVariant &v);
    virtual XVariant GetProperty(const string &name);
};

#endif // LABEL_H
