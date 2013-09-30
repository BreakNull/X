#include "XWidget.h"
#include "XLog.h"
#include "XPlatform.h"
#include <ctype.h>

#ifdef _FOR_ANDROID_
#include <jni.h>
#include "XJniMgr.h"
#endif

XWidget::XWidget()
    :m_pRealWidget(NULL)
    ,m_iFlags(0)
{
}

XWidget::~XWidget()
{
#ifdef _FOR_ANDROID_
    if (m_iFlags & F_NEW_REF) {
        JNIEnv *pEnv = XJniMgr::Instance()->GetJniEnv();
        /*
         * (1).A java method returned object is a global object ref.
         *      And can't new its weak ref.(Its weak ref is a invalid pointer, like 0x02aaef)
         * (2).On a global object new its global ref will return a pointer same as itself.
         *      But they(global obj, its global ref) are not full the same.
         *
        if (pEnv->IsSameObject(reinterpret_cast<jobject>(m_pRealWidget), (jobject)NULL)) {
            LOGD("java widget %p has been delete by java GC", m_pRealWidget);
        }
        pEnv->DeleteWeakGlobalRef(reinterpret_cast<jobject>(m_pRealWidget));
        */
        pEnv->DeleteGlobalRef(reinterpret_cast<jobject>(m_pRealWidget));
    }
#endif
}

void XWidget::Create(XPage *p, int flags)
{
    m_iFlags = flags;
#ifdef _FOR_ANDROID_
    if ((m_iFlags & F_NEW_REF) && (m_pRealWidget != NULL)) {
        JNIEnv *pEnv = XJniMgr::Instance()->GetJniEnv();
        jobject obj = pEnv->NewGlobalRef(reinterpret_cast<jobject>(m_pRealWidget));
        //jobject obj = pEnv->NewWeakGlobalRef(reinterpret_cast<jobject>(m_pRealWidget));
        m_pRealWidget = reinterpret_cast<void*>(obj);
    }
#endif
}

static bool GetColor(const string &s, int *val)
{
    int d = 0;
    const char *p = s.c_str();
    int len = strlen(p);
    if (len != 6 && len != 8) {
        return false;
    }
    for (int i = 0; *p && i < len; ++i,++p) {
        int cur = 0;
        if (*p >= '0' && *p <= '9') {
            cur = *p - '0';
        } else if (*p >= 'a' && *p <= 'z') {
            cur = *p - 'a' + 10;
        } else if (*p >= 'A' && *p <= 'Z') {
            cur = *p - 'A' + 10;
        } else {
            return false;
        }
        d = d*16 + cur;
    }
    if (len == 6) {
        d |= 0xff000000;
    }
    *val = d;
    return true;
}

void XWidget::SetProperty(const string &name, const XVariant &v)
{
    //TODO:
    if (name == "x") {

    } else if (name == "y") {

    } else if (name == "w") {

    } else if (name == "h") {

    } else if (name == "id") {
        XPlatform::Instance()->SetId(this, v.ToString());
    } else if (name == "bgcolor") {
        string s = v.ToString();
        int d = 0;
        if (!GetColor(s, &d)) {
            LOGE("The color '%s' is invalid", s.c_str());
            return;
        }
        XPlatform::Instance()->SetBgColor(this, d);
    } else if (name == "bgimg") {
        XPlatform::Instance()->SetBgImg(this, v.ToString());
    }
}

XVariant XWidget::GetProperty(const string &name)
{
    //TODO:
    if (name == "x") {

    } else if (name == "y") {

    } else if (name == "w") {

    } else if (name == "h") {

    } else if (name == "id") {
    }

    //not find this property
    return XVariant();
}

bool XWidget::IsContainer()
{
    return false;
}

void *XWidget::GetChild(const string &id)
{
    return XPlatform::Instance()->GetChild(this, id.c_str());
}

int XWidget::GetChildCount()
{
    return XPlatform::Instance()->GetChildCount(this);
}

void *XWidget::GetChildAt(int idx)
{
    return XPlatform::Instance()->GetChildAt(this, idx);
}

void XWidget::AddChild(XWidget *pChild, int idx)
{
    XPlatform::Instance()->AddChild(this, pChild, idx);
}


