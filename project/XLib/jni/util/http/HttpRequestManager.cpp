#include "HttpRequestManager.h"
#include "HttpRequest.h"
#include "XAutoMutex.h"

HttpRequestManager *HttpRequestManager::s_ins = NULL;

HttpRequestManager::HttpRequestManager()
{
    m_reqList.clear();
}

HttpRequestManager *HttpRequestManager::Instance()
{
    if (!s_ins) {
        s_ins = new HttpRequestManager;
    }
    return s_ins;
}

void HttpRequestManager::PostRequest(HttpRequest *pReq)
{
    if (!pReq) {
        return;
    }

    {
        XAutoMutex cAutoSync(m_cSyncReqList);
        m_reqList.push_back(pReq);
    }
}

void
HttpRequestManager::Cancel(HttpRequest *pReq)
{
    if (!pReq) {
        return;
    }

    {
        XAutoMutex cAutoSync(m_cSyncReqList);

        vector<HttpRequest*>::iterator iter = m_reqList.begin();
        for (; iter != m_reqList.end(); )
        {
            HttpRequest *pCurReq = *iter;
            if ( pReq->GetReqId() == pCurReq->GetReqId())
            {
                m_reqList.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

void HttpRequestManager::Run()
{

}



