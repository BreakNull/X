#ifndef XJNIPAGE_H
#define XJNIPAGE_H

#ifdef _FOR_ANDROID_
#include "jni.h"

/**
 * java的JPage类中native函数的实现
 */
class XJniPage
{
public:
    static jint GetStyle(JNIEnv *pEnv, jobject jpage, jint id);
    static void OnNew(JNIEnv *pEnv, jobject jpage, jstring pageName, jint id);
    static jobject OnCreate(JNIEnv *pEnv, jobject jpage, jint id);
    static jobject OnReload(JNIEnv *pEnv, jobject jpage, jint id);
    static void OnDestroy(JNIEnv *pEnv, jobject jpage, jint id);
    static void OnStart(JNIEnv *pEnv, jobject jpage, jint id);
    static void OnStop(JNIEnv *pEnv, jobject jpage, jint id);
    static void OnBackPressed(JNIEnv *pEnv, jobject jpage, jint id);

    static void OnClick(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId);
    static void OnTimeChanged(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId, jint hourOfDay, jint minute);
    static void OnDateChanged(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId, jint y, jint m, jint d);

    static jboolean OnCreateOptionsMenu(JNIEnv *pEnv, jobject jpage, jint id, jobject menu);
    static void OnOptionsItemSelected(JNIEnv *pEnv, jobject jpage, jint id, jint menuId);
};

#endif

#endif // XJNIPAGE_H
