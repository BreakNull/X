#include "NiPage.h"
#include "XLog.h"
#include "XWidget.h"
#include "XPageMgr.h"
#include "XButton.h"
#include "XFile.h"
#include <stdio.h>

NiPage::NiPage(void *pRealPage, const string &name, int id)
:XPage(pRealPage, name, id)
{
    m_idx = 0;
}

void NiPage::OnClick(const string &id)
{
    if (id == "go_world") {
        XFile f("ni.dat");
        FILE *pf = fopen(f.GetPath().c_str(), "rb+");
        const char *str = "Hello ni page\n";
        fwrite(str, strlen(str), 1, pf);
        fclose(pf);

        XPageMgr::Instance()->LoadNewPage("WorldPage", XPageMgr::A_TOP_IN|XPageMgr::A_BOTTOM_OUT);
    }
}
