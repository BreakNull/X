#include "XJniUiThreadRunnable.h"
#include "XUiThread.h"
#include "XLog.h"

void XJniUiThreadRunnable::Run(JNIEnv *pEnv, jlong addr, jlong param)
{
    XUiThread::Runnable r = reinterpret_cast<XUiThread::Runnable>(addr);
    if (addr == 0) {
        LOGE("addr is NULL");
        return;
    }

    void *p = reinterpret_cast<void*>(param);
    r(p);
}
