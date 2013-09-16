#include "XFile.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "XLog.h"

XFile::XFile(const string &name)
{
    m_cPath = RegularizName(name);
    m_pListDir = NULL;
}

void XFile::SetPath(const string &path)
{
    m_cPath = RegularizName(path);
}

bool XFile::IsDir()
{
    struct stat buf;
    int r = 0;
    r= stat(m_cPath.c_str(), &buf);
    if (!r && (buf.st_mode & S_IFDIR)) {
        return true;
    }
    return false;
}

bool XFile::IsExists()
{
    return access(m_cPath.c_str(), F_OK) == 0;
}

bool XFile::Remove()
{
    if (IsDir()) {
        return RemoveDir();
    }
    return unlink(m_cPath.c_str()) == 0;
}

bool XFile::RemoveDir()
{
    XFile f(m_cPath);
    if (!f.OpenDir()) {
        LOGE("open dir='%s' error", f.GetPath().c_str());
        return false;
    }
    const char *pName = NULL;
    bool b = true;
    while (pName = f.GetNextChildFileName()) {
        XFile ft(f.GetPath() + "/" + string(pName));
        b = ft.Remove();
        if (!b) {
            break;
        }
    }
    return false;
}

bool XFile::MakeDir(const string &dir)
{
    string n = RegularizName(dir);
    if (n.empty()) {
        LOGE("no dir name");
        return false;
    }

    XFile f(m_cPath);
    const char *pB = n.c_str();
    const char *pE = pB;
    const char *pEnd = pB + strlen(pB);
    char path[256];
    while (pB < pEnd && pE < pEnd) {
        pE = strchr(pB, '/');
        if (pE == NULL) {
            pE = pEnd;
        }
        if (pE == pB) {
            strcpy(path, "/");
        } else {
            memcpy(path, pB, pE - pB);
            path[pE-pB] = 0;
        }
        ++pE;
        pB = pE;
        f.Cd(path);
        if (!f.IsExists()) {
            int r = mkdir(f.GetPath().c_str(), 0777);
            if (r != 0) {
                return false;
            }
        }
    }
    return true;
}



bool XFile::Cd(const string &dir)
{
    string n = RegularizName(dir);
    if (n.empty()) {
        LOGE("dir is empty");
        return false;
    }

    XFile f;
    string p;
    if (*n.c_str() == '/') {
        p = n;
    } else {
        p = m_cPath + "/" + n;
    }
    f.SetPath(p);
    if (f.IsExists()) {
        m_cPath = p;
        return true;
    }
    return false;
}

bool XFile::OpenDir()
{
    m_pListDir = (void*)opendir(m_cPath.c_str());
    return m_pListDir != NULL;
}

const char *XFile::GetNextChildFileName()
{
    if (m_pListDir) {
        return NULL;
    }
    while (true) {
        struct dirent * pd = readdir((DIR*)m_pListDir);
        if (pd == NULL) {
            return NULL;
        }
        if (strcmp(".", pd->d_name) && strcmp("..", pd->d_name)) {
            return pd->d_name;
        }
    }
    return NULL;
}

void XFile::CloseDir()
{
    if (m_pListDir) {
        closedir((DIR*)m_pListDir);
        m_pListDir = NULL;
    }
}

string XFile::RegularizName(const string &name)
{
    if (name.empty()) {
        return "";
    }
    char *pBuf = new char[name.length() + 1];
    strcpy(pBuf, name.c_str());
    char *p = pBuf;
    while (p != NULL) {
        p = strchr(p, '\\');
        if (p)
            *p = '/';
    }
    char *pB = pBuf;
    for (; *pB && isspace(*pB); ++pB);
    char *pE = pBuf + name.length() - 1;
    for (; pE >= pB && isspace(*pE); --pE) {
        *pE = '\0';
    }
    while (pE > pB && *pE == '/') {
        *pE = '\0';
        --pE;
    }

    string tmp(pB);
    delete pBuf;
    return tmp;
}


