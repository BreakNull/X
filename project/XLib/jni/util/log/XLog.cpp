#include "XLog.h"
#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#ifdef _FOR_ANDROID_
#include <android/log.h>
#endif


#define MAXLOGSIZE 2000
#define BUF_SIZE 256
const int TERMINATE_CODE_SIZE		= 0;

#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

static char logfilename1[]="Log.txt";
static char logfilename2[]="Log1.txt";
static char datestr[16];
static char timestr[16];
static char mss[4];

static FILE *flog;
static pthread_mutex_t cs_log;

static void LogV(const char *logstr);

static const char *GetSimpleFileName(const char *pFileName)
{
    const char *p = strrchr(pFileName, '/');
    if (NULL != p) {
        return p + 1;
    }
    return pFileName;
}

static void XLog(const char *pTag, int level, const char *pFileName, const char *pFuncName, int line, const char *pFmt, va_list vl)
{
    char szLogInfo[BUF_SIZE + 1] = {0};
    sprintf(szLogInfo, "[%s:%d %s] ", GetSimpleFileName(pFileName), line, pFuncName);
    int len = strlen(szLogInfo);
	
    vsnprintf(szLogInfo + len, (BUF_SIZE - len), pFmt, vl);

#ifdef _FOR_ANDROID_
    __android_log_write(level, pTag, szLogInfo);
#else
    printf("%s", szLogInfo);
#endif
}

void XLogDebug(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...)
{
    va_list al;
    va_start(al, pFmt);
#ifdef _FOR_ANDROID_
    XLog(pTag, (int)ANDROID_LOG_DEBUG, pFileName, pFuncName, line, pFmt, al);
#else
    XLog(pTag, 0, pFileName, pFuncName, line, pFmt, al);
#endif
    va_end(al);
}

void XLogError(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt,...)
{
	pthread_mutex_lock(&cs_log);
    va_list al;
    va_start(al, pFmt);
#ifdef _FOR_ANDROID_
    XLog(pTag, (int)ANDROID_LOG_ERROR, pFileName, pFuncName, line, pFmt, al);
#else
    XLog(pTag, 0, pFileName, pFuncName, line, pFmt, al);
#endif
    va_end(al);
	pthread_mutex_unlock(&cs_log);
}

static void LogV(const char *logstr)
{
	struct tm *now;
    struct timeb tb;

    if (NULL==logstr||0==logstr[0]) {
		return;	
    }
	
    ftime(&tb);
    now=localtime(&tb.time);
    sprintf(datestr,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
    sprintf(timestr,"%02d:%02d:%02d",now->tm_hour     ,now->tm_min  ,now->tm_sec );
    sprintf(mss,"%03d",tb.millitm);
	
    printf("%s %s.%s %s", datestr,timestr,mss,logstr);
	
    flog = fopen(logfilename1,"a");
    if (NULL!=flog) {
        fprintf(flog,"%s %s.%s %s",datestr,timestr,mss,logstr);
		
        if (ftell(flog)>MAXLOGSIZE) {
            fclose(flog);
            if (rename(logfilename1,logfilename2)) {
                remove(logfilename2);
                rename(logfilename1,logfilename2);
            }
            flog=fopen(logfilename1,"a");
            if (NULL==flog) return;
        }
		
        fclose(flog);
    }
}


