#ifndef XJNIPAGEMGR_H
#define XJNIPAGEMGR_H

#ifdef _FOR_ANDROID_
#include "jni.h"

class XJniPageMgr
{
public:
    static void LockScreen(JNIEnv *pEnv, jboolean lock);
    static jboolean IsScreenLocked(JNIEnv *pEnv);
};

#endif

#endif // XJNIPAGEMGR_H
