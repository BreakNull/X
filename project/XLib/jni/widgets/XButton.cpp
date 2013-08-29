#include "XButton.h"
#include "XPlatform.h"

XButton::XButton(XPage *p)
    :XWidget(p)
{
}

void XButton::Create()
{
    m_pRealWidget = XPlatform::Instance()->NewButton(m_pPage);
}

void XButton::SetProperty(const string &name, const XVariant &v)
{
    if (name == "txt") {
        XPlatform::Instance()->SetButtonText(this, v.ToString().c_str());
    }
    else {
        XWidget::SetProperty(name, v);
    }
}

XVariant XButton::GetProperty(const string &name)
{
    if (name == "txt") {
        return XPlatform::Instance()->GetButtonText(this).c_str();
    }
    else {
        return XWidget::GetProperty(name);
    }
}
