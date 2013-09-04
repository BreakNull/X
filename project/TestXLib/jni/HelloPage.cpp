#include "HelloPage.h"
#include "XLog.h"
#include "XWidget.h"
#include "XPageMgr.h"
#include "XButton.h"

HelloPage::HelloPage(void *pRealPage, const string &name, int id)
:XPage(pRealPage, name, id)
{
    m_idx = 0;
}

void HelloPage::OnClick(const string &id)
{
	LOGD("widget id=%s", id.c_str());
	void *pBtn = FindById(id, NULL);
	LOGD("widget id=%s, find=%p", id.c_str(), pBtn);
	if (pBtn == NULL) {
		LOGE("not find widget, id=%s", id.c_str());
		return;
	}
	if (id == "go_ni") {
        XPageMgr::Instance()->LoadNewPage("NiPage", 2);
		return;
	}
	LOGD("find widget=%p", pBtn);
    ++m_idx;
    char buf[50] = {0};
    sprintf(buf, "Click %d times", m_idx);
	XButton btn(this);
	btn.SetRealWidget(pBtn);
    btn.SetProperty("txt", buf);
}
