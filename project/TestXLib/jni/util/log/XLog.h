#ifndef CXX_COM_LOG_H
#define CXX_COM_LOG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void LogDebug(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...);

void LogError(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...);

#define LOGD(fmt, ...) LogDebug("X", __FILE__, __FUNCTION__, __LINE__,fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) LogError("X", __FILE__, __FUNCTION__, __LINE__,fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif


