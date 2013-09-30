#include "XLineLayout.h"
#include "XPlatform.h"
#include "XLog.h"

XLineLayout::XLineLayout()
{
}

void XLineLayout::Create(XPage *p, int flags)
{
    m_pRealWidget = XPlatform::Instance()->NewLineLayout(p);
    XWidget::Create(p, flags);
}

void XLineLayout::SetProperty(const string &name, const XVariant &v)
{
    if (name == "ori") {
        XPlatform::Instance()->SetOrientation(this, v.ToString() == "ver");
    }
    else {
        XWidget::SetProperty(name, v);
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
