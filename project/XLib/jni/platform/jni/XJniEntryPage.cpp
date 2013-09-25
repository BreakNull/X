#include "XJniEntryPage.h"
#include "XApp.h"

#ifdef _FOR_ANDROID_

void XJniEntryPage::CopyOmlDbFile(JNIEnv *pEnv)
{
    XApp::Instance()->CopyOmlDbFile();
}

#endif
