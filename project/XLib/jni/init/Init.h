#ifndef INIT_H
#define INIT_H

class XPageXml;

#ifdef _FOR_ANDROID_

#include "jni.h"
jint JNI_OnLoad(JavaVM* vm, void* r);

#else

bool InitXLib();

#endif

/**
 * 获得一个XPageXml的实例，它始终会返回相同的实例
 * 此实例由SetPageXml()来设置
 * 若未通过SetPageXml()设置，则将使用默认的XPageXml
 */
XPageXml *GetXPageXml();

/**
 * 可在初始化SO时，调用此函数以初始化XPageXml的一个实例
 * 目的：以后可以重载XPageXml的一个子类， 提供扩充xml解析的能力
 */
void SetXPageXml(XPageXml *p);

#endif // STDAFX_H
