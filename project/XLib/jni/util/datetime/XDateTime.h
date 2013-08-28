#ifndef XDATETIME_H
#define XDATETIME_H

#include <string>

/**
 * 日期
 */
class XDate
{
public:
    XDate();
    XDate(int y, int m, int d);

    //当前日期
    static XDate CurrentDate();
    /*
     * 将字符串格式的日期，格式化成Date
     * @param day "2013-04-24"
     * @param format "yyyy-MM-dd"  "yyyy-M-d"
     *  yyyy:4位数字的年份
     *  M:1或2位的月份,   MM:2位的月份
     *  d:1或2位的日期,   dd:2位的日期
     */
    static XDate FromString(const std::string &day, const std::string &format);

    XDate AddDays(int d);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    //星期
    int GetDayOfWeek() const;
    //此月中有几天
    int	GetDaysInMonth () const;
    int DaysTo(const XDate &d) const;
    bool IsValid();
    void SetDate(int y, int m, int d);
    std::string ToString(const std::string &format = "yyyy-MM-dd") const;

    bool operator!=(const XDate &d) const;
    bool operator<(const XDate &d) const;
    bool operator<=(const XDate &d) const;
    bool operator==(const XDate &d) const;
    bool operator>(const XDate &d) const;
    bool operator>=(const XDate &d) const;
private:
	bool IsLeapYear(int y);
protected:
    int m_iYear;
    int m_iMonth;
    int m_iDay;
};

//------------------------------------------------------------------------------
/**
 * 时间
 */
class XTime
{
public:
    XTime();
    XTime(int h, int m, int s = 0, int ms = 0);

    static XTime CurrentTime();
    /*
     * 将字符串格式的时间，格式化成Time
     * @param day "15:38:13"
     * @param format "hh:mm:ss.sss"
     *  h:1或2位的小时,  hh:2位的小时
     *  m:1或2位的分钟,  mm:2位的分钟
     *  s:1或2位的秒,    ss:2位的秒
     *  sss:毫秒
     */
    static XTime FromString(const std::string &time, const std::string &format);

	static void GetTimeSpec(struct timespec *time,  int msec);
	
    XTime AddMillSecs(int ms);
    XTime AddSecs(int ms);
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    //毫秒
    int GetMSec() const;
    bool IsValid();
    //this - d 相隔多少秒
    int	SecsTo (const XTime &t) const;
    bool setHMS(int h, int m, int s, int ms = 0);
    std::string	ToString(const std::string &format = "hh:mm:ss") const;

    bool operator!= ( const XTime &t) const;
    bool operator< ( const XTime &t) const;
    bool operator<= ( const XTime &t) const;
    bool operator== ( const XTime &t) const;
    bool operator> ( const XTime &t) const;
    bool operator>= ( const XTime &t) const;

protected:
    int m_iHour;
    int m_iMinute;
    int m_iSecond;
    int m_iMillSecond;
};

//------------------------------------------------------------------------------

class XDateTime
{
public:
    XDateTime(const XDate &d, const XTime &t);

    static XDateTime CurrentDateTime();
    static XDateTime FromString(const std::string &datetime, const std::string &format);

    XDateTime AddDays(int ndays);
    XDateTime AddMSecs(long long msecs);
    XDateTime AddMonths(int nmonths );
    XDateTime AddSecs(int s);
    XDateTime AddYears(int nyears);

    XDate GetDate() const;
	XTime GetTime() const;
    int	DaysTo(const XDateTime &other) const;
    bool IsValid();
    long long MsecsTo(const XDateTime &other) const;
    int	SecsTo(const XDateTime &other) const;
    void SetDate(const XDate &date);
    void SetTime(const XTime &time);
    std::string ToString(const std::string &format = "yyyy-MM-dd-hh:mm:ss:sss") const;

    bool operator!= ( const XDateTime &other) const;
    bool operator< ( const XDateTime &other) const;
    bool operator<= ( const XDateTime &other) const;
    bool operator== ( const XDateTime &other) const;
    bool operator> ( const XDateTime &other) const;
    bool operator>= ( const XDateTime &other) const;

protected:
    XDate m_date;
    XTime m_time;
};

#endif // DATETIME_H
