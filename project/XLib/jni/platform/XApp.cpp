#include "XApp.h"
#include "XPlatform.h"
#include "XFile.h"
#include "XResource.h"
#include <stdio.h>
#include "XLog.h"

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

string XApp::GetOmlDbFilePath()
{
    return GetWorkDir() + "/oml.db";
}

void XApp::CopyOmlDbFile()
{
    XFile f(GetOmlDbFilePath());
    if (f.IsExists()) {
        return;
    }
    XResource res("plt:oml_db");
    int len = res.GetDataLen();
    void *pBuf = res.GetData();
    if (!pBuf || !len) {
        LOGE("can't load res 'plt:oml_db'");
        return;
    }

    FILE *pf = fopen(GetOmlDbFilePath().c_str(), "wb");
    if (!pf) {
        free(pBuf);
        LOGE("open oml.db error");
        return;
    }
    fwrite(pBuf, 1, len, pf);
    fclose(pf);
    free(pBuf);
}
