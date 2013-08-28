#include "HttpRequest.h"
#include "HttpRequestManager.h"

static int s_iReqId = 0;

HttpRequest::HttpRequest(const string &url, METHOD m)
    :m_bCloseWhenPageLeave(true)
    ,m_url(url)
    ,m_eMethod(m)
    ,m_callback(NULL)
{
    m_iReqId = ++s_iReqId ;
}
