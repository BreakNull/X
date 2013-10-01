#include "XTimer.h"
#include "XTimerManager.h"

XTimerManager& GetTimerManager()
{
	static XTimerManager _tm;
    static bool b = false;
    if (!b) {
        _tm.StartThread();
    }
	return _tm;
}

XTimer::XTimer(XRunnable r, void *params, int msec, bool it)
{
    m_iMsec	= msec;
    m_bIterate = it;
    m_id = 0;
    m_runnable = r;
    m_params = params;
}

XTimer::~XTimer()
{
    Stop();
}

void XTimer::Start()
{
    if (m_id) {
        return;
    }
    GetTimerManager().RegisterTimer(this);
}

void XTimer::Stop()
{
    if (!m_id) {
        return;
    }
	GetTimerManager().RemoveTimer(this);
    m_id = 0;
}

void XTimer::Restart()
{
    Restart(m_iMsec);
}

void XTimer::Restart(int ms)
{
    m_iMsec = ms;
    Stop();
    Start();
}

void XTimer::DoAction()
{
    if (m_runnable) {
        m_runnable(m_params);
    } else {
        OnTimer();
    }
}

void XTimer::OnTimer()
{
}
