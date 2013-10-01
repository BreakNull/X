#ifndef CXX_XSYNC_OBJ_H
#define CXX_XSYNC_OBJ_H

#include <pthread.h>

class XMutex
{
public:
	/**
	* Construction.
	*/
    XMutex();

	/**
	* Destruction.
	*/
    virtual ~XMutex();

    void Lock();

	/**
    * Try synchronize
	*
	* @return bool : true means synchronize succeed, and false failed.
	*/
    bool TryLock();

    void Unlock();
  
private:
        XMutex(const XMutex& src);
        XMutex& operator = (const XMutex& src);

protected:
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;
};

#endif
