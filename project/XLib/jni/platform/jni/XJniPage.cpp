#include "XJniPage.h"
#include "XJniMgr.h"
#include "XPage.h"
#include "XPageFactory.h"
#include "XPageManager.h"
#include "XWidget.h"
#include "XMenu.h"
#include "XLog.h"

#ifdef _FOR_ANDROID_

void XJniPage::OnNew(JNIEnv *pEnv, jobject jpage, jstring pageName, jint id)
{
    LOGD("XJniPage::OnNew jpage=%p, pageName=%p, id=%d", jpage, pageName, id);

    const char *pName = pEnv->GetStringUTFChars(pageName, NULL);
    if (!pName) {
        LOGE("XJniPage::OnNew fail, pName is NULL");
        return;
    }

    XPage *page = XPageFactory::Instance()->New(jpage, pName, id);
    pEnv->ReleaseStringUTFChars(pageName, pName);
    if (!page) {
        LOGE("XJniPage::OnNew fail, page is NULL");
        return;
    }
    XPageManager::Instance()->AddPage(id, page);
}

jobject XJniPage::OnCreate(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnCreate");
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        LOGE("XJniPage::OnCreate fail, page is NULL");
        return NULL;
    }
    XWidget *pW = page->OnCreate();
    if (!pW) {
        LOGE("XJniPage::OnCreate fail, pW is NULL");
        return NULL;
    }
    return (jobject)pW->GetRealWidget();
}

void XJniPage::OnDestroy(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnDestroy");
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        LOGE("XJniPage::OnDestroy fail, page is NULL");
        return;
    }
    page->OnDestroy();
}

void XJniPage::OnStart(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnStart");
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        LOGE("XJniPage::OnStart fail, page is NULL");
        return;
    }
    page->OnStart();
}

void XJniPage::OnStop(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnStop");
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        LOGE("XJniPage::OnStart fail, page is NULL");
        return;
    }
    page->OnStop();
}

void XJniPage::OnClick(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId)
{
    LOGD("XJniPage::OnClick");

    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        LOGE("XJniPage::OnStart fail, page is NULL");
        return;
    }
    const char *pId = pEnv->GetStringUTFChars(widgetId, NULL);
    if (!pId) {
        LOGE("XJniPage::OnStart fail, pId is NULL");
        return;
    }
    page->OnClick(pId);
    pEnv->ReleaseStringUTFChars(widgetId, pId);
}

void XJniPage::OnTimeChanged(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId, jint hourOfDay, jint minute)
{
    LOGD("XJniPage::OnTimeChanged");

    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        //Log err
        return;
    }
    const char *pId = pEnv->GetStringUTFChars(widgetId, NULL);
    if (!pId) {
        //Log error
        return;
    }
    page->OnTimeChanged(pId, hourOfDay, minute);
    pEnv->ReleaseStringUTFChars(widgetId, pId);
}

void XJniPage::OnDateChanged(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId, jint y, jint m, jint d)
{
    LOGD("XJniPage::OnDateChanged");

    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        //Log err
        return;
    }
    const char *pId = pEnv->GetStringUTFChars(widgetId, NULL);
    if (!pId) {
        //Log error
        return;
    }
    page->OnDateChanged(pId, y, m, d);
    pEnv->ReleaseStringUTFChars(widgetId, pId);
}

jboolean XJniPage::OnCreateOptionsMenu(JNIEnv *pEnv, jobject jpage, jint id, jobject menu)
{
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        //Log err
        return false;
    }
    XMenu *pMenu = new XMenu(page);
    pMenu->SetRealMenu((void*)menu);
    return page->OnCreateOptionsMenu(pMenu);
}

void XJniPage::OnOptionsItemSelected(JNIEnv *pEnv, jobject jpage, jint id, jint menuId)
{
    XPage *page = XPageManager::Instance()->GetPage(id);
    if (!page) {
        //Log err
        return;
    }
    page->OnOptionsItemSelected(menuId);
}

#endif
