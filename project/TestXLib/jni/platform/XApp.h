#ifndef XAPP_H
#define XAPP_H

/**
 * 表示一个应用程序的实例
 */
class XApp
{
public:
    static XApp *Instance();

protected:
    XApp();

private:
    static XApp *s_ins;
};

#endif // APP_H
