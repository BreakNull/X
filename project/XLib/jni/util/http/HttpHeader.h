#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <vector>

using namespace std;
class HttpHeaderItem
{
public:
    HttpHeaderItem();
    HttpHeaderItem(string strFiledName, string strFiledValue);

    string GetFiledName() {return m_strFiledName;}
    string GetFiledValue() {return m_strFiledValue;}
private:
    string m_strFiledName;
    string m_strFiledValue;
};

class HttpHeader
{
public:
    HttpHeader();

    void Add(const string &name, const string &value);
    int Size();
    string GetValue(const string &name);
    string GetName(int idx);
    string GetValue(int idx);

private:
    vector<HttpHeaderItem> m_cHeaders;
};

#endif // HTTPHEADER_H
