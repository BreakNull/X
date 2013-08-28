#include "HttpHeader.h"

HttpHeaderItem::HttpHeaderItem()
    :   m_strFiledName("")
    ,   m_strFiledValue("")
{
}

HttpHeaderItem::HttpHeaderItem(string strFiledName, string strFiledValue)
    :   m_strFiledName(strFiledName)
    ,   m_strFiledValue(strFiledValue)
{
}

HttpHeader::HttpHeader()
{
    m_cHeaders.clear();
}

int HttpHeader::Size()
{
    return m_cHeaders.size();
}

string HttpHeader::GetValue(const string &name)
{
    for (int i = 0; i < Size(); ++i) {
        HttpHeaderItem item = m_cHeaders.at(i);
        if (name == item.GetFiledName()) {
            return item.GetFiledValue();
        }
    }

    return "";
}

string HttpHeader::GetName(int idx)
{
    if (idx < 0 || idx >= Size()) {
        return "";
    }

    HttpHeaderItem item = m_cHeaders.at(idx);
    return item.GetFiledName();
}

string HttpHeader::GetValue(int idx)
{
    if (idx < 0 || idx >= Size()) {
        return "";
    }

    HttpHeaderItem item = m_cHeaders.at(idx);
    return item.GetFiledValue();
}

void HttpHeader::Add(const string &name, const string &value)
{
    HttpHeaderItem item(name, value);
    m_cHeaders.push_back(item);
}


