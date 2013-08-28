#include "MainPage.h"
#include "XLog.h"
#include "XWidget.h"

MainPage::MainPage(void *pRealPage, const string &name, int id)
:XPage(pRealPage, name, id)
{
}

void MainPage::OnClick(const string &id)
{
	LOGD("widget id=%s", id.c_str());
	XWidget *pBtn = FindById(id);
	if (pBtn == NULL) {
		LOGE("not find widget, id=%s", id.c_str());
		return;
	}
	pBtn->SetProperty(this, "txt", "You clicked me");
}