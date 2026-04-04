#pragma once
#include <string>
using namespace std;
struct stPersonInfo
{
	string FirstName;
	string LastName;
	string Email;
	string Phone;

};
class clsPerson
{
private:
	stPersonInfo _Person;
public:
	clsPerson(stPersonInfo DatePerson)
	{
		_Person = DatePerson;
	}
	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_Person.FirstName = FirstName;
		_Person.LastName = LastName;
		_Person.Email = Email;
		_Person.Phone = Phone;
	}

	void setFirstName(string FirstName)
	{
		_Person.FirstName = FirstName;
	}
	string getFirstName()
	{
		return _Person.FirstName;
	}

	void setLastName(string LastName)
	{
		_Person.LastName = LastName;
	}
	string getLastName()
	{
		return _Person.LastName;
	}

	void setEmail(string Email)
	{
		_Person.Email = Email;
	}
	string getEmail()
	{
		return _Person.Email;
	}

	void setPhone(string Phone)
	{
		_Person.Phone = Phone;
	}
	string getPhone()
	{
		return _Person.Phone;
	}

	string FullName()
	{
		return _Person.FirstName + " " + _Person.LastName;
	}
};

