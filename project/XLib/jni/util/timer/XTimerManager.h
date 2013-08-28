#ifndef CXX_XTIMER_MANAGER_H
#define CXX_XTIMER_MANAGER_H

#include "XSyncObj.h"
#include "XThread.h"
#include <list>
#include <string.h>

#include <sys/time.h>
#include <sys/stat.h>
using namespace std;

#define NTIMER_MAX_NUM		(256)

#ifndef BYTE
#   define BYTE unsigned char
#endif

class XTimer;
class XTimerRequest
{
public:
	struct timespec timeout_tick;
	void		*pthread;
	XTimer*	timer;
	XTimerRequest(){ memset(&timeout_tick, 0,sizeof(timeout_tick)) ; pthread = NULL; timer = NULL;}
	~XTimerRequest(){}
	bool operator == (const XTimerRequest& req) const;
	bool operator <  (const XTimerRequest& req) const;
	bool operator <= (const XTimerRequest& req) const;
	bool operator >  (const XTimerRequest& req) const;
	bool operator >= (const XTimerRequest& req) const;
	
private:
	XTimerRequest(const XTimerRequest& src){}
	XTimerRequest& operator =(const XTimerRequest& src){return *this;}
};

class XTimerManager : public XSyncObj, public XThread
{
public:
	XTimerManager();
	virtual ~XTimerManager();
	bool RegisterTimer(XTimer* timer);
	void RemoveTimer(XTimer* timer);
	bool IsValid(int id);
	void SetInvalid(int id);
	virtual bool RequestSanity();
	void Notify();
	
protected:
	void AddRequest(XTimerRequest* new_req);
	void RemoveRequest(int id);
	int NextID();
	virtual int Run();
	inline bool CheckQuit() {return (m_bQuitflg);}
	BYTE		timer_table[NTIMER_MAX_NUM];
	list <XTimerRequest*> m_cReqList;
	pthread_t m_tid;
	pthread_attr_t	m_attr;
	pthread_mutex_t	m_mutex;
	pthread_cond_t	m_cond;
	int			m_dNextid;
	bool			need_sanity_reply;
	bool			m_bQuitflg;
	bool			m_bSignalflg;

	XThread* 		m_pTimerManagerThread;
private:
	XTimerManager(const XTimerManager& src){}
	XTimerManager& operator =(const XTimerManager& src){return *this;}
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
