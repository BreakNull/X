#ifndef XUITHREADRUNNABLE_H
#define XUITHREADRUNNABLE_H

#ifdef _FOR_ANDROID_
#include "jni.h"

class XJniUiThreadRunnable
{
public:
    static void Run(JNIEnv *pEnv, jlong addr, jlong param);
};


#endif
#endif // XUITHREADRUNNABLE_H
