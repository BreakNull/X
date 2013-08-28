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

    /*
     * 删除data，释放内存。在HttpResponse对象被delete时，不会自动去删除data
     * 用户需要手动调用DeleteData() 来释放内存
     */
    void DeleteData();

    //Http response header
    HttpHeader &GetHeader() {return m_header;}

    string GetContentType();
    string GetContentEncoding();
    int GetContentLength();

private:
    void *m_pData;
    HttpHeader m_header;
};

#endif // HTTPRESPONSE_H
