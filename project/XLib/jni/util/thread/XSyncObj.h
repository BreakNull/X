#ifndef CXX_XSYNC_OBJ_H
#define CXX_XSYNC_OBJ_H

#include <pthread.h>

class XSyncObj
{
public:
	/**
	* Construction.
	*/
	XSyncObj();

	/**
	* Destruction.
	*/
	virtual ~XSyncObj();

	/**
	* Synchronize start.
	*/
	void SyncStart();

	/**
	* Try synchronize start
	*
	* @return bool : true means synchronize succeed, and false failed.
	*/
	bool TrySyncStart();

	/**
	* Synchronize end.
	*/
	void SyncEnd();
  
private:
        XSyncObj(const XSyncObj& src){}
        XSyncObj& operator = (const XSyncObj& src){return *this;}

protected:
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;
};

#endif
