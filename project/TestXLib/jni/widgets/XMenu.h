#ifndef XMENU_H
#define XMENU_H

#include "XWidget.h"

class XMenu : public XWidget
{
public:
    XMenu(XPage *p);
    WIDGET_NEW(XMenu)

    void SetRealMenu(void *pMenu) {m_pRealWidget = pMenu;}
};

#endif // MENU_H
