#ifndef INIT_H
#define INIT_H

class XPageXml;

#ifdef _FOR_ANDROID_

#include "jni.h"
jint JNI_OnLoad(JavaVM* vm, void* r);

#else

bool InitXLib();

#endif

#endif // STDAFX_H
