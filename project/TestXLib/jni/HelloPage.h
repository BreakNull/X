#ifndef MA_H
#include "XPage.h"

class HelloPage : public XPage 
{
public:
	HelloPage(void *pRealPage, const string &name, int id);

    PAGE_NEW(HelloPage)
	
	virtual void OnClick(const string &id);

private:
    int m_idx;
};

#endif
