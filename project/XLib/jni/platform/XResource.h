#ifndef XRESOURCE_H
#define XRESOURCE_H

#include <string>
using namespace std;

/**
 * 资源
 */
class XResource
{
public:

    /**
     * 解析url得到一个资源
     * @param url 可支持的格式有：
     *               plt:xxx            平台系统的资源名称
     *               loc:/dir1/xxx      本地文件系统(绝对路径)
     *               app:dir1/xxx       以应用程序所在的路径作为根路径的本地文件系统
     */
    static XResource *Parse(const std::string &url);
    string GetName();

private:
    XResource();
};

#endif // RESOURCE_H
