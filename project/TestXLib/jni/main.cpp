#include <jni.h>
#include "Init.h"
#include "tinyxml.h"
#include "XPageXml.h"
#include "XPageFactory.h"
#include "HelloPage.h"
#include "XLog.h"

#ifdef __cplusplus
#pragma message "there is c++ compile"
#endif

#ifndef _FOR_ANDROID_
#	pragma message "There has no micro _FOR_ANDROID_"
#else
#	pragma message "There has micro _FOR_ANDROID_"
#endif



jint JNI_OnLoad(JavaVM* vm, void* r)
{
	LOGD("TestXLib init begin>>>>>>");
    XPageFactory::Instance()->RegistNew("HelloPage", HelloPage::New);
	LOGD("TestXLib init end<<<<<<<<<");
	return JNI_VERSION_1_4;
}
