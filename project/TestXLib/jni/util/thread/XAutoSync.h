#ifndef CXX_XAUTO_SYNC_H
#define CXX_XAUTO_SYNC_H

class XSyncObj;
class XAutoSync
{
	XSyncObj& m_cSync;

public:
	/**
	* Construction.
	*	*/
	XAutoSync(XSyncObj& cSync);

	/**
	* Destruction.
	*/
	~XAutoSync();

private:
	XAutoSync(const XAutoSync& cSync);

	XAutoSync& operator=(const XAutoSync& cSync);
};


#endif // CXX_AIL_AUTOSYNC_H
