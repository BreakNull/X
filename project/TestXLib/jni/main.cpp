#include <jni.h>
#include "Init.h"
#include "tinyxml.h"
#include "XPageXml.h"
#include "XPageFactory.h"
#include "MainPage.h"

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
	SetXPageXml(new XPageXml(NULL));
	InitXLib(vm, r);
    XPageFactory::Instance()->RegistNew("MainActivity", MainPage::New);
	return JNI_VERSION_1_4;
}
