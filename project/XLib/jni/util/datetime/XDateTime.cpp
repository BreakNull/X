#include "XDateTime.h"
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/timeb.h>

XDate::XDate()
	: m_iYear(0)
    , m_iMonth(0)
    , m_iDay(0)
{
}

XDate::XDate(int y, int m, int d)
	: m_iYear(y)
    , m_iMonth(m)
    , m_iDay(d)

{
}

XDate 
XDate::CurrentDate()
{
	XDateTime date_time = XDateTime::CurrentDateTime();
	return date_time.GetDate();
}

XDate 
XDate::FromString(const std::string &day, const std::string &format)
{
	std::string cur_format = format;
	XDate date(-1, -1, -1);
	
	int iDayPos = cur_format.find("dd");
	if(iDayPos == std::string::npos) {
		iDayPos = cur_format.find("d");

		if(iDayPos == std::string::npos) {
			return date;
		}
		else {
			cur_format.replace(iDayPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iDayPos, 2, "%02d");
	}

	
	int iMonthPos = cur_format.find("MM");
	if(iMonthPos == std::string::npos) {
		iMonthPos = cur_format.find("M");

		if(iMonthPos == std::string::npos) {
			return date;
		}
		else {
			cur_format.replace(iMonthPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMonthPos, 2, "%02d");
	}

	int iYearPos = cur_format.find("yyyy");
	if(iYearPos == std::string::npos) {
		return date;
	}
	else {
		cur_format.replace(iYearPos, 4, "%04d");
	}

	// start set the value
	XDate cDate;

	if(iYearPos < iDayPos && iYearPos < iMonthPos) {
		sscanf(day.c_str(), cur_format.c_str(),
			&cDate.m_iYear, &cDate.m_iMonth, &cDate.m_iDay);
	}
	else {
		sscanf(day.c_str(), cur_format.c_str(),
			&cDate.m_iDay, &cDate.m_iMonth, &cDate.m_iYear);
	}
	
	
	return cDate;
}

XDate 
XDate::AddDays(int d)
{
#if 0
	#an example to implement this funciton

	char fmt[] = "%Y-%m-%d-%H:%M:%S";
	char buf[] = "2000-01-01-00:00:00";
	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		fprintf(stdout "ok");
	}
#endif
	XDate date(-1, -1, -1);
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_iYear, m_iMonth, m_iDay, iTmp, iTmp, iTmp);
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return date;
	}

	tb.tm_mday += d;

	date.SetDate(tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);
	return date;
}

int
XDate::GetYear() const
{
	return m_iYear;
}

int 
XDate::GetMonth() const
{
	return m_iMonth;
}

int 
XDate::GetDay() const
{
	return m_iDay;
}

int 
XDate::GetDayOfWeek() const
{
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_iYear, m_iMonth, m_iDay, iTmp, iTmp, iTmp);
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return 0;
	}
		
	return tb.tm_wday;
}

bool
XDate::IsLeapYear(int y)
{
	if ((y % 4) != 0){
		return false;
	}
	if ((y % 100) == 0) {
		return ((y % 400) == 0) ? true : false;
	}
	return true;
}

bool 
XDate::IsValid()
{
	if (m_iMonth == 0 || m_iMonth > 12) {
		return false;
	}
	
    short MAX_DAY_OF_MONTH = 0;
	
	if (IsLeapYear(m_iYear)) {
        static const short DAY_OF_MONTH[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
		MAX_DAY_OF_MONTH = DAY_OF_MONTH[m_iMonth];
	}
	else {
        static const short DAY_OF_MONTH[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
		MAX_DAY_OF_MONTH = DAY_OF_MONTH[m_iMonth];
	}
	
	if (m_iDay == 0 || m_iDay > MAX_DAY_OF_MONTH) {
		return false;
	}
	return true;
}

void 
XDate::SetDate(int y, int m, int d)
{
	m_iYear = y;
	m_iMonth = m;
	m_iDay = d;
}

std::string 
XDate::ToString(const std::string &format) const
{
	std::string cur_format = format;

	int iDayPos = cur_format.find("dd");
	if(iDayPos == std::string::npos) {
		iDayPos = cur_format.find("d");
		if(iDayPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iDayPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iDayPos, 2, "%02d");
	}
	

	int iMonthPos = cur_format.find("MM");
	if(iMonthPos == std::string::npos) {
		iMonthPos = cur_format.find("M");
		if(iMonthPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iMonthPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMonthPos, 2, "%02d");
	}
	
	
	int iYearPos = cur_format.find("yyyy");
	if(iYearPos == std::string::npos) {
		return "";
	}
	else {
		cur_format.replace(iYearPos, 4, "%04d");
	}
	

	int date_val[3] = {0};
	if(iYearPos < iDayPos && iYearPos < iMonthPos) {
		date_val[0] = m_iYear;
		date_val[1] = m_iMonth;
		date_val[2] = m_iDay;
	}
	else {
		date_val[0] = m_iDay;
		date_val[1] = m_iMonth;
		date_val[2] = m_iYear;
	}
	
	char szValue[30] = {0};
	sprintf(szValue, cur_format.c_str(), date_val[0], date_val[1], date_val[2]);

	return (std::string)(szValue);
}

bool 
XDate::operator!=(const XDate &d) const
{
	bool ret = true;

	if (m_iYear == d.m_iYear && m_iMonth == d.m_iMonth && m_iDay == d.m_iDay) {
		ret = false;
	}
		
	return ret;
}
	
bool 
XDate::operator<(const XDate &d) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = d.ToString();
			
	return str_cur < str_comp;
}

bool 
XDate::operator<=(const XDate &d) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = d.ToString();
			
	return str_cur <= str_comp;
}

