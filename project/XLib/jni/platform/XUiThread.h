#ifndef UITHREAD_H
#define UITHREAD_H

#include "XRunnable.h"

/**
 * 平台相关的UI线程
 * 用于将一个Runnable放到UI线程上执行
 */
class XUiThread
{
public:

    //将r发送到UI线程， 并将在UI线程上执行
    static bool PostRunnable(XRunnable r);

    //将r发送到UI线程， 并将延迟delayMs毫秒之后在UI线程上执行
    static bool PostRunnable(XRunnable r, int delayMs);

private:
    XUiThread();
};

#endif // UITHREAD_H
