#ifndef CXX_XTIMER_H
#define CXX_XTIMER_H

#include <pthread.h>

class XTimerRequest;
class XTimerManager;

class XTimer
{
friend class XTimerManager;

public:
	explicit XTimer(long msec, bool iter = true);
	virtual ~XTimer();
	bool Start();
	void Stop();
	bool Restart();
	bool Restart(long tm);
	inline bool IsActive() const {return m_dTimerid != 0;}
	inline int GetId() const {return used_timer_id;}
	void DoAction();
	static bool IsValid(int id);
	
protected:
	long		msec;
	int		m_dTimerid;
	bool		m_bIterate;
	int		used_timer_id;
	int        signal;
	XTimerRequest* m_pRequest;
	virtual void OnTimer();
	
private:
	XTimer(const XTimer& src){}
	XTimer& operator =(const XTimer& src){return *this;}
	static XTimerManager& GetTimerManager();
};

#endif
