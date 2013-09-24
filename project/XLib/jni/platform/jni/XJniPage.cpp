#include "XJniPage.h"
#include "XJniMgr.h"
#include "XPage.h"
#include "XPageFactory.h"
#include "XPageMgr.h"
#include "XWidget.h"
#include "XMenu.h"
#include "XLog.h"

#ifdef _FOR_ANDROID_

jint XJniPage::GetStyle(JNIEnv *pEnv, jobject jpage, jint id)
{
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return NULL;
    }
    return page->GetStyle();
}

void XJniPage::OnNew(JNIEnv *pEnv, jobject jpage, jstring pageName, jint id)
{
    LOGD("jpage=%p, pageName=%p, id=%d", jpage, pageName, id);
    const char *pName = pEnv->GetStringUTFChars(pageName, NULL);
    if (!pName) {
        LOGE("Fail, pName is NULL");
        return;
    }

    XPage *page = XPageFactory::Instance()->New(jpage, pName, id);
    pEnv->ReleaseStringUTFChars(pageName, pName);
    if (!page) {
        LOGE("Fail, page is NULL");
        return;
    }
    XPageMgr::Instance()->AddPage(page);
}

jobject XJniPage::OnCreate(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnCreate jpage=%p id=%d", jpage, id);
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return NULL;
    }
    XWidget *pW = page->OnCreate();
    if (!pW) {
        LOGE("fail, pW is NULL. Can't create content widget.");
        return NULL;
    }
    return (jobject)pW->GetRealWidget();
}

jobject XJniPage::OnReload(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnReload jpage=%p id=%d", jpage, id);
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return NULL;
    }
    page->SetRealPage(reinterpret_cast<void*>(jpage));
    return (jobject)page->GetRoot()->GetRealWidget();
}

void XJniPage::OnDestroy(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnDestroy jpage=%p id=%d", jpage, id);
    XPage *page = XPageMgr::Instance()->FindInAll(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return;
    }
    page->OnDestroy();
}

void XJniPage::OnStart(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnStart jpage=%p id=%d", jpage, id);
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return;
    }
    page->OnStart();
}

void XJniPage::OnStop(JNIEnv *pEnv, jobject jpage, jint id)
{
    LOGD("XJniPage::OnStop  jpage=%p id=%d", jpage, id);
    XPage *page = XPageMgr::Instance()->FindInAll(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return;
    }
    page->OnStop();
}

void XJniPage::OnBackPressed(JNIEnv *pEnv, jobject jpage, jint id)
{
    //LOGD("XJniPage::OnBackPressed pageId=%d", id);
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return;
    }
    page->OnBackPressed();
}

void XJniPage::OnClick(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId)
{
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        LOGE("fail, page is NULL");
        return;
    }
    const char *pId = pEnv->GetStringUTFChars(widgetId, NULL);
    if (!pId) {
        LOGE("fail, pId is NULL, widgetId=%p", widgetId);
        return;
    }
    page->OnClick(pId);
    pEnv->ReleaseStringUTFChars(widgetId, pId);
}

void XJniPage::OnTimeChanged(JNIEnv *pEnv, jobject jpage, jint id, jstring widgetId, jint hourOfDay, jint minute)
{
    XPage *page = XPageMgr::Instance()->Get(id);
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
    XPage *page = XPageMgr::Instance()->Get(id);
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
    XPage *page = XPageMgr::Instance()->Get(id);
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
    XPage *page = XPageMgr::Instance()->Get(id);
    if (!page) {
        //Log err
        return;
    }
    page->OnOptionsItemSelected(menuId);
}

#endif
