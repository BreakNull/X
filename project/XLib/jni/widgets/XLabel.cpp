#include "XLabel.h"
#include "XPlatform.h"

XLabel::XLabel(XPage *p)
    :XWidget(p)
{
}

void XLabel::Create(int flags)
{
    m_pRealWidget = XPlatform::Instance()->NewLabel(m_pPage);
    XWidget::Create(flags);
}

void XLabel::SetProperty(const string &name, const XVariant &v)
{
    if (name == "txt") {
        XPlatform::Instance()->SetLabelText(this, v.ToString().c_str());
    }
    else {
        XWidget::SetProperty(name, v);
    }
}

XVariant XLabel::GetProperty(const string &name)
{
    if (name == "txt") {
        //return XPlatform::Instance()->GetLabText(this).c_str();
    }

    return XWidget::GetProperty(name);
}
