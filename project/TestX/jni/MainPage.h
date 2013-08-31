#ifndef MA_H
#include "XPage.h"

class MainPage : public XPage 
{
public:
	MainPage(void *pRealPage, const string &name, int id);

    PAGE_NEW(MainPage)
	
	virtual void OnClick(const string &id);

private:
    int m_idx;
};

#endif
