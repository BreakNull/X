#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T10:25:05
#
#-------------------------------------------------

QT       -= core gui

TARGET = XLib
TEMPLATE = lib

DEFINES += XLIB_LIBRARY
INCLUDEPATH += .. http page platform schedule util util/datetime util/log \
		util/sqlite3 util/thread util/timer util/tinyxml util/variant \
		widgets platform/jni init

DEFINES += _FOR_ANDROID_

SOURCES += \
    page/XPage.cpp \
    page/XPageFactory.cpp \
    platform/XResource.cpp \
    platform/XPlatform.cpp \
    platform/XIntent.cpp \
    platform/XApp.cpp \
    platform/jni/XJObj.cpp \
    platform/jni/XJniMgr.cpp \
    widgets/XWidgetFactory.cpp \
    widgets/XWidget.cpp \
    widgets/XToast.cpp \
    widgets/XTimePicker.cpp \
    widgets/XTab.cpp \
    widgets/XSpinner.cpp \
    widgets/XSeekBar.cpp \
    widgets/XScrollView.cpp \
    widgets/XRatingBar.cpp \
    widgets/XRadioGroup.cpp \
    widgets/XRadio.cpp \
    widgets/XProgressBar.cpp \
    widgets/XMenu.cpp \
    widgets/XLineLayout.cpp \
    widgets/XLabel.cpp \
    widgets/XInput.cpp \
    widgets/XImageView.cpp \
    widgets/XImageButton.cpp \
    widgets/XGridView.cpp \
    widgets/XGridLayout.cpp \
    widgets/XFrameLayout.cpp \
    widgets/XDialog.cpp \
    widgets/XDatePicker.cpp \
    widgets/XCheckBox.cpp \
    widgets/XButton.cpp \
    platform/jni/XJniPage.cpp \
    platform/XPlatformAndroid.cpp \
    util/datetime/XDateTime.cpp \
    util/log/XLog.cpp \
    util/sqlite3/sqlite3.c \
    util/sqlite3/DataBaseOP.cpp \
    util/thread/XThread.cpp \
    util/thread/XSyncObj.cpp \
    util/thread/XAutoSync.cpp \
    util/timer/XTimerManager.cpp \
    util/timer/XTimer.cpp \
    util/variant/XVariant.cpp \
    init/Init.cpp \
    page/XPageXml.cpp \
    util/http/HttpResponse.cpp \
    util/http/HttpRequestManager.cpp \
    util/http/HttpRequest.cpp \
    util/http/HttpHeader.cpp \
    util/schedule/XBroadcaster.cpp \
    platform/XUiThread.cpp \
    util/schedule/XTaskSchedule.cpp \
    platform/jni/XJniUiThreadRunnable.cpp \
    util/style/XStyle.cpp \
    page/XPageMgr.cpp \
    util/oml/XmlElement.cpp \
    util/oml/XmlDocument.cpp \
    util/file/XFile.cpp

HEADERS +=\
    page/XPage.h \
    page/XPageFactory.h \
    platform/XResource.h \
    platform/XPlatform.h \
    platform/XIntent.h \
    platform/XApp.h \
    platform/jni/XJObj.h \
    platform/jni/XJniMgr.h \
    widgets/XWidgetFactory.h \
    widgets/XWidget.h \
    widgets/XToast.h \
    widgets/XTimePicker.h \
    widgets/XTab.h \
    widgets/XSpinner.h \
    widgets/XSeekBar.h \
    widgets/XScrollView.h \
    widgets/XRatingBar.h \
    widgets/XRadioGroup.h \
    widgets/XRadio.h \
    widgets/XProgressBar.h \
    widgets/XMenu.h \
    widgets/XLineLayout.h \
    widgets/XLabel.h \
    widgets/XInput.h \
    widgets/XImageView.h \
    widgets/XImageButton.h \
    widgets/XGridView.h \
    widgets/XGridLayout.h \
    widgets/XFrameLayout.h \
    widgets/XDialog.h \
    widgets/XDatePicker.h \
    widgets/XCheckBox.h \
    widgets/XButton.h \
    platform/jni/XJniPage.h \
    platform/XPlatformAndroid.h \
    http/HttpRequestManager.h \
    util/datetime/XDateTime.h \
    util/log/XLog.h \
    util/sqlite3/sqlite3ext.h \
    util/sqlite3/sqlite3.h \
    util/sqlite3/DataBaseOP.h \
    util/thread/XThread.h \
    util/thread/XSyncObj.h \
    util/thread/XAutoSync.h \
    util/timer/XTimerManager.h \
    util/timer/XTimer.h \
    util/variant/XVariant.h \
    init/Init.h \
    page/XPageXml.h \
    util/http/HttpResponse.h \
    util/http/HttpRequest.h \
    util/http/HttpHeader.h \
    util/schedule/XBroadcaster.h \
    platform/XUiThread.h \
    util/schedule/XTaskSchedule.h \
    platform/jni/XJniUiThreadRunnable.h \
    util/style/XStyle.h \
    page/XPageMgr.h \
    util/oml/XmlElement.h \
    util/oml/XmlDocument.h \
    util/file/XFile.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
