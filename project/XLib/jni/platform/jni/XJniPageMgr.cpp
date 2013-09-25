#include "XJniPageMgr.h"
#include "XPageMgr.h"

void XJniPageMgr::LockScreen(JNIEnv *pEnv, jboolean lock)
{
    XPageMgr::Instance()->LockScreen(lock ? true : false);
}


jboolean XJniPageMgr::IsScreenLocked(JNIEnv *pEnv)
{
    bool b = XPageMgr::Instance()->IsScreenLocked();
    return b ? JNI_TRUE : JNI_FALSE;
}