bool 
XDate::operator==(const XDate &d) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = d.ToString();
			
	return str_cur == str_comp;
}

bool 
XDate::operator>(const XDate &d) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = d.ToString();
			
	return str_cur > str_comp;
}

bool
XDate::operator>=(const XDate &d) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = d.ToString();
			
	return str_cur >= str_comp;
}


XTime::XTime()
	: m_iHour(0)
    , m_iMinute(0)
    , m_iSecond(0)
    , m_iMillSecond(0)
{	
}

XTime::XTime(int h, int m, int s, int ms)
	: m_iHour(h)
    , m_iMinute(m)
    , m_iSecond(s)
    , m_iMillSecond(ms)
{
	
}

 XTime 
 XTime::CurrentTime()
 {
 	XDateTime date_time = XDateTime::CurrentDateTime();
	return date_time.GetTime();
 }

XTime 
XTime::FromString(const std::string &time, const std::string &format)
{
	std::string cur_format = format;
	XTime cTime(-1, -1, -1, -1);

	int iHourPos = cur_format.find("hh");
	if(iHourPos == std::string::npos) {
		iHourPos = cur_format.find("h");

		if(iHourPos == std::string::npos) {
			return cTime;
		}
		else {
			cur_format.replace(iHourPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iHourPos, 2, "%02d");
	}

	int iMinPos = cur_format.find("mm");
	if(iMinPos == std::string::npos) {
		iMinPos = cur_format.find("m");

		if(iMinPos == std::string::npos) {
			return cTime;
		}
		else {
			cur_format.replace(iMinPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMinPos, 2, "%02d");
	}

	int iSecPos = cur_format.find("ss");
	if(iSecPos == std::string::npos) {
		iSecPos = cur_format.find("s");

		if(iSecPos == std::string::npos) {
			return cTime;
		}
		else {
			cur_format.replace(iSecPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iSecPos, 2, "%02d");
	}

	bool bMsec = false;
	int iMsecPos = cur_format.find("sss");
	if(iMsecPos != std::string::npos) {
		bMsec = true;
		cur_format.replace(iMsecPos, 2, "%03d");
	}
	
	
	if (bMsec) {
		sscanf(time.c_str(), cur_format.c_str(), &cTime.m_iHour, &cTime.m_iMinute, &cTime.m_iSecond, &cTime.m_iMillSecond);
	}
	else {
		sscanf(time.c_str(), cur_format.c_str(), &cTime.m_iHour, &cTime.m_iMinute, &cTime.m_iSecond);
	}
		
	
	return cTime;
}

void
XTime::GetTimeSpec(struct timespec *time,  int msec)
{
	struct timeval now;
	gettimeofday(&now,NULL);
	time->tv_sec = now.tv_sec + msec/1000;
	time->tv_nsec = now.tv_usec*1000 + (msec%1000)*1000000;
}


XTime 
XTime::AddSecs(int ms)
{
	XTime time;
	XDateTime date_time = XDateTime::CurrentDateTime();
    XDate date = date_time.GetDate();
	
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		date.GetYear(), date.GetMonth(), date.GetDay(), m_iHour, m_iMinute, m_iSecond);
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return XTime();
	}

	tb.tm_sec += ms;
	time.setHMS(tb.tm_hour, tb.tm_min, tb.tm_sec);
	
	return time;
}

int 
XTime::GetHour() const
{
	return m_iHour;
}

int XTime::GetMinute() const
{
	return m_iMinute;
}

int XTime::GetSecond() const
{
	return m_iSecond;
}

int 
XTime::GetMSec() const
{
	return m_iMillSecond;
}

bool 
XTime::IsValid()
{
	if (m_iHour > 23 || m_iMinute > 59 || m_iSecond > 59 ) {
		return false;
	}
	
	return true;
}

bool 
XTime::setHMS(int h, int m, int s, int ms)
{
	m_iHour = h;
	m_iMinute = m;
	m_iSecond = s;
	m_iMillSecond = ms;
}

std::string	
XTime::ToString(const std::string &format) const
{
	std::string cur_format = format;
	
	int iHourPos = cur_format.find("hh");
	if(iHourPos == std::string::npos) {
		iHourPos = cur_format.find("h");

		if(iHourPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iHourPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iHourPos, 2, "%02d");
	}

	int iMinPos = cur_format.find("mm");
	if(iMinPos == std::string::npos) {
		iMinPos = cur_format.find("m");

		if(iMinPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iMinPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMinPos, 2, "%02d");
	}

	int iSecPos = cur_format.find("ss");
	if(iSecPos == std::string::npos) {
		iSecPos = cur_format.find("s");

		if(iSecPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iSecPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iSecPos, 2, "%02d");
	}

	bool bMsec = false;
	int iMsecPos = cur_format.find("sss");
	if(iMsecPos != std::string::npos) {
		bMsec = true;
		cur_format.replace(iMsecPos, 2, "%03d");
	}

	char buf[30] = {0};
	if (bMsec) {
		sprintf(buf, cur_format.c_str(), m_iHour, m_iMinute, m_iSecond, m_iMillSecond);
	}
	else {
		sprintf(buf, cur_format.c_str(), m_iHour, m_iMinute, m_iSecond);
	}
	
	return (std::string)(buf);
}

bool 
XTime::operator!= ( const XTime &t) const
{
	bool ret = true;

	if (m_iHour == t.m_iHour && m_iMinute == t.m_iMinute 
		&& m_iSecond == t.m_iSecond && m_iMillSecond == t.m_iMillSecond) {
		ret = false;
	}
		
	return ret;
}

bool 
XTime::operator< ( const XTime &t) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = t.ToString();
			
	return str_cur < str_comp;
}

