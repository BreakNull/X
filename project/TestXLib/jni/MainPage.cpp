#include "MainPage.h"
#include "XLog.h"
#include "XWidget.h"

MainPage::MainPage(void *pRealPage, const string &name, int id)
:XPage(pRealPage, name, id)
{
    m_idx = 0;
}

void MainPage::OnClick(const string &id)
{
	LOGD("widget id=%s", id.c_str());
	XWidget *pBtn = FindById(id);
	if (pBtn == NULL) {
		LOGE("not find widget, id=%s", id.c_str());
		return;
	}
    ++m_idx;
    char buf[50] = {0};
    sprintf(buf, "Click %d times", m_idx);
    pBtn->SetProperty(this, "txt", buf);
}
