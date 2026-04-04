#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;
/*
	The clsInputValidate class provides static methods for validating user input, including methods for checking if a number is within a specified range, if a date is valid, and for reading different types of input from the user with error handling to ensure valid input is received.	
*/
class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		return Number >= From && Number <= To;
	}
	static bool IsNumberBetween(int Number, int From, int To)
	{
		return Number >= From && Number <= To;
	}
	static bool IsNumberBetween(float Number, float From, float To)
	{
		return Number >= From && Number <= To;
	}
	static bool IsNumberBetween(double Number, double From, double To)
	{
		return Number >= From && Number <= To;
	}
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&& (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
			return true;
		else return false;
	}
	static string ReadString(string MSM)
	{
		string str;
		cout << MSM;
		getline(cin >> ws, str);
		return str;
	}
	static float ReadFloatNumber(string MSM)
	{
		double Number;
		cout << MSM;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore();
			cout << "Invalid Number, Enter again:";
		}
		return Number;
	}
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Num;
		while (!(cin >> Num))
		{
			cin.clear();
			cin.ignore();
			cout << ErrorMessage;
		}
		return Num;
	}
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore();
			cout << ErrorMessage;
		}
		return Number;
	}
	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}
	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}
};

