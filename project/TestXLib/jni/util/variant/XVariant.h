#ifndef XVARIANT_H
#define XVARIANT_H

#include <string>

class XVariant
{
public:
    enum TYPE {
        VT_NONE = 0,
        VT_STRING,
        VT_INT,
        VT_LONG_LONG,
        VT_DOUBLE,
        VT_FLOAT,
        VT_BOOL,
        VT_POINTER
    };

    //使用无参构造函数构造出来的Variant，默认是无效的
    XVariant();
    XVariant(const XVariant &v);
    XVariant &operator=(const XVariant &v);
    ~XVariant();

    XVariant(const char *pcVal);
    XVariant(char *pcVal);
    XVariant(int val);
    XVariant(long long val);
    XVariant(double val);
    XVariant(float val);
    XVariant(bool val);
    XVariant(void *val);

    //此Variant是否是有效的
    bool IsValid();
    TYPE GetType() {return m_eType;}

    std::string ToString() const;
    int ToInt(bool *ok = 0) const;
    long long ToLongLong(bool *ok = 0) const;
    double ToDouble(bool *ok = 0) const;
    float ToFloat(bool *ok = 0) const;
    bool ToBool(bool *ok = 0) const;
    void *ToPointer() const;

private:
    void SetString(const char *p);

private:
    TYPE m_eType;
    union {
        int iVal;
        long long llVal;
        double dVal;
        float fVal;
        bool bVal;
        void* pVal;
        char *pcVal;
    } _val;
};

#endif // VARIANT_H
