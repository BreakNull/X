#ifndef MA_H
#include "XPage.h"

class NiPage : public XPage
{
public:
    NiPage(void *pRealPage, const string &name, int id);

    PAGE_NEW(NiPage)
	
	virtual void OnClick(const string &id);

private:
    int m_idx;
};

#endif
