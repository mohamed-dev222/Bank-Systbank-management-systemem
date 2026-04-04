#pragma warning(disable : 4996)
#pragma once
#include <vector>
#include "clsString.h"
// The stDate structure is used to store the day, month, and year components of a date.
struct stDate
{
	int Day;
	int Month;
	int Year;
};
/*
	The clsDate class provides various functionalities for handling dates, including constructors for different date formats, methods for validating dates, comparing dates, and formatting dates as strings. It also includes static methods for determining leap years, the number of days in a month, and the day of the week for a given date.
*/
class clsDate
{
private:
	
	stDate _Date;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Date.Day = now->tm_mday;
		_Date.Month = now->tm_mon +1;
		_Date.Year = now->tm_year + 1900;
	}
	clsDate(string Date)
	{
		// 2/2/2000
		vector<string> vDate = clsString::Split(Date,"/");
		_Date.Day = stoi(vDate.at(0));
		_Date.Month = stoi(vDate.at(1));
		_Date.Year = stoi(vDate.at(2));
	}
	clsDate(short Day, short Month, short Year)
	{
		_Date.Day = Day;
		_Date.Month = Month;
		_Date.Year = Year;
	}
	clsDate(int DayOrderInYear, int Year)
	{
		*this = GetDateFromDayOrderInYear(DayOrderInYear, Year);
	}
	void SetDate(stDate Date)
	{
		_Date.Day   = Date.Day;
		_Date.Month = Date.Month;
		_Date.Year  = Date.Year;
	}
	stDate GetDate()
	{
		return _Date;
	}

	void PrintDate()
	{
		cout << "Date: " << _Date.Day << "/" << _Date.Month << "/" << _Date.Year << endl;
	}
	static string DateToString(clsDate Date)
	{
		vector<string> vDate;
		stDate sDate = Date.GetDate();
		vDate.push_back(to_string(sDate.Day));
		vDate.push_back(to_string(sDate.Month));
		vDate.push_back(to_string(sDate.Year));
		string strDate = clsString::JoinString(vDate, "/");
		return strDate;

	}
	string DateToString()
	{
		return to_string(_Date.Day) + "/" + to_string(_Date.Month) + "/" + to_string(_Date.Year);
	}

	static bool isLeapYear(short Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_Date.Year);
	}
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		if (Date1._Date.Year < Date2._Date.Year) return true;
		else if (Date1._Date.Month < Date2._Date.Month) return true;
		else if (Date1._Date.Day < Date2._Date.Day) return true;
		else return false;

	}
	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}
	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Date.Day == Date2._Date.Day &&
			Date1._Date.Month == Date2._Date.Month &&
			Date1._Date.Year == Date2._Date.Year);
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}
	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date._Date.Day == NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}
	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return IsDate1BeforeDate2(Date1, Date2) ? false : IsDate1EqualDate2(Date1, Date2) ? false : true;
	}
	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}
	static bool IsValidDate(clsDate Date)
	{
		if (Date._Date.Day > NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year) || Date._Date.Day < 0) return false;
		else if (Date._Date.Month > 12 || Date._Date.Month < 1) return false;
		return true;
	}
	bool IsValid()
	{
		return IsValidDate(*this);
	}
	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date._Date) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}
	static bool IsWeekEnd(clsDate Date)
	{
		return DayOfWeekOrder(Date._Date) == 5 || IsEndOfWeek(Date);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}
	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month > 12 || Month < 1) return 0;
		short MonthDay[12] = { (short)31, (isLeapYear(Year) ? (short)29 : (short)28), (short)31, (short)30, (short)31, (short)30, (short)31, (short)31, (short)30, (short)31, (short)30, (short)31 };
		return MonthDay[Month - 1];
	}
	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Date.Month, _Date.Year);
	}
	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}
	short NumberOfHoursInAMonth()
	{
		return NumberOfHoursInAMonth(_Date.Month, _Date.Year);
	}
	static short NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}
	short NumberOfMinutesInAMonth()
	{
		return NumberOfMinutesInAMonth(_Date.Month, _Date.Year);
	}
	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return  NumberOfMinutesInAMonth(Month, Year) * 60;
	}
	int NumberOfSecondsInAMonth()
	{
		return  NumberOfSecondsInAMonth(_Date.Month, _Date.Year);
	}
	static short NumberOfDaysInAYear(short Year)
	{
		return (isLeapYear(Year) ? 366 : 365);
	}
	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Date.Year);
	}
	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Date.Year);
	}
	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Date.Year);
	}
	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year)*60;
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Date.Year);
	}

	static short DayOfWeekOrder(stDate Date)
	{
		short a = (14 - Date.Month) / 12;
		short y = Date.Year - a;
		short m = Date.Month + (12 * a) - 2;
		return (Date.Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Date);
	}
	static string DayShortName(short DayWeekOrder)
	{
		string DayOfWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		if (DayWeekOrder < 0 || DayWeekOrder > 6)  
			return "Invalid Day";

		return DayOfWeek[DayWeekOrder];  
	}
	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}
	static string MonthShortName(short MonthNumber)
	{
		if (MonthNumber < 1 || MonthNumber > 12)
			return "Invalid Month!";

		string Months[12] =
		{ "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return Months[MonthNumber - 1];
	}
	string MonthShortName()
	{
		return MonthShortName(_Date.Month);
	}	

	static void PrintMonthCalendar(stDate Date)
	{
		printf("  _______________%s_______________\n\n", MonthShortName(Date.Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		 
		for (i = 0; i < DayOfWeekOrder(Date); i++) printf("     ");

		for (int j = 1; j <= NumberOfDaysInAMonth(Date.Month, Date.Year); j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");


	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Date);
	}
	static void PrintYearCalendar(stDate Date)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Date.Year);
		printf("  _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			Date.Month = i;
			PrintMonthCalendar(Date);
		}
	
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Date);
	}

	static int DaysFromBeginningOfYear(stDate Date)
	{
		int Sum = 0;
		for (int i = 1; i < Date.Month; i++) Sum += NumberOfDaysInAMonth(i, Date.Year);
		Sum += Date.Day;
		return Sum;
	}
	int DaysFromBeginningOfYear()
	{
		return DaysFromBeginningOfYear(_Date);
	}
	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Date);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}
	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year) - Date._Date.Day;
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}
	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		return NumberOfDaysInAYear(Date._Date.Year) - DaysFromBeginningOfYear(Date._Date);
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;
	}
	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}
	static int CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, GetSystemDate(), true);
	}
	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate var = Date1;
		Date1 = Date2;
		Date2 = var;
	}
	void AddDays(int Days)
	{
		int TotalDays = DaysFromBeginningOfYear(_Date) + Days;
		int Year = _Date.Year;

		while (TotalDays > NumberOfDaysInAYear(Year))
		{
			TotalDays -= NumberOfDaysInAYear(Year);
			Year++;
		}

		*this = GetDateFromDayOrderInYear(TotalDays, Year);
	}
	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Date.Month))
			{
				Date._Date.Day = 1;
				Date._Date.Month = 1;
				Date._Date.Year++;
			}
			else
			{
				Date._Date.Day = 1;
				Date._Date.Month++;
			}
		}
		else
		{
			Date._Date.Day++;
		}
		return Date;
	}
	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1AfterDate2(Date1, Date2)) return enDateCompare::After;
		else if (IsDate1BeforeDate2(Date1, Date2)) return enDateCompare::Before;
		else return enDateCompare::Equal;
	}
	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static clsDate GetDateFromDayOrderInYear(int DayOrderInYear, int Year)
	{
		clsDate Date;
		int RemainingDay = DayOrderInYear;
		int MonthDay = 0;
		Date._Date.Year = Year;
		Date._Date.Month = 1;
		while (true)
		{
			MonthDay = NumberOfDaysInAMonth(Date._Date.Month, Year);
			if (RemainingDay > MonthDay)
			{
				Date._Date.Month++;
				RemainingDay -= MonthDay;
			}
			else
			{
				Date._Date.Day = RemainingDay;
				break;
			}
		}
		return Date;
	}
	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		clsDate DateCounter = Date1;

		if (IsDate1AfterDate2(Date1, Date2))
		{
			while (IsDate1AfterDate2(DateCounter, Date2))
			{
				DateCounter = DecreaseDateByOneDay(DateCounter);
				Days--;
			}
		}
		else
		{
			while (IsDate1BeforeDate2(DateCounter, Date2))
			{
				DateCounter = AddOneDay(DateCounter);
				Days++;
			}
		}

		return IncludeEndDay ? Days + 1 : Days;
	}
	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}
	static clsDate GetSystemDate()
	{
		return clsDate();
	}
	
	
	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (size_t i = 0; i < 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}
	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (size_t i = 0; i < Weeks; i++) IncreaseDateByOneWeek(Date);
		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}
	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date._Date.Month))
		{
			Date._Date.Month = 1;
			Date._Date.Year++;
		}
		else Date._Date.Month++;
		short DaysInMonth = NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year);
		if (Date._Date.Day > DaysInMonth)
		{
			Date._Date.Day = DaysInMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}
	static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (int i = 1; i <= Months; i++) IncreaseDateByOneMonth(Date);
		return Date;
	}
	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}
	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		if (isLeapYear(Date._Date.Year) && Date._Date.Month == 2 && Date._Date.Day == 29)
		{
			Date._Date.Year++;
			Date._Date.Month++;
			Date._Date.Day = 1;
		}
		else
		{
			Date._Date.Year++;
		}
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}
	static clsDate IncreaseDateByXYear(short NumOfYears, clsDate& Date)
	{
		for (int i = 0; i < NumOfYears; i++)
		{
			IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	void IncreaseDateByXYear(short NumOfYears)
	{
		*this = IncreaseDateByXYear(NumOfYears, *this);
	}
	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		return IncreaseDateByXYear(10,Date);
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}
	static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (int i = 0; i < Decades; i++) IncreaseDateByOneDecade(Date);
		return Date;
	}
	void IncreaseDateByXDecades(short Decades)
	{
		*this = IncreaseDateByXDecades(Decades, *this);
	}
	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		return IncreaseDateByXDecades(10, Date);
	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}
	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		return IncreaseDateByXDecades(100, Date);
	}
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date._Date.Day == 1)
		{
			if (Date._Date.Month == 1)
			{
				Date._Date.Day = 31;
				Date._Date.Month = 12;
				Date._Date.Year--;
			}
			else
			{
				Date._Date.Month--;
				Date._Date.Day = NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year);
			}
		}
		else Date._Date.Day--;
		return Date;

	}
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}
	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}
	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}
	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{

		if (Date._Date.Month == 1)
		{
			Date._Date.Month = 12;
			Date._Date.Year--;
		}
		else
			Date._Date.Month--;


		//last check day in date should not exceed max days in the current month
	   // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
	   // be 28/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Date.Month, Date._Date.Year);
		if (Date._Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date._Date.Day = NumberOfDaysInCurrentMonth;
		}


		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}
	static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}
	static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}
	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{

		Date._Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}
	static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{

		Date._Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}
	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		//Period of 10 years
		Date._Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}
	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{

		Date._Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}
	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		//Period of 100 years
		Date._Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}
	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		//Period of 1000 years
		Date._Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}
};
