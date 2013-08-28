#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "HttpHeader.h"

class HttpResponse
{
public:
    HttpResponse();
    ~HttpResponse();

    /**
     * 获得http响应的数据内容
     */
    void *GetData() {return m_pData;}
    void SetData(void *pData) {m_pData = pData;}

    //Http response header
    HttpHeader &GetHeader() {return m_header;}

    //当此response对象被删除时， 是否删除m_pData， 默认为true
    bool IsDeleteData() {return m_bDeleteData;}
    void SetDeleteData(bool b) {m_bDeleteData = b;}

    string GetContentType();
    string GetContentEncoding();
    int GetContentLength();

private:
    void *m_pData;
    HttpHeader m_header;
    bool m_bDeleteData;
};

#endif // HTTPRESPONSE_H
