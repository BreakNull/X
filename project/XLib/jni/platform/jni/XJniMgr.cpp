#include "XJniMgr.h"
#include <list>

#ifdef _FOR_ANDROID_
#include "jni.h"
#include "XLog.h"

using namespace std;

XJniMgr *XJniMgr::s_pcIns;

class XJniClass
{
public:
    XJniClass() :m_pcClass(NULL),m_pcObj(NULL) {}

    jclass m_pcClass;                 //java class
    jobject m_pcObj;                  //java object of this class
    map<string, void*> m_cFields;     //java fields
    map<string, void*> m_cMethods;    //java methods
};

XJniMgr::XJniMgr()
    :m_pJavaVM(NULL)
{
}

XJniMgr *XJniMgr::Instance()
{
    if (!s_pcIns) {
        s_pcIns = new XJniMgr;
    }
    return s_pcIns;
}

jclass XJniMgr::GetClass(const char *szClassName)
{
    XJniClass *pClass = GetJniClass(szClassName);
    if (NULL == pClass) {
        return NULL;
    }
    return pClass->m_pcClass;
}

jfieldID XJniMgr::GetField(const char *szClassName, const char *szFieldName)
{
    XJniClass *pClass = GetJniClass(szClassName);
    if (NULL == pClass) {
        return NULL;
    }
    string name(szFieldName);
    map<string, void*>::iterator it = pClass->m_cFields.find(name);
    if (it != pClass->m_cFields.end()) {
        void *r = (*it).second;
        return (jfieldID)r;
    }
    return NULL;
}

jmethodID XJniMgr::GetMethod(const char *szClassName, const char *szMethodName)
{
    XJniClass *pClass = GetJniClass(szClassName);
    if (NULL == pClass) {
        return NULL;
    }
    string name(szMethodName);
    map<string, void*>::iterator it = pClass->m_cMethods.find(name);
    if (it != pClass->m_cMethods.end()) {
        void *r = (*it).second;
        return (jmethodID)r;
    }
    return NULL;
}

void XJniMgr::AddClass(const char *szClassName, jclass pClass)
{
    if (NULL == szClassName || NULL == pClass) {
        LOGE("XJniMgr::AddClass arg invalid, szClassName=%p, pClass=%p", szClassName, pClass);
        return;
    }

    string name(szClassName);
    XJniClass *pClassInfo = NULL;

    map<string, XJniClass*>::iterator it = m_cJniClassMap.find(name);
    if (it != m_cJniClassMap.end()) {
        pClassInfo = (*it).second;
    } else {
        pClassInfo = new XJniClass;
        m_cJniClassMap.insert(pair<string,XJniClass*>(name, pClassInfo));
    }
    pClassInfo->m_pcClass = pClass;
}

void XJniMgr::AddField(const char *szClassName, const char *szFieldName, jfieldID pField)
{
    if (!szClassName || !szFieldName || !pField) {
        LOGE("XJniMgr::AddField arg invalid, szClassName=%p, szFieldName=%p, pField=%p", szClassName, szFieldName, pField);
        return;
    }

    string name(szClassName);
    XJniClass *pClassInfo = NULL;

    map<string, XJniClass*>::iterator it = m_cJniClassMap.find(name);
    if (it == m_cJniClassMap.end()) {
        //TODO: log 'There is not class for szClassName, you must add class first'
        return;
    }
    pClassInfo = (*it).second;
    if (!pClassInfo) {
        //TODO: log
        return;
    }
    pClassInfo->m_cFields.insert(pair<string,void*>(szFieldName, pField));
}

