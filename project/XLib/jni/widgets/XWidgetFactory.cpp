#include "XWidgetFactory.h"

XWidgetFactory *XWidgetFactory::s_ins = NULL;

XWidgetFactory::XWidgetFactory()
{
}

XWidgetFactory *XWidgetFactory::Instance()
{
    if (!s_ins) {
        s_ins = new XWidgetFactory();
    }
    return s_ins;
}

XWidget *XWidgetFactory::New(const string &name, XPage *p)
{
    map<string, NewFunc>::iterator it = m_cMap.find(name);
    if (it != m_cMap.end()) {
        NewFunc fun = (*it).second;
        if (NULL != fun) {
            return fun(p);
        }
    }
    return NULL;
}

void XWidgetFactory::RegistNew(const string &name, NewFunc fun)
{
    if (NULL == fun || name.empty()) {
        //TODO: log error
        return;
    }
    m_cMap.insert(pair<string,NewFunc>(name, fun));
}
