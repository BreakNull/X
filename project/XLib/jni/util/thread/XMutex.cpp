#include "XMutex.h"


XMutex::XMutex()
{
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);
}

XMutex::~XMutex()
{
	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
}

void
XMutex::Lock()
{
	pthread_mutex_lock(&mutex);
}

bool
XMutex::TryLock()
{
    int ret = pthread_mutex_trylock(&mutex);
	return (ret==0)?true:false;
}

void
XMutex::Unlock()
{
	pthread_mutex_unlock(&mutex);
}

