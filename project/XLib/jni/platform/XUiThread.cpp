#include "XUiThread.h"
#include "XPlatform.h"

XUiThread::XUiThread()
{
}

bool XUiThread::PostRunnable(Runnable r)
{
    return XPlatform::Instance()->PostRunnable(r);
}

bool XUiThread::PostRunnable(Runnable r, int delayMs)
{
    return XPlatform::Instance()->PostRunnable(r, delayMs);
}
