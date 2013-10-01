#ifndef CXX_XTIMER_H
#define CXX_XTIMER_H

class XTimer
{
public:
    explicit XTimer(int msec, bool iter = true);
	virtual ~XTimer();
    void Start();
	void Stop();
    void Restart();
    void Restart(int ms);
    inline bool IsActive() const {return m_id != 0;}
	
protected:
	virtual void OnTimer();
	
private:
    friend class XTimerManager;
    int m_iMsec;
    int	m_id;
    bool m_bIterate;

    XTimer(const XTimer& src);
    XTimer& operator =(const XTimer& src);
};

#endif