void XJniMgr::AddMethod(const char *szClassName, const char *szMethodName, jmethodID pMethod)
{
    if (!szClassName || !szMethodName || !pMethod) {
        LOGE("XJniMgr::AddMethod arg invalid, szClassName=%p, szMethodName=%p, pMethod=%p", szClassName, szMethodName, pMethod);
        return;
    }

    string name(szClassName);
    XJniClass *pClassInfo = NULL;

    map<string, XJniClass*>::iterator it = m_cJniClassMap.find(name);
    if (it == m_cJniClassMap.end()) {
        LOGE("XJniMgr::AddMethod, There is not class for '%s', you must add class first", szClassName);
        return;
    }
    pClassInfo = (*it).second;
    if (!pClassInfo) {
        //TODO: log
        return;
    }
    pClassInfo->m_cMethods.insert(pair<string,void*>(szMethodName, pMethod));
}

JNIEnv *XJniMgr::GetJniEnv()
{
    if (NULL ==m_pJavaVM) {
        return NULL;
    }
    void* pEnv = NULL;
    if (m_pJavaVM->GetEnv(&pEnv, JNI_VERSION_1_4) != JNI_OK) {
        return NULL;
    }
    return (JNIEnv*)pEnv;
}

XJniClass *XJniMgr::GetJniClass(const char *szClassName)
{
    if (NULL == szClassName) {
        return NULL;
    }
    string name(szClassName);
    map<string, XJniClass*>::iterator it = m_cJniClassMap.find(name);
    if (it != m_cJniClassMap.end()) {
        return (*it).second;
    }

    return LoadClass(szClassName);
}

XJniClass *XJniMgr::LoadClass(const char *szClassName)
{
    JNIEnv *pEnv = GetJniEnv();
    string s(szClassName), sb(szClassName);
    string::size_type pos = 0;

    while((pos = s.find(".", pos)) != string::npos) {
        s.replace(pos, 1, "/");
        pos++;
    }
    LOGD("XJniMgr::LoadClass className=%s", s.c_str());

    if (NULL == pEnv) {
        LOGE("XJniMgr::LoadClass pEnv is NULL");
        return NULL;
    }

    XJniClass *pClass = new XJniClass;
    m_cJniClassMap.insert(std::pair<string,XJniClass*>(sb, pClass));
    jclass clazz = pEnv->FindClass(s.c_str());
    if (NULL == clazz) {
        LOGE("XJniMgr::LoadClass clazz is NULL");
        return NULL;
    }
    jclass newClazz = (jclass)pEnv->NewGlobalRef(clazz);
    if (NULL == newClazz) {
        LOGE("XJniMgr::LoadClass new global ref error");
        return NULL;
    }

    LOGD("XJniMgr::LoadClass class=%p global clazz ref=%p", clazz, newClazz);
    pClass->m_pcClass = newClazz;
    LoadFields(pEnv, newClazz, pClass);
    LoadMethods(pEnv, newClazz, pClass);

    return pClass;
}

void XJniMgr::LoadFields(JNIEnv *pEnv, jclass clazz, XJniClass *pInfo)
{
    LOGD("XJniMgr::LoadFields begin clazz=%p", clazz);
    jmethodID mid = pEnv->GetStaticMethodID(clazz, "getFields", "()[Ljava/lang/String;");
    if (!mid) {
        LOGE("XJniMgr::LoadFields mid not find");
        return;
    }

    jobject obj = pEnv->CallStaticObjectMethod(clazz, mid);
    if (!obj) {
        LOGD("XJniMgr::LoadFields call getFields(), no fields");
        return;
    }

    jobjectArray arr = (jobjectArray)obj;
    jint len = pEnv->GetArrayLength(arr);
    if ((len%3) != 0) {
        LOGE("XJniMgr::LoadFields len is not 3N");
        return;
    }

    const char *pItems[3] = {0};
    jstring jsItems[3] = {0};
    for (int i = 0; i < len; i+=3) {
        //list one field
        for (int j = i; j < 3+i; ++j) {
            jobject item = pEnv->GetObjectArrayElement(arr, j);
            if (!item) {
                LOGE("XJniMgr::LoadFields item is NULL i=%d,j=%d", i, j);
                goto _err;
            }

            jstring strItem = (jstring)item;
            jsItems[j-i] = strItem;
            const char *pStr = pEnv->GetStringUTFChars(strItem, NULL);
            pItems[j-i] = pStr;
            if (!pStr) {
                LOGE("XJniMgr::LoadFields pStr is NULL i=%d,j=%d", i, j);
                goto _err;
            }
        }

        //get filed id
        jfieldID fid = NULL;
        if (*pItems[2] == 'S') {
            fid = pEnv->GetStaticFieldID(clazz, pItems[0], pItems[1]);
        } else {
            fid = pEnv->GetFieldID(clazz, pItems[0], pItems[1]);
        }
        if (fid) {
            string s(pItems[0]);
            //fid = (jfieldID)pEnv->NewGlobalRef((jobject)fid);
            pInfo->m_cFields.insert(pair<string,void*>(s, (void*)fid));
        } else {
            LOGE("XJniMgr::LoadFields fid is NULL, field is '%s'", pItems[0]);
            goto _err;
        }

        //relase memory
        for (int j = 0; j < 3; ++j) {
            pEnv->ReleaseStringUTFChars(jsItems[j], pItems[j]);
        }
    }

_err:
    LOGD("XJniMgr::LoadFields end");
}

