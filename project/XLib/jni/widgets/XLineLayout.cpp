#include "XLineLayout.h"
#include "XPlatform.h"

XLineLayout::XLineLayout(XPage *p)
    :XWidget(p)
{
}

void XLineLayout::Create()
{
    m_pRealWidget = XPlatform::Instance()->NewLineLayout(m_pPage);
}

void XLineLayout::SetProperty(XPage *p, const string &name, const XVariant &v)
{
    if (name == "ori") {
        XPlatform::Instance()->SetOrientation(this, v.ToString() == "ver");
    }
    else {
        XWidget::SetProperty(p, name, v);
    }
}

XVariant XLineLayout::GetProperty(const string &name)
{
    return XWidget::GetProperty(name);
}

bool XLineLayout::IsContainer()
{
    return true;
}