bool 
XTime::operator<= ( const XTime &t) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = t.ToString();
			
	return str_cur <= str_comp;
}

bool 
XTime::operator== ( const XTime &t) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = t.ToString();
			
	return str_cur ==  str_comp;
}

bool 
XTime::operator> ( const XTime &t) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = t.ToString();
			
	return str_cur >  str_comp;
}

bool
XTime::operator>= ( const XTime &t) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = t.ToString();
			
	return str_cur >=  str_comp;
}




XDateTime::XDateTime(const XDate &d, const XTime &t)
	: m_date(d)
	, m_time(t)
{
	
}

XDateTime 
XDateTime::CurrentDateTime()
{
	time_t t;
	t = time(NULL);

	struct tm *time;
	time = localtime(&t);

	XDate cur_date;
	XTime cur_time;
	
	cur_date.SetDate(time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);

	struct timeb tp;
	ftime(&tp);
	cur_time.setHMS(time->tm_hour, time->tm_min, time->tm_sec, tp.millitm); 

	XDateTime date_time(cur_date, cur_time);
	return date_time;
}

XDateTime 
XDateTime::FromString(const std::string &datetime, const std::string &format)
{
	std::string cur_format = format;
	
	XDate date(-1, -1, -1);
	XTime time(-1, -1, -1, -1);
	XDateTime date_time(date, time);

	int iYear, iMonth, iDay;	
	int iHour, iMinute, iSec;
	int iMillSec = 0;
	// Date
	int iDayPos = cur_format.find("dd");
	if(iDayPos == std::string::npos) {
		iDayPos = cur_format.find("d");

		if(iDayPos == std::string::npos) {
			return date_time;
		}
		else {
			cur_format.replace(iDayPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iDayPos, 2, "%02d");
	}


	int iMonthPos = cur_format.find("MM");
	if(iMonthPos == std::string::npos) {
		iMonthPos = cur_format.find("M");

		if(iMonthPos == std::string::npos) {
			return date_time;
		}
		else {
			cur_format.replace(iMonthPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMonthPos, 2, "%02d");
	}
	
	
	int iYearPos = cur_format.find("yyyy");
	if(iYearPos == std::string::npos) {
		return date_time;
	}
	else {
		cur_format.replace(iYearPos, 4, "%04d");
	}

	//int *date_val[3] = {0};
	// Time
	int iHourPos = cur_format.find("hh");
	if(iHourPos == std::string::npos) {
		iHourPos = cur_format.find("h");

		if(iHourPos == std::string::npos) {
			return date_time;
		}
		else {
			cur_format.replace(iHourPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iHourPos, 2, "%02d");
	}

	int iMinPos = cur_format.find("mm");
	if(iMinPos == std::string::npos) {
		iMinPos = cur_format.find("m");

		if(iMinPos == std::string::npos) {
			return date_time;
		}
		else {
			cur_format.replace(iMinPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMinPos, 2, "%02d");
	}

	int iSecPos = cur_format.find("ss");
	if(iSecPos == std::string::npos) {
		iSecPos = cur_format.find("s");

		if(iSecPos == std::string::npos) {
			return date_time;
		}
		else {
			cur_format.replace(iSecPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iSecPos, 2, "%02d");
	}

	bool bMsec = false;
	int iMsecPos = cur_format.find("sss");
	if(iMsecPos != std::string::npos) {
		bMsec = true;
		cur_format.replace(iMsecPos, 2, "%03d");
	}

	
	if(bMsec) {	
		if(iYearPos < iDayPos && iYearPos < iMonthPos) {
			sscanf(datetime.c_str(), cur_format.c_str(), 
				&iYear, &iMonth, &iDay,
				&iHour, &iMinute, &iSec, &iMillSec);
		}
		else {
			sscanf(datetime.c_str(), cur_format.c_str(), 
				&iDay, &iMonth, &iYear,
				&iHour, &iMinute, &iSec, &iMillSec);
		}
		
	}
	else {
		if(iYearPos < iDayPos && iYearPos < iMonthPos) {
			sscanf(datetime.c_str(), cur_format.c_str(), 
				&iYear, &iMonth, &iDay,
				&iHour, &iMinute, &iSec);
		}
		else {
			sscanf(datetime.c_str(), cur_format.c_str(), 
				&iDay, &iMonth, &iYear,
				&iHour, &iMinute, &iSec);
		}
	}
	
	XDate cDate(iYear, iMonth, iDay);	
	XTime cTime(iHour, iMinute, iSec, iMillSec);
	
	return XDateTime(cDate, cTime);
}

XDateTime 
XDateTime::AddDays(int ndays)		
{
    XDate date(-1, -1, -1);
	XTime time(-1, -1, -1, -1);

	XDateTime date_time(date, time);
	
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_date.GetYear(), m_date.GetMonth(), m_date.GetDay(), 
		m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());
	
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return date_time;
	}

	tb.tm_mday += ndays;

	date.SetDate(tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);
		
	struct timeb tp;
	ftime(&tp);
	time.setHMS(tb.tm_hour, tb.tm_min, tb.tm_sec, tp.millitm); 

	return XDateTime(date, time);
}

XDateTime
XDateTime::AddMonths(int nmonths )
{
	XDate date(-1, -1, -1);
	XTime time(-1, -1, -1, -1);

	XDateTime date_time(date, time);
	
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_date.GetYear(), m_date.GetMonth(), m_date.GetDay(), 
		m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());
	
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return date_time;
	}

	tb.tm_mon += nmonths;

	date.SetDate(tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);
		
	struct timeb tp;
	ftime(&tp);
	time.setHMS(tb.tm_hour, tb.tm_min, tb.tm_sec, tp.millitm); 

	return XDateTime(date, time);
}

XDateTime 
XDateTime::AddSecs(int s)
{
	XDate date(-1, -1, -1);
	XTime time(-1, -1, -1, -1);

	XDateTime date_time(date, time);
	
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_date.GetYear(), m_date.GetMonth(), m_date.GetDay(), 
		m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());
	
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return date_time;
	}

	tb.tm_sec += s;

	date.SetDate(tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);
		
	struct timeb tp;
	ftime(&tp);
	time.setHMS(tb.tm_hour, tb.tm_min, tb.tm_sec, tp.millitm); 

	return XDateTime(date, time);
}

