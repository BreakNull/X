#include <jni.h>
#include "init/Init.h"
#include "util/tinyxml/tinyxml.h"
#include "page/XPageXml.h"

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
	
	return JNI_VERSION_1_4;
}