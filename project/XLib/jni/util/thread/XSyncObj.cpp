#include "XSyncObj.h"


XSyncObj::XSyncObj()
{
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);
}

XSyncObj::~XSyncObj()
{
	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
}

void
XSyncObj::SyncStart()
{
	pthread_mutex_lock(&mutex);
}

bool
XSyncObj::TrySyncStart()
{
    int ret = pthread_mutex_trylock(&mutex);
	return (ret==0)?true:false;
}

void
XSyncObj::SyncEnd()
{
	pthread_mutex_unlock(&mutex);
}

