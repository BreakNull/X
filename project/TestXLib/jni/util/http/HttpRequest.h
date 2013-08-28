#ifndef HTTP_H
#define HTTP_H

#include <string>
#include "HttpHeader.h"
class HttpResponse;
class HttpRequest;
using namespace std;

typedef void (*HttpReqCallback)(HttpRequest*, HttpResponse*);

class HttpRequest
{
public:
    enum METHOD {
        M_GET,
        M_POST
    };

    HttpRequest(const string &url, METHOD m = M_GET);

    //请求id
    int GetReqId() {return m_iReqId;}
    HttpHeader &GetHeader() {return m_cHeader;}

    //当页面离开时， 是否关闭连接。默认为true
    bool GetCloseWhenPageLeave() {return m_bCloseWhenPageLeave;}
    void SetCloseWhenPageLeave(bool b) {m_bCloseWhenPageLeave = b;}

    METHOD GetMethod() {return m_eMethod;}

    //获得与页面相关的页面id
    int GetRelationPageId() {return m_iRelationPageId;}
    void SetRelationPageId(int id) {m_iRelationPageId = id;}    

    HttpReqCallback GetCallback() {return m_callback;}
    void SetCallBack(HttpReqCallback cb) {m_callback = cb;}

protected:
    METHOD m_eMethod;
    string m_url;
    bool m_bCloseWhenPageLeave;
    int m_iRelationPageId;
    int m_iReqId;
    HttpHeader m_cHeader;
    HttpReqCallback m_callback;
};

#endif // HTTP_H
