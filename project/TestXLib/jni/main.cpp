#include <jni.h>
#include "Init.h"
#include "XPageXml.h"
#include "XPageFactory.h"
#include "HelloPage.h"
#include "NiPage.h"
#include "XLog.h"


jint JNI_OnLoad(JavaVM* vm, void* r)
{
    XPageFactory::Instance()->RegistNew("HelloPage", HelloPage::New);
	XPageFactory::Instance()->RegistNew("NiPage", NiPage::New);
	return JNI_VERSION_1_4;
}
