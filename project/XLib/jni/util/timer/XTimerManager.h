#ifndef CXX_XTIMER_MANAGER_H
#define CXX_XTIMER_MANAGER_H

#include "XMutex.h"
#include "XThread.h"
#include <list>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
using namespace std;

class XTimer;

class XTimerManager : public XThread
{
public:
	XTimerManager();
	virtual ~XTimerManager();
    void RegisterTimer(XTimer* timer);
    void RemoveTimer(XTimer* timer);

protected:
    virtual void Run();

private:
    list<XTimer*> m_cReqList;
    int	m_iNextId;
    XMutex m_cMutex;

    int NextID() {return ++m_iNextId;}
    XTimerManager(const XTimerManager& src);
    XTimerManager& operator =(const XTimerManager& src);
};

#ifdef __cplusplus
extern "C" {
#endif

void gettimespec(struct timespec *time,  int msec);
void settimespec(struct timespec *time,  int msec);
int  subtimespec(struct timespec *time1, struct timespec *time2);

#ifdef __cplusplus
}
#endif

#endif
