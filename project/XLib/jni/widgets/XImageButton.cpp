#include "XImageButton.h"
#include "XPlatform.h"

XImageButton::XImageButton()
{
}

void XImageButton::Create(XPage *p, int flags)
{
    m_pRealWidget = XPlatform::Instance()->NewImageButton(p);
    XWidget::Create(p, flags);
}

void XImageButton::SetProperty(const string &name, const XVariant &v)
{
    if (name == "src") {
        XPlatform::Instance()->SetImgButtonSrc(this, v.ToString().c_str());
    }
    else {
        XWidget::SetProperty(name, v);
    }
}
