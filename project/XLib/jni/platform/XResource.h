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
     * @param url 可支持的格式有：
     *               plt:xxx            平台系统的资源名称
     *               loc:/dir1/xxx      本地文件系统(绝对路径)
     *               loc:dir1/xxx       本地文件系统(相对对路径，以应用程序所在的路径为根路径)
     */
    XResource(const string &url);

    /**
     * Note: you must free the buffer yourself
     * void *p = GetData();
     * free(p);
     */
    void *GetData();
    int GetDataLen();

private:
    enum DType {
        DT_NONE,
        DT_PLT,
        DT_LOC
    };

    void Load();
    void LoadFromFile();
    void LoadFromPlt();

    int m_iDatLen;
    void *m_pDat;
    DType m_eDt;
    bool m_bLoaded;
    string m_cAbsPath;
};

#endif // RESOURCE_H
