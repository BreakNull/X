#ifndef XPAGEFACTORY_H
#define XPAGEFACTORY_H

#include <map>
#include <string>
using namespace std;
class XPage;

/**
 * 创建页面工厂
 */
class XPageFactory
{
public:
    typedef XPage *(*NewFunc)(void *, const string &, int);

    static XPageFactory *Instance();

    /**
     * 根据xml文件名来创建一个Page对象, 若没有找到与xml文件名相对应的Page构造器
     *   则使用默认的Page::New来构造
     */
    XPage *New(void *pRealPage, const string &name, int id);

    /**
     * 注册一个Widget的New函数
     * @param name 标签名
     * @param fun New函数指针
     */
    void RegistNew(const string &name, NewFunc fun);

private:
    XPageFactory();

    static XPageFactory *s_ins;
    map<string, NewFunc> m_cMap;
};

#endif // PAGEFACTORY_H
