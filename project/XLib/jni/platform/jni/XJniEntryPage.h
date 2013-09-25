#ifndef XJNIENTRYPAGE_H
#define XJNIENTRYPAGE_H

#ifdef _FOR_ANDROID_
#include <jni.h>

class XJniEntryPage
{
public:
    static void CopyOmlDbFile(JNIEnv *pEnv);
};

#endif

#endif // XJNIENTRYPAGE_H
