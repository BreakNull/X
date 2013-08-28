#include "XAutoSync.h"
#include "XSyncObj.h"

XAutoSync::XAutoSync(XSyncObj& cSync)
: m_cSync(cSync)
{
	m_cSync.SyncStart();
	return;
}

XAutoSync::~XAutoSync()
{
	m_cSync.SyncEnd();
	return;
}

