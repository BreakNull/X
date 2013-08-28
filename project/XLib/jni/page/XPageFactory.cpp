#include "XPageFactory.h"
#include "XPage.h"
#include "XLog.h"

XPageFactory *XPageFactory::s_ins;

XPageFactory::XPageFactory()
{
}

XPageFactory *XPageFactory::Instance()
{
    if (!s_ins) {
        s_ins = new XPageFactory;
    }
    return s_ins;
}

XPage *XPageFactory::New(void *pRealPage, const string &name, int id)
{
    if (name.empty() || !pRealPage) {
        LOGE("XPageFactory::New arg is invlaid. name=%s, pRealPage=%p, id=%d", name.c_str(), pRealPage, id);
        return NULL;
    }

    map<string, NewFunc>::iterator it = m_cMap.find(name);
    if (it == m_cMap.end()) {
        LOGD("XPageFactory::New not find %s::New, use default XPage::New", name.c_str());
        return XPage::New(pRealPage, name, id);
    }

    NewFunc fun = (*it).second;
    if (NULL != fun) {
        return fun(pRealPage, name, id);
    }
    LOGE("XPageFactory::New find %s::New, but its NULL", name.c_str());
    return NULL;
}

void XPageFactory::RegistNew(const string &name, NewFunc fun)
{
    if (NULL == fun || name.empty()) {
        //TODO: print log
        return;
    }
    m_cMap.insert(pair<string,NewFunc>(name, fun));
}


