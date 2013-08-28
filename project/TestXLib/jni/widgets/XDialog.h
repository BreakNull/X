#ifndef XDIALOG_H
#define XDIALOG_H

#include "XWidget.h"
class XPage;

/**
 * Dialog d = new Dialog(page);
 * d.Create();
 * d.SetContent(p2);
 * d.Show();
 */
class XDialog : public XWidget
{
public:
    XDialog(XPage *p);
    WIDGET_NEW(XDialog)

    virtual void Show();
    virtual void SetContent(XWidget *p);
    virtual void SetTitle(const string &title);

protected:
    XPage *m_page;
};

#endif // DIALOG_H
