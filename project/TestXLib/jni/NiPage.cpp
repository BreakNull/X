#include "NiPage.h"
#include "XLog.h"
#include "XWidget.h"
#include "XPageMgr.h"
#include "XButton.h"

NiPage::NiPage(void *pRealPage, const string &name, int id)
:XPage(pRealPage, name, id)
{
    m_idx = 0;
}

void NiPage::OnClick(const string &id)
{
    if (id == "go_world") {
        XPageMgr::Instance()->LoadNewPage("WorldPage", 2);
    }
}
