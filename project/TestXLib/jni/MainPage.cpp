#include "MainPage.h"
#include "XLog.h"
#include "XWidget.h"
#include "XPageMgr.h"

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
	if (id == "go_world") {
		XPageMgr::Instance()->LoadNewPage("WorldPage", 1, 2);
		return;
	}
	LOGD("find widget=%p", pBtn);
    ++m_idx;
    char buf[50] = {0};
    sprintf(buf, "Click %d times", m_idx);
    pBtn->SetProperty("txt", buf);
}