XDateTime
XDateTime::AddYears(int nyears)
{
	XDate date(-1, -1, -1);
	XTime time(-1, -1, -1, -1);

	XDateTime date_time(date, time);
	
	int iTmp = 0;
	char buf[40]; 

	sprintf(buf, "%04d-%02d-%02d-%02d:%02d:%02d", 
		m_date.GetYear(), m_date.GetMonth(), m_date.GetDay(), 
		m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());
	
	char fmt[] = "%Y-%m-%d-%H:%M:%S";

	struct tm tb;
	if (strptime(buf, fmt, &tb) == NULL) {
		return date_time;
	}

	tb.tm_year += nyears;

	date.SetDate(tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);
		
	struct timeb tp;
	ftime(&tp);
	time.setHMS(tb.tm_hour, tb.tm_min, tb.tm_sec, tp.millitm); 

	return XDateTime(date, time);
}


XDate 
XDateTime::GetDate() const
{
	return m_date;
}

XTime 
XDateTime::GetTime() const
{
	return m_time;
}

bool 
XDateTime::IsValid()
{
	bool date_ret = m_date.IsValid();
	bool time_ret = m_time.IsValid();

	return (date_ret && time_ret);
}

void 
XDateTime::SetDate(const XDate &date)
{
	m_date = date;
}

