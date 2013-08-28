#include "XApp.h"

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
