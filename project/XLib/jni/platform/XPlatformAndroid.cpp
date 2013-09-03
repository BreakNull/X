#include "XPlatformAndroid.h"
#include "XJniMgr.h"
#include "jni.h"
#include "XResource.h"
#include "XWidget.h"
#include "XPage.h"
#include "string.h"
#include "XLog.h"

#define GET_MID(name, ret)  \
    jmethodID mid = (jmethodID)XJniMgr::Instance()->GetMethod(m_pClassName, name);  \
    JNIEnv *pEnv = (JNIEnv *)XJniMgr::Instance()->GetJniEnv(); \
    if (!mid || !pEnv || !m_pClass) { \
        LOGE("Error, pEnv=%p, mid=%p, m_pClass=%p, method=%s", pEnv, mid, m_pClass, name);  \
        return ret; \
    }

#define GET_MID_NO(name)  \
    jmethodID mid = (jmethodID)XJniMgr::Instance()->GetMethod(m_pClassName, name);  \
    JNIEnv *pEnv = (JNIEnv *)XJniMgr::Instance()->GetJniEnv(); \
    if (!mid || !pEnv || !m_pClass) { \
        LOGE("Error, pEnv=%p, mid=%p, m_pClass=%p, method=%s", pEnv, mid, m_pClass, name);  \
        return; \
    }

