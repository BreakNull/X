#ifndef CXX_COM_LOG_H
#define CXX_COM_LOG_H

#include <stdarg.h>


void XLogDebug(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...);
void XLogError(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...);

#define LOGD(fmt, ...) XLogDebug("X", __FILE__, __FUNCTION__, __LINE__,fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) XLogError("X", __FILE__, __FUNCTION__, __LINE__,fmt, ##__VA_ARGS__)



#endif


