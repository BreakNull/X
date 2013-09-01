#include "XImageButton.h"
#include "XPlatform.h"

XImageButton::XImageButton(XPage *p)
    :XWidget(p)
{
}

void XImageButton::Create()
{
    m_pRealWidget = XPlatform::Instance()->NewImageButton(m_pPage);
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