void 
XDateTime::SetTime(const XTime &time)
{
	m_time = time;
}

std::string 
XDateTime::ToString(const std::string &format) const
{
	std::string cur_format = format;
	
	int iYear = m_date.GetYear();
	int iMonth = m_date.GetMonth();
	int iDay = m_date.GetDay();

	int iHour = m_time.GetHour();
	int iMinute = m_time.GetMinute();
	int iSecond = m_time.GetSecond();
	int iMSec = m_time.GetMSec();
	
	// Date
	int iDayPos = cur_format.find("dd");
	if(iDayPos == std::string::npos) {
		iDayPos = cur_format.find("d");
		if(iDayPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iDayPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iDayPos, 2, "%02d");
	}

	int iMonthPos = cur_format.find("MM");
	if(iMonthPos == std::string::npos) {
		iMonthPos = cur_format.find("M");
		if(iMonthPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iMonthPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMonthPos, 2, "%02d");
	}

	
	int iYearPos = cur_format.find("yyyy");
	if(iYearPos == std::string::npos) {
		return "";
	}
	else {
		cur_format.replace(iYearPos, 4, "%04d");
	}
	
	int date_val[3] = {0};
	if(iYearPos < iDayPos && iYearPos < iMonthPos) {
		date_val[0] = iYear;
		date_val[1] = iMonth;
		date_val[2] = iDay;
	}
	else {
		date_val[0] = iDay;
		date_val[1] = iMonth;
		date_val[2] = iYear;
	}

	// Time
	int iHourPos = cur_format.find("hh");
	if(iHourPos == std::string::npos) {
		iHourPos = cur_format.find("h");

		if(iHourPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iHourPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iHourPos, 2, "%02d");
	}

	int iMinPos = cur_format.find("mm");
	if(iMinPos == std::string::npos) {
		iMinPos = cur_format.find("m");

		if(iMinPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iMinPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iMinPos, 2, "%02d");
	}

	int iSecPos = cur_format.find("ss");
	if(iSecPos == std::string::npos) {
		iSecPos = cur_format.find("s");

		if(iSecPos == std::string::npos) {
			return "";
		}
		else {
			cur_format.replace(iSecPos, 1, "%d");
		}
	}
	else {
		cur_format.replace(iSecPos, 2, "%02d");
	}

	bool bMsec = false;
	int iMsecPos = cur_format.find("sss");
	if(iMsecPos != std::string::npos) {
		bMsec = true;
		cur_format.replace(iMsecPos, 2, "%03d");
	}

	char buf[50] = {0};
	if (bMsec) {
		sprintf(buf, cur_format.c_str(), date_val[0], date_val[1], date_val[2],
			iHour, iMinute, iSecond, iMSec);
	}
	else {
		sprintf(buf, cur_format.c_str(), date_val[0], date_val[1], date_val[2],
			iHour, iMinute, iSecond);
	}

	return std::string(buf);
}

bool 
XDateTime::operator!= ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
			
	return str_cur !=  str_comp;
}

bool 
XDateTime::operator<  ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
				
	return str_cur <   str_comp;
}

bool 
XDateTime::operator<= ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
					
	return str_cur <=  str_comp;
}

bool 
XDateTime::operator== ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
					
	return str_cur ==  str_comp;
}

bool
XDateTime::operator > ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
						
	return str_cur  >  str_comp;
}
	
bool 
XDateTime::operator>= ( const XDateTime &other) const
{
	std::string str_cur = this->ToString();
	std::string str_comp = other.ToString();
						
	return str_cur >=  str_comp;
}



