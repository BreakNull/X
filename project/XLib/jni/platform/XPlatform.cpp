#include "XPlatform.h"
#include "XPlatformAndroid.h"

XPlatform *XPlatform::s_ins;

XPlatform::XPlatform()
{
}

XPlatform *XPlatform::Instance()
{
    if (!s_ins) {
#ifdef _FOR_ANDROID_
        s_ins = new XPlatformAndroid();
#else
        s_ins = new XPlatformIphone();
#endif
    }
    return s_ins;
}
