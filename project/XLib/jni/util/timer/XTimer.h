#ifndef CXX_XTIMER_H
#define CXX_XTIMER_H

#include "XThread.h"
#include "XRunnable.h"

class XTimer
{
public:
    explicit XTimer(XRunnable r, void *params, int msec, bool iter = true);
	virtual ~XTimer();
    void Start();
	void Stop();
    void Restart();
    void Restart(int ms);
    inline bool IsActive() const {return m_id != 0;}

private:
    virtual void OnTimer();
		
private:
    friend class XTimerManager;
    int m_iMsec;
    int	m_id;
    bool m_bIterate;
    XRunnable m_runnable;
    void *m_params;

    void DoAction();
    XTimer(const XTimer& src);
    XTimer& operator =(const XTimer& src);
};

#endif
