#ifndef XWIDGETFACTORY_H
#define XWIDGETFACTORY_H

#include <map>
#include <string>
class XWidget;
class XPage;

using namespace std;

class XWidgetFactory
{
public:
    typedef XWidget *(*NewFunc)(XPage *);

    static XWidgetFactory *Instance();

    /**
     * 根据标签名来创建一个Widget对象，此标签名就是xml中的标签
     */
    XWidget *New(const string &name, XPage *p);

    /**
     * 注册一个Widget的New函数
     * @param name 标签名
     * @param fun New函数指针
     */
    void RegistNew(const string &name, NewFunc fun);

private:
    XWidgetFactory();
    map<string, NewFunc> m_cMap;
    static XWidgetFactory *s_ins;
};

#endif // WIDGETFACTORY_H
