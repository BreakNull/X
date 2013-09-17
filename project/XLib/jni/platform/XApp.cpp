#include "XApp.h"
#include "XPlatform.h"

XApp *XApp::s_ins;

XApp::XApp()
{
}

XApp *XApp::Instance()
{
    if (!s_ins) {
        s_ins = new XApp();
    }
    return s_ins;
}

string XApp::GetWorkDir()
{
    return XPlatform::Instance()->GetWorkDir();
}

string XApp::GetAppFilesDir()
{
    string n = GetWorkDir();
    if (n.empty()) {
        return "";
    }
    return n + "/files";
}
