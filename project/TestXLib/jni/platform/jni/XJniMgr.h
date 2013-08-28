#ifndef XJNIMGR_H
#define XJNIMGR_H

#ifdef _FOR_ANDROID_

#include <jni.h>
#include <map>
#include <string>
class XJniClass;

/**
 * Jni管理器, 用于管理java的class, field, method实例
 * 两种使用方法：
 * <1>. 由java类来实现静态的getFields, getMethods函数，
 *      那么Jni管理器将自动去装载java类中所有的函数,
 *      在任何时候都可调用GetClass, GetField, GetMethod来获得相应的对象
 *
 * <2>. 由用户去调用AddClass, AddField, AddMethod函数去初始化java类到此管理器中，
 *      之后即可调用GetClass, GetField, GetMethod来获得相应的对象
 */
class XJniMgr
{
public:
    static XJniMgr *Instance();

    /**
     *  获得一个java class
     *  如果不存在，将会自动创建一个新的java class，但此类应实现JObj接口,
     *  若没有实现JObj接口将不会创建此类的class，此时将会返回NULL
     *
     *  @param szClassName 类名，以点号分隔。如： com.pia.MyClass
     */
    jclass GetClass(const char *szClassName);
    jfieldID GetField(const char *szClassName, const char *szFieldName);
    jmethodID GetMethod(const char *szClassName, const char *szMethodName);

    void AddClass(const char *szClassName, jclass pClass);
    void AddField(const char *szClassName, const char *szFieldName, jfieldID pField);
    void AddMethod(const char *szClassName, const char *szMethodName, jmethodID pMethod);

    JNIEnv *GetJniEnv();
    JavaVM *GetJavaVM() {return m_pJavaVM;}
    void SetJavaVM(JavaVM *pVM) {m_pJavaVM = pVM;}

private:
    XJniMgr();
    XJniClass *LoadClass(const char *szClassName);
    XJniClass *GetJniClass(const char *szClassName);
    void LoadFields(JNIEnv *pEnv, jclass pClass, XJniClass *pInfo);
    void LoadMethods(JNIEnv *pEnv, jclass pClass, XJniClass *pInfo);

    static XJniMgr *s_pcIns;
    std::map<std::string, XJniClass*> m_cJniClassMap;
    JavaVM *m_pJavaVM;
};

#endif //_FOR_ANDROID_

#endif // JNIMGR_H
