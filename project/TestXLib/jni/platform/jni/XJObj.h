#ifndef XJOBJ_H
#define XJOBJ_H

/**
 * 所有的java与c++类传递数据的类，都需要继承此类
 *
 * <1>.将java对像转成c++对象：
 *  void *pJavaObj = xxxx;
 *  JObj obj;
 *  obj.ToNativeObj(pJavaObj);  //此时已将java对象转成了一个人c++的JObj对象
 *
 * <2>.将c++对象转成java对象
 *  JObj *pObj = xxx;
 *  void *pJavaObj = pObj->ToJavaObj();  //在不使用时需要释放pJavaObj内存
 *
 */
class XJObj
{
public:
    XJObj();

    //创建此JObj对象的对应Java对象的实例
    virtual void *ToJavaObj() = 0;

    //将java对象的内容复制到此JObj对象中
    virtual void ToNativeObj(void *javaObj) = 0;
};



#endif // JOBJ_H
