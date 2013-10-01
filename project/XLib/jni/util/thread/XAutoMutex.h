#ifndef CXX_XAUTO_SYNC_H
#define CXX_XAUTO_SYNC_H

#include "XMutex.h"

class XAutoMutex
{
    XMutex &m_cSync;

public:
	/**
	* Construction.
	*	*/
    XAutoMutex(XMutex &cSync);

	/**
	* Destruction.
	*/
    ~XAutoMutex();

private:
    XAutoMutex(const XAutoMutex& cSync);

    XAutoMutex& operator=(const XAutoMutex& cSync);
};


#endif // CXX_AIL_AUTOSYNC_H
