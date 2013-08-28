#include "XVariant.h"
#include <sstream>
#include <string.h>

using namespace std;

#define SET_OK(r) if (ok) *ok = (r)

XVariant::XVariant()
{
    m_eType = VT_NONE;
}

XVariant::XVariant(const XVariant &v)
{
    m_eType = v.m_eType;
    memcpy(&_val, &v._val, sizeof(_val));
    if (m_eType == VT_STRING) {
        SetString(v._val.pcVal);
    }
}

XVariant &XVariant::operator=(const XVariant &v)
{
    m_eType = v.m_eType;
    memcpy(&_val, &v._val, sizeof(_val));
    if (m_eType == VT_STRING) {
        SetString(v._val.pcVal);
    }
    return *this;
}

XVariant::~XVariant()
{
    if (m_eType == VT_STRING) {
        delete[] _val.pcVal;
    }
}

XVariant::XVariant(const char *pcVal)
{
    m_eType = VT_STRING;
    SetString(pcVal);
}

XVariant::XVariant(char *pcVal)
{
    m_eType = VT_STRING;
    SetString(pcVal);
}

XVariant::XVariant(int val)
{
    m_eType = VT_INT;
	_val.iVal = val;
}

XVariant::XVariant(long long val)
{
    m_eType = VT_LONG_LONG;
	_val.llVal = val;
}

XVariant::XVariant(double val)
{
    m_eType = VT_DOUBLE;
    _val.dVal = val;

}

XVariant::XVariant(float val)
{
    m_eType = VT_FLOAT;
	_val.fVal = val;
}

XVariant::XVariant(bool val)
{
    m_eType = VT_BOOL;
	_val.bVal = val;
}

XVariant::XVariant(void *val)
{
    m_eType = VT_INT;
    _val.pVal = val;
}

bool XVariant::IsValid()
{
    if (m_eType == VT_NONE) {
		return false;
	}

	return true;
}

std::string XVariant::ToString() const
{
    char buf[20] = {0};

    switch (m_eType) {
    case VT_STRING:
        return _val.pcVal;

    case VT_INT:
        sprintf(buf, "%d", _val.iVal);
        return buf;

    case VT_LONG_LONG:
        sprintf(buf, "%ld", _val.llVal);
        return buf;

    case VT_DOUBLE:
        sprintf(buf, "%f", _val.dVal);
        return buf;

    case VT_FLOAT:
        sprintf(buf, "%f", _val.fVal);
        return buf;

    case VT_BOOL:
        return _val.bVal ? "true" : "false";

    case VT_POINTER:
        sprintf(buf, "%p", _val.pVal);
        return buf;
	}
    return "";
}

int XVariant::ToInt(bool *ok) const
{
    return (int)ToLongLong(ok);
}

static bool IsNum(const char *p)
{
    if (!p || *p == '\0') {
        return false;
    }
    if (*p == '-') {
        ++p;
    }
    while (*p >= '0' && *p <= '9') {
        ++p;
    }
    return *p == '\0';
}

static bool IsFloat(const char *p)
{
    if (!p || *p == '\0') {
        return false;
    }
    if (*p == '-') {
        ++p;
    }
    while (*p >= '0' && *p <= '9') {
        ++p;
    }
    if (*p == '.') {
        ++p;
        while (*p >= '0' && *p <= '9') {
            ++p;
        }
    }
    return *p == '\0';
}

long long XVariant::ToLongLong(bool *ok) const
{
    long long ret = 0;

    switch (m_eType) {
    case VT_STRING:
        if (IsNum(_val.pcVal)) {
            SET_OK(true);
            stringstream ss;
            ss << _val.pcVal;
            ss >> ret;
        } else {
            SET_OK(false);
        }
        return ret;

    case VT_INT:
        SET_OK(true);
        return _val.iVal;

    case VT_LONG_LONG:
        SET_OK(true);
        return _val.llVal;

    case VT_DOUBLE:
        SET_OK(true);
        return (long long)_val.dVal;

    case VT_FLOAT:
        SET_OK(true);
        return (long long)_val.fVal;

    case VT_BOOL:
        SET_OK(true);
        return _val.bVal ? 1 : 0;

    case VT_POINTER:
        SET_OK(false);
        return 0;
    }

    SET_OK(false);
    return 0;
}

double XVariant::ToDouble(bool *ok) const
{
    double ret = 0;

    switch (m_eType) {
    case VT_STRING:
        if (IsFloat(_val.pcVal)) {
            SET_OK(true);
            stringstream ss;
            ss << _val.pcVal;
            ss >> ret;
        } else {
            SET_OK(false);
        }
        return ret;

    case VT_INT:
        SET_OK(true);
        return _val.iVal;

    case VT_LONG_LONG:
        SET_OK(true);
        return (double)_val.llVal;

    case VT_DOUBLE:
        SET_OK(true);
        return _val.dVal;

    case VT_FLOAT:
        SET_OK(true);
        return _val.fVal;

    case VT_BOOL:
        SET_OK(true);
        return _val.bVal ? 1 : 0;

    case VT_POINTER:
        SET_OK(false);
        return 0;
    }

    SET_OK(false);
    return 0;
}


float XVariant::ToFloat(bool *ok) const
{
    return (float)ToDouble(ok);
}

bool XVariant::ToBool(bool *ok) const
{
    switch (m_eType) {
    case VT_STRING:
        SET_OK(false);
        return false;

    case VT_INT:
        SET_OK(true);
        return _val.iVal != 0;

    case VT_LONG_LONG:
        SET_OK(true);
        return _val.llVal != 0;

    case VT_DOUBLE:
        SET_OK(true);
        return _val.dVal != 0;

    case VT_FLOAT:
        SET_OK(true);
        return _val.fVal != 0;

    case VT_BOOL:
        SET_OK(true);
        return _val.bVal;

    case VT_POINTER:
        SET_OK(false);
        return false;
    }

    SET_OK(false);
    return false;
}

void *XVariant::ToPointer() const
{
    if (m_eType == VT_POINTER) {
        return _val.pVal;
	}

    return NULL;
}

void XVariant::SetString(const char *pcVal)
{
    if (pcVal) {
        _val.pcVal = new char[strlen(pcVal) + 1];
        strcpy(_val.pcVal, pcVal);
    } else {
        _val.pcVal = NULL;
    }
}


