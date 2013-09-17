#ifndef XAPP_H
#define XAPP_H

#include <string>
using namespace std;

/**
 * 表示一个应用程序的实例
 */
class XApp
{
public:
    static XApp *Instance();

    /**
     * Get app work dir. If get faild, return ""
     */
    string GetWorkDir();

    /**
     *  Get app storage user file dir. If get faild, return ""
     *  The dir path is $(work-dir)/files
     */
    string GetAppFilesDir();

protected:
    XApp();

private:
    static XApp *s_ins;
};

#endif // APP_H
