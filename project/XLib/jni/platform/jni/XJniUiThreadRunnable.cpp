#include "XJniUiThreadRunnable.h"
#include "XUiThread.h"
#include "XLog.h"

#ifdef _FOR_ANDROID_

void XJniUiThreadRunnable::Run(JNIEnv *pEnv, jlong addr, jlong param)
{
    XRunnable r = reinterpret_cast<XRunnable>(addr);
    if (addr == 0) {
        LOGE("addr is NULL");
        return;
    }

    void *p = reinterpret_cast<void*>(param);
    r(p);
}

#endif
