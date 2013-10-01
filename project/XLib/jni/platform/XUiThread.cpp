#include "XUiThread.h"
#include "XPlatform.h"

XUiThread::XUiThread()
{
}

bool XUiThread::PostRunnable(XRunnable r)
{
    return XPlatform::Instance()->PostRunnable(r);
}

bool XUiThread::PostRunnable(XRunnable r, int delayMs)
{
    return XPlatform::Instance()->PostRunnable(r, delayMs);
}
