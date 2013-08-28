#include "XTimer.h"
#include "XTimerManager.h"
XTimerManager&
XTimer::GetTimerManager()
{
	static XTimerManager _tm;
	return _tm;
}

XTimer::XTimer(long tm, bool it)
{
	msec			= tm;
	m_bIterate		= it;
	m_dTimerid		= 0;
	used_timer_id	= 0;
	signal			= 0;
	m_pRequest		= new XTimerRequest();
	m_pRequest->timer	= this;
}

XTimer::~XTimer()
{
	Stop();
	if (NULL != m_pRequest)
	{
		delete m_pRequest;
	}
}

bool XTimer::Start()
{
	if (m_dTimerid) return true;
	signal = 0;
	bool ret = GetTimerManager().RegisterTimer(this);
	used_timer_id = m_dTimerid;
	return ret;
}

void XTimer::Stop()
{
	if (!m_dTimerid) return;
	signal = 0;
	GetTimerManager().RemoveTimer(this);
}

bool XTimer::Restart()
{
	return Restart(msec);
}

bool XTimer::Restart(long time)
{
	msec = time;
	if (m_dTimerid)
	{
		signal = 0;
		GetTimerManager().RemoveTimer(this);
		bool ret = GetTimerManager().RegisterTimer(this);
		used_timer_id = m_dTimerid;
		return ret;
	}
	else
	{
		return(Start());
	}
	return false;
}

void XTimer::DoAction()
{
	signal = 0;
	if (!m_bIterate)
	{
		GetTimerManager().SetInvalid(m_dTimerid);
		m_dTimerid = 0;
	}
	
	OnTimer();
}

bool XTimer::IsValid(int id)
{
	return GetTimerManager().IsValid(id);
}

void XTimer::OnTimer()
{
}
