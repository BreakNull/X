#ifndef XPROGRESSBAR_H
#define XPROGRESSBAR_H

#include "XWidget.h"

/**
 * 进度条
 */
class XProgressBar : public XWidget
{
public:
    XProgressBar(XPage *p);

    WIDGET_NEW(XProgressBar)
};

#endif // PROGRESSBAR_H