void XJniMgr::LoadMethods(JNIEnv *pEnv, jclass clazz, XJniClass *pInfo)
{
    LOGD("XJniMgr::LoadMethods begin clazz=%p", clazz);
    jmethodID mid = pEnv->GetStaticMethodID(clazz, "getMethods", "()[Ljava/lang/String;");
    if (!mid) {
        LOGE("XJniMgr::LoadMethods mid not find");
        return;
    }

    jobject obj = pEnv->CallStaticObjectMethod(clazz, mid);
    if (!obj) {
        LOGD("XJniMgr::LoadMethods call getMethods(), no methods");
        return;
    }
    LOGD("XJniMgr::LoadMethods obj=%p", obj);

    jobjectArray arr = (jobjectArray)obj;
    jint len = pEnv->GetArrayLength(arr);
    if ((len%3) != 0) {
        LOGE("XJniMgr::LoadMethods len is not 3N");
        return;
    }

    LOGD("XJniMgr::LoadMethods array length=%d", len);

    const char *pItems[3] = {0};
    jstring jsItems[3] = {0};
    for (int i = 0; i < len; i+=3) {
        //list one field
        for (int j = i; j < 3+i; ++j) {
            jobject item = pEnv->GetObjectArrayElement(arr, j);
            if (!item) {
                LOGE("XJniMgr::LoadMethods item is NULL i=%d,j=%d", i, j);
                goto _err;
            }

            jstring strItem = (jstring)item;
            jsItems[j-i] = strItem;
            const char *pStr = pEnv->GetStringUTFChars(strItem, NULL);
            pItems[j-i] = pStr;
            if (!pStr) {
                LOGE("XJniMgr::LoadMethods pStr is NULL i=%d,j=%d", i, j);
                goto _err;
            }
        }

        //get method id
        jmethodID fid = NULL;
        if (*pItems[2] == 'S') {
            fid = pEnv->GetStaticMethodID(clazz, pItems[0], pItems[1]);
        } else {
            fid = pEnv->GetMethodID(clazz, pItems[0], pItems[1]);
        }
        if (fid) {
            string s(pItems[0]);
            //注：jfieldID 和jmethodID不是一个引用(jclass是引用)，所以不能NewGlobalRef
            //fid = (jmethodID)pEnv->NewGlobalRef((jobject)fid);
            pInfo->m_cMethods.insert(pair<string,void*>(s, (void*)fid));
        } else {
            LOGE("XJniMgr::LoadMethods fid is NULL. pItems=[%s,%s,%s]", pItems[0], pItems[1], pItems[2]);
            goto _err;
        }

        //relase memory
        for (int j = 0; j < 3; ++j) {
            pEnv->ReleaseStringUTFChars(jsItems[j], pItems[j]);
        }
    }

_err:
    LOGD("XJniMgr::LoadMethods end");
}

#endif



