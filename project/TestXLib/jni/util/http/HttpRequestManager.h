#ifndef HTTPREQUESTMANAGER_H
#define HTTPREQUESTMANAGER_H

#include "XThread.h"
#include "XSyncObj.h"

#include <vector>
using namespace std;

class HttpRequest;
class HttpRequestManager : public XThread
{
public:
    static HttpRequestManager *Instance();

    //发送请求
    void PostRequest(HttpRequest *pReq);
    //取消请求
    void Cancel(HttpRequest *pReq);

protected:
    virtual int Run();

private:
    HttpRequestManager();

private:
    static HttpRequestManager *s_ins;

    XSyncObj m_cSyncReqList;
    vector<HttpRequest*> m_reqList;
};

#endif // HTTPREQUESTMANAGER_H
