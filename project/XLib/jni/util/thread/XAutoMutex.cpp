#include "XAutoMutex.h"

XAutoMutex::XAutoMutex(XMutex& cSync)
: m_cSync(cSync)
{
    m_cSync.Lock();
}

XAutoMutex::~XAutoMutex()
{
    m_cSync.Unlock();
}

