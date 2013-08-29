#include "Init.h"
#include "XLog.h"
#include "XWidgetFactory.h"
#include "XLabel.h"
#include "XButton.h"
#include "XLineLayout.h"
#include "XCheckBox.h"
#include "XDatePicker.h"
#include "XGridLayout.h"
#include "XGridView.h"
#include "XImageButton.h"
#include "XImageView.h"
#include "XInput.h"
#include "XMenu.h"
#include "XProgressBar.h"
#include "XRadio.h"
#include "XRadioGroup.h"
#include "XRatingBar.h"
#include "XScrollView.h"
#include "XSeekBar.h"
#include "XSpinner.h"
#include "XTab.h"
#include "XTimePicker.h"
#include "XToast.h"

static void InitWidgetFactory();

#ifdef _FOR_ANDROID_
#include "XJniMgr.h"
#include "jni.h"
#include "XJniPage.h"
#include "XJniUiThreadRunnable.h"
#include <android/log.h>

static JNINativeMethod GetNativeMethod(const char *pName, const char *pSig, void *func)
{
    JNINativeMethod m;
    m.name = pName;
    m.signature = pSig;
    m.fnPtr = func;

    return m;
}

static void RegisterNativPageMethod(JNIEnv *pEnv)
{
    //LOGD("Init->RegisterNativPageMethod");
    XJniMgr *pMgr = XJniMgr::Instance();
    jclass pageclazz = (jclass)pMgr->GetClass("x.core.ui.JPage");
    if (!pageclazz) {
        LOGE("Init->RegisterNativPageeMethod fail, not find x.core.ui.JPage");
        return;
    }

    int i = 0;
    JNINativeMethod methods[30];
    methods[i++] = GetNativeMethod("GetStyle", "(I)I", (void*)XJniPage::GetStyle);
    methods[i++] = GetNativeMethod("OnNew", "(Ljava/lang/String;I)V", (void*)XJniPage::OnNew);
    methods[i++] = GetNativeMethod("OnCreate", "(I)Ljava/lang/Object;", (void*)XJniPage::OnCreate);
    methods[i++] = GetNativeMethod("OnDestroy", "(I)V", (void*)XJniPage::OnDestroy);
    methods[i++] = GetNativeMethod("OnStart", "(I)V", (void*)XJniPage::OnStart);
    methods[i++] = GetNativeMethod("OnStop", "(I)V", (void*)XJniPage::OnStop);
    methods[i++] = GetNativeMethod("OnClick", "(ILjava/lang/String;)V", (void*)XJniPage::OnClick);
    methods[i++] = GetNativeMethod("OnTimeChanged", "(ILjava/lang/String;II)V", (void*)XJniPage::OnTimeChanged);
    methods[i++] = GetNativeMethod("OnDateChanged", "(ILjava/lang/String;III)V", (void*)XJniPage::OnDateChanged);

    methods[i++] = GetNativeMethod("OnCreateOptionsMenu", "(ILjava/lang/Object;)Z", (void*)XJniPage::OnCreateOptionsMenu);
    methods[i++] = GetNativeMethod("OnOptionsItemSelected", "(II)V", (void*)XJniPage::OnOptionsItemSelected);
    jint num = pEnv->RegisterNatives(pageclazz, methods, i);

    //LOGD("Init->RegisterNativPageMethod register natives num=%d", num);
}

static void RegisterNativUiThreadRunnableMethod(JNIEnv *pEnv)
{
    //LOGD("Init->RegisterNativUiThreadRunnableMethod");
    XJniMgr *pMgr = XJniMgr::Instance();
    jclass pageclazz = (jclass)pMgr->GetClass("x.core.ui.UiThreadRunnable");
    if (!pageclazz) {
        LOGE("Init->RegisterNativUiThreadRunnableMethod fail, not find x.core.ui.UiThreadRunnable");
        return;
    }

    int i = 0;
    JNINativeMethod methods[30];
    methods[i++] = GetNativeMethod("Run", "(JJ)V", (void*)XJniUiThreadRunnable::Run);
    jint num = pEnv->RegisterNatives(pageclazz, methods, i);

    //LOGD("Init->RegisterNativUiThreadRunnableMethod register natives num=%d", num);
}

bool InitXLib(JavaVM *pJavaVm, void *reserved)
{
    LOGD("Init->JniOnLoad -- begin");
    XJniMgr::Instance()->SetJavaVM(pJavaVm);
    JNIEnv* env = NULL;

    env = (JNIEnv*)XJniMgr::Instance()->GetJniEnv();
    if (NULL == env) {
        LOGE("Init->JniOnLoad fail, env is NULL");
        return false;
    }
    RegisterNativPageMethod(env);
    RegisterNativUiThreadRunnableMethod(env);
    InitWidgetFactory();
    LOGD("Init->JniOnLoad -- end");

    return true;
}

#else // for iphone

bool InitXLib()
{
    InitWidgetFactory();
}

#endif //android end

static void InitWidgetFactory()
{
    XWidgetFactory *pFac = XWidgetFactory::Instance();

    pFac->RegistNew("Btn", XButton::New);
    pFac->RegistNew("Lab", XLabel::New);
    pFac->RegistNew("LineLay", XLineLayout::New);
    pFac->RegistNew("CheckBox", XCheckBox::New);
    pFac->RegistNew("DatePicker", XDatePicker::New);
    pFac->RegistNew("GridLay", XGridLayout::New);
    pFac->RegistNew("GridView", XGridView::New);
    pFac->RegistNew("ImgBtn", XImageButton::New);
    pFac->RegistNew("ImgView", XImageView::New);
    pFac->RegistNew("Input", XInput::New);
    pFac->RegistNew("Menu", XMenu::New);
    pFac->RegistNew("ProgressBar", XProgressBar::New);
    pFac->RegistNew("Radio", XRadio::New);
    pFac->RegistNew("RadioGroup", XRadioGroup::New);
    pFac->RegistNew("RatingBar", XRatingBar::New);
    pFac->RegistNew("Scroll", XScrollView::New);
    pFac->RegistNew("SeekBar", XSeekBar::New);
    pFac->RegistNew("Spinner", XSpinner::New);
    pFac->RegistNew("Tab", XTab::New);
    pFac->RegistNew("TimePicker", XTimePicker::New);
    pFac->RegistNew("Toast", XToast::New);
}

static XPageXml *s_pageXml;
XPageXml *GetXPageXml()
{
    return s_pageXml;
}

void SetXPageXml(XPageXml *p)
{
    s_pageXml = p;
}
