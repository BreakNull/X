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
    page/XPageManager.cpp \
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
    util/tinyxml/xpath_syntax.cpp \
    util/tinyxml/xpath_stream.cpp \
    util/tinyxml/xpath_static.cpp \
    util/tinyxml/xpath_stack.cpp \
    util/tinyxml/xpath_processor.cpp \
    util/tinyxml/xpath_expression.cpp \
    util/tinyxml/xml_util.cpp \
    util/tinyxml/tokenlist.cpp \
    util/tinyxml/tinyxmlparser.cpp \
    util/tinyxml/tinyxmlerror.cpp \
    util/tinyxml/tinyxml.cpp \
    util/tinyxml/tinystr.cpp \
    util/tinyxml/node_set.cpp \
    util/tinyxml/lex_util.cpp \
    util/tinyxml/htmlutil.cpp \
    util/tinyxml/action_store.cpp \
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
    util/style/XStyle.cpp

HEADERS +=\
    page/XPage.h \
    page/XPageFactory.h \
    page/XPageManager.h \
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
    util/tinyxml/xpath_syntax.h \
    util/tinyxml/xpath_stream.h \
    util/tinyxml/xpath_static.h \
    util/tinyxml/xpath_stack.h \
    util/tinyxml/xpath_processor.h \
    util/tinyxml/xpath_expression.h \
    util/tinyxml/xml_util.h \
    util/tinyxml/tokenlist.h \
    util/tinyxml/tinyxpath_conf.h \
    util/tinyxml/tinyxml.h \
    util/tinyxml/tinystr.h \
    util/tinyxml/node_set.h \
    util/tinyxml/lex_util.h \
    util/tinyxml/lex_token.h \
    util/tinyxml/htmlutil.h \
    util/tinyxml/byte_stream.h \
    util/tinyxml/action_store.h \
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
    util/style/XStyle.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