#define CALL_OBJ(...)  \
    jobject _obj = pEnv->CallStaticObjectMethod((jclass)m_pClass, mid, ##__VA_ARGS__);

#define CALL_OBJ_R(...)  \
    return pEnv->CallStaticObjectMethod((jclass)m_pClass, mid, ##__VA_ARGS__);

#define CALL_VOID(...) \
    pEnv->CallStaticVoidMethod((jclass)m_pClass, mid, ##__VA_ARGS__);

#define CALL_BOOL_R(...) \
    return pEnv->CallStaticBooleanMethod((jclass)m_pClass, mid, ##__VA_ARGS__);

#define CALL_INT_R(...) \
    return pEnv->CallStaticIntMethod((jclass)m_pClass, mid, ##__VA_ARGS__);

#define CHECK_P(p) \
    bool _b = true; \
    if (NULL == p) {LOGE("Arguments error! " #p " = NULL");_b=false;}

#define CHECK_PP(p1, p2) \
    bool _b = true; \
    if (NULL == p1 || NULL == p2) {LOGE("Arguments error! " #p1 " = %p, " #p2 " = %p", p1, p2);_b=false;}

#define CHECK_PS(p1, ps) \
    bool _b = true; \
    if (NULL == p1 || NULL == ps) {LOGE("Arguments error! " #p1 " = %p, " #ps " = %s", p1, ps);_b=false;}

#define CHECK_B(r) if (!_b) return r;
#define CHECK_B_NO() if (!_b) return;

#define W(p) (jobject)p->GetRealWidget()
#define R(p) (jobject)p->GetRealPage()

XPlatformAndroid::XPlatformAndroid()
{
    strcpy(m_pClassName,"x.core.ui.Platform");
    m_pClass = XJniMgr::Instance()->GetClass(m_pClassName);
}

void *XPlatformAndroid::NewButton(XPage *p)
{
    CHECK_P(p);
    CHECK_B(NULL);
    GET_MID("newButton", NULL);
    CALL_OBJ_R(R(p));
}

void *XPlatformAndroid::NewLabel(XPage *p)
{
    CHECK_P(p);
    CHECK_B(NULL);
    GET_MID("newLabel", NULL);
    CALL_OBJ_R(R(p));
}

void *XPlatformAndroid::NewLineLayout(XPage *p)
{
    CHECK_P(p);
    CHECK_B(NULL);
    GET_MID("newLineLayout", NULL);
    CALL_OBJ_R(R(p));
}

void *XPlatformAndroid::NewImageButton(XPage *p)
{
    CHECK_P(p);
    CHECK_B(NULL);
    GET_MID("newImageButton", NULL);
    CALL_OBJ_R(R(p));
}

static string Js2N(jstring jstr, JNIEnv *pEnv)
{
    if (!pEnv || !jstr) {
        return "";
    }
    const char *p = pEnv->GetStringUTFChars(jstr, NULL);
    string s(p);
    pEnv->ReleaseStringUTFChars(jstr, p);
    return s;
}

string XPlatformAndroid::GetId(XWidget *p)
{
    CHECK_P(p);
    CHECK_B("");
    GET_MID("getId", "");
    CALL_OBJ(W(p));
    return Js2N((jstring)_obj, pEnv);
}

void XPlatformAndroid::SetId(XWidget *p, const string &id)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setId");
    jstring jsid = pEnv->NewStringUTF(id.c_str());
    CALL_VOID(W(p), jsid);
    pEnv->DeleteLocalRef(jsid);
}

//XResource *GetBgImg(XWidget *p){}
void XPlatformAndroid::SetBgImg(XWidget *p, const string &rid)
{
    CHECK_P(p);
    _b = !rid.empty();
    CHECK_B_NO();
    GET_MID_NO("setBgImg");
    jstring jsname = pEnv->NewStringUTF(rid.c_str());
    CALL_VOID(W(p), jsname);
    pEnv->DeleteLocalRef(jsname);
}

//int GetBgColor(XWidget *p){}
void XPlatformAndroid::SetBgColor(XWidget *p, int color)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setBgColor");
    CALL_VOID(W(p), color);
}

bool XPlatformAndroid::IsClickable(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(false);
    GET_MID("isClickable", false);
    CALL_BOOL_R(W(p));
}

void XPlatformAndroid::SetClickable(XWidget *p, bool b)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setClickable");
    CALL_VOID(W(p), b);
}

bool XPlatformAndroid::IsFocusable(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(false);
    GET_MID("isFocusable", false);
    CALL_BOOL_R(W(p));
}

void XPlatformAndroid::SetFocusable(XWidget *p, bool b)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setFocusable");
    CALL_VOID(W(p), b);
}

void XPlatformAndroid::SetPadding(XWidget *p, int left, int top, int right, int bottom)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setPadding");
    CALL_VOID(W(p), left, top, right, bottom);
}

bool XPlatformAndroid::IsVisible(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(false);
    GET_MID("isVisible", false);
    CALL_BOOL_R(W(p));
}

void XPlatformAndroid::SetVisible(XWidget *p, bool b)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setVisible");
    CALL_VOID(W(p), b);
}

//int GetMinWidth(XWidget *p){}
void XPlatformAndroid::SetMinWidth(XWidget *p, int w)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setMinWidth");
    CALL_VOID(W(p), w);
}

//int GetMinHeight(XWidget *p){}
void XPlatformAndroid::SetMinHeight(XWidget *p, int h)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setMinHeight");
    CALL_VOID(W(p), h);
}

//int GetX(XWidget *p){}
//int GetY(XWidget *p){}

int XPlatformAndroid::GetPaddingLeft(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    GET_MID("getPaddingLeft", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetPaddingRight(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    GET_MID("getPaddingRight", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetPaddingTop(XWidget *p)
{
    GET_MID("getPaddingTop", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetPaddingBottom(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    GET_MID("getPaddingBottom", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetWidth(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    GET_MID("getWidth", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetHeight(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    GET_MID("getHeight", 0);
    CALL_INT_R(W(p));
}

int XPlatformAndroid::GetChildCount(XWidget *p)
{
    CHECK_P(p);
    CHECK_B(0);
    if (!p->IsContainer()) {
        return 0;
    }
    GET_MID("getChildCount", 0);
    CALL_INT_R(W(p));
}

void *XPlatformAndroid::GetChildAt(XWidget *p, int idx)
{
    CHECK_P(p);
    CHECK_B(NULL);
    if (!p->IsContainer()) {
        return NULL;
    }
    GET_MID("getChildAt", NULL);
    CALL_OBJ_R(W(p), idx);
}

void *XPlatformAndroid::GetChild(XWidget *p, const char *pId)
{
    CHECK_PP(p, pId);
    CHECK_B(NULL);
    if (!p->IsContainer()) {
        return NULL;
    }
    GET_MID("getChild", NULL);
    jstring js = pEnv->NewStringUTF(pId);
    CALL_OBJ(W(p), js);
    pEnv->DeleteLocalRef(js);
    return _obj;
}

void XPlatformAndroid::SetTitle(XPage *p, const string &title)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setTitle");
    jstring js = pEnv->NewStringUTF(title.c_str());
    CALL_VOID(R(p), js);
    pEnv->DeleteLocalRef(js);
}

void XPlatformAndroid::SetListener(XPage *p, XWidget *w, const string &name)
{
    CHECK_PP(p, w);
    CHECK_B_NO();
    GET_MID_NO("setListener");
    jstring js = pEnv->NewStringUTF(name.c_str());
    CALL_VOID(R(p), W(w), js);
    pEnv->DeleteLocalRef(js);
}

void XPlatformAndroid::ClearListener(XPage *p, XWidget *w, const string &name)
{
    CHECK_PP(p, w);
    CHECK_B_NO();
    GET_MID_NO("clearListener");
    jstring js = pEnv->NewStringUTF(name.c_str());
    CALL_VOID(R(p), W(w), js);
    pEnv->DeleteLocalRef(js);
}

void *XPlatformAndroid::FindById(const char *pId, XWidget *p)
{
    CHECK_PP(p, pId);
    CHECK_B(NULL);
    GET_MID("findById", NULL);
    jstring js = pEnv->NewStringUTF(pId);
    CALL_OBJ(W(p), js);
    pEnv->DeleteLocalRef(js);
    return reinterpret_cast<void*>(_obj);
}

void XPlatformAndroid::SetButtonText(XWidget *p, const char *pcTxt)
{
    CHECK_PS(p, pcTxt);
    CHECK_B_NO();
    GET_MID_NO("setButtonText");
    jstring js = pEnv->NewStringUTF(pcTxt);
    CALL_VOID(W(p), js);
    pEnv->DeleteLocalRef(js);
}

string XPlatformAndroid::GetButtonText(XWidget *p)
{
    CHECK_P(p);
    CHECK_B("");
    GET_MID("getButtonText", "");
    CALL_OBJ(W(p));
    return Js2N((jstring)_obj, pEnv);
}

void XPlatformAndroid::SetLabelText(XWidget *p, const char *pcTxt)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setLabelText");
    jstring js = pEnv->NewStringUTF(pcTxt);
    CALL_VOID(W(p), js);
    pEnv->DeleteLocalRef(js);
}

void XPlatformAndroid::SetOrientation(XWidget *p, bool vertical)
{
    CHECK_P(p);
    CHECK_B_NO();
    GET_MID_NO("setOrientation");
    jboolean b = vertical ? 1 : 0;
    CALL_VOID(W(p), b);
}

bool XPlatformAndroid::AddChild(XWidget *p, XWidget *c, int idx)
{
    CHECK_PP(p, c);
    CHECK_B(false);
    if (p->IsContainer()) {
        GET_MID("addChild", false);
        CALL_BOOL_R(W(p), W(c), idx);
    }
    return false;
}

bool XPlatformAndroid::PostRunnable(XUiThread::Runnable r)
{
    CHECK_P(r);
    CHECK_B(false);
    GET_MID("post", false);
    CALL_BOOL_R((jlong)r);
}

bool XPlatformAndroid::PostRunnable(XUiThread::Runnable r, int delayMs)
{
    CHECK_P(r);
    CHECK_B(false);
    GET_MID("post2", false);
    CALL_BOOL_R((jlong)r, delayMs);
}

void XPlatformAndroid::SetImgButtonSrc(XWidget *p, const char *pSrc)
{
    CHECK_PP(p, pSrc);
    CHECK_B_NO();
    GET_MID_NO("setImgButtonSrc");
    jstring js = pEnv->NewStringUTF(pSrc);
    CALL_VOID(W(p), js);
    pEnv->DeleteLocalRef(js);
}
