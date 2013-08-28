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
};

#endif // LABEL_H
