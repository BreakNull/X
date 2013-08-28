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
#define OUTPUT_BUFF_SIZE 256
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

void
LogDebug(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt, ...)
{
    char szLogInfo[OUTPUT_BUFF_SIZE + 1] = {0};
    sprintf(szLogInfo, "[%s:%d %s] ", GetSimpleFileName(pFileName), line, pFuncName);
    int len = strlen(szLogInfo);
	
	va_list list;
    va_start(list, pFmt);
    vsnprintf(szLogInfo + len, (OUTPUT_BUFF_SIZE - TERMINATE_CODE_SIZE - len), pFmt, list);
	va_end(list);

	#ifdef _FOR_ANDROID_
        __android_log_print(ANDROID_LOG_DEBUG, pTag, "%s", szLogInfo);
	#else
		printf("%s", szLogInfo);
	#endif
}

void 
LogError(const char *pTag, const char *pFileName, const char *pFuncName, int line, const char *pFmt,...)
{
	va_list argp;

	pthread_mutex_lock(&cs_log);
	
    va_start(argp, pFmt);
    char szLogInfo[OUTPUT_BUFF_SIZE + 1] = {0};
    sprintf(szLogInfo, "[%s:%d %s] ", GetSimpleFileName(pFileName), line, pFuncName);
    int len = strlen(szLogInfo);
    snprintf(szLogInfo + len, (OUTPUT_BUFF_SIZE - TERMINATE_CODE_SIZE - len), pFmt, argp);
    va_end(argp);
    //LogV(szLogInfo);

	
#ifdef _FOR_ANDROID_
        __android_log_print(ANDROID_LOG_ERROR, pTag, "%s", szLogInfo);
#else
		printf("%s", szLogInfo);
#endif

	pthread_mutex_unlock(&cs_log);
}

static void
LogV(const char *logstr)
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


