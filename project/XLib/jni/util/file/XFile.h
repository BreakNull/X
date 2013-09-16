#ifndef XFILE_H
#define XFILE_H

#include <string>
using namespace std;

class XFile
{
public:
    XFile(const string &path = "");

    const string &GetPath() {return m_cPath;}
    void SetPath(const string &path);
    bool IsDir();
    bool IsExists();
    bool Remove();

    /**
     * @param dir canbe a xx or xx/yy/zz
     */
    bool MakeDir(const string &dir);

    /**
     * @param dir cd a dir, canbe a xx or xx/yy/zz or /xx/yy/zz
     */
    bool Cd(const string &dir);

    /**
     * 遍历目录下所有的文件/文件夹
     */
    bool OpenDir();
    const char *GetNextChildFileName();
    void CloseDir();

private:
    string RegularizName(const string &name);
    bool RemoveDir();
    string m_cPath;
    void *m_pListDir;
};

#endif // XFILE_H
