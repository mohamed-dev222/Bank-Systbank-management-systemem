#pragma once
#include <iostream>
#include "../Core/clsPerson.h"
#include "../Core/clsString.h"
#include <fstream>
enum enMode { EmptyMode = 0, UpdateMode= 1, AddNewMode = 2};
struct stAccountDate
{
	enMode Mode;
	string AccountNumber;
	string PinCode;
	float AccountBalance;
};
class clsBankClient : public clsPerson
{
private:
	stAccountDate _Account;
	bool _MarkedForDelete = false;
	
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientDate;
		vClientDate = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3], vClientDate[4], vClientDate[5], stod(vClientDate[6]));
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsBankClient> _LoadClientDateFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}
	static string  _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.getFirstName() + Seperator;
		stClientRecord += Client.getLastName() + Seperator;
		stClientRecord += Client.getEmail() + Seperator;
		stClientRecord += Client.getPhone() + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.getPinCode() + Seperator;
		stClientRecord += to_string(Client.getAccountBalance());
		return stClientRecord;
	}
    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientDateFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);

	}
	void _AddNew()
	{

		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
public:
	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	clsBankClient(stPersonInfo Person, stAccountDate Account) : clsPerson(Person)
	{
		_Account = Account;
	}
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)

	{
		_Account.Mode = Mode;
		_Account.AccountNumber = AccountNumber;
		_Account.PinCode = PinCode;
		_Account.AccountBalance = AccountBalance;

	}

	bool isEmpty()
	{
		return (_Account.Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _Account.AccountNumber;
	}

	void setPinCode(string PinCode)
	{
		_Account.PinCode = PinCode;
	}
	string getPinCode()
	{
		return _Account.PinCode;
	}

	void setAccountBalance(float AccountBalance)
	{
		_Account.AccountBalance = AccountBalance;
	}
	float getAccountBalance()
	{
		return _Account.AccountBalance;
	}

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name  : " << getFirstName();
		cout << "\nLast Name   : " << getLastName();
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << getEmail();
		cout << "\nPhone       : " << getPhone();
		cout << "\nAcc. Number : " << _Account.AccountNumber;
		cout << "\nPassword    : " << _Account.PinCode;
		cout << "\nBalance     : " << _Account.AccountBalance;
		cout << "\n___________________\n";
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFill;
		MyFill.open("Clients.txt", ios::in);
		if (MyFill.is_open())
		{
			string Line;
			while (getline(MyFill, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFill.close();
					return Client;
				}
			}
			MyFill.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFill;
		MyFill.open("Clients.txt", ios::in);
		if (MyFill.is_open())
		{
			string Line;
			while (getline(MyFill, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.getPinCode()==PinCode)
				{
					MyFill.close();
					return Client;
				}
			}
			MyFill.close();
		}
		return _GetEmptyClientObject();
	}

	static bool isClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.isEmpty());
	}

	enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2, svError = 3};
	enSaveResults Save()
	{

		switch (_Account.Mode)
		{
		case enMode::EmptyMode:
		{
			if (isEmpty())
			{

				return enSaveResults::svFaildEmptyObject;

			}

		}

		case enMode::UpdateMode:
		{


			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::isClientExist(AccountNumber()))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//We need to set the mode to update after add new
				_Account.Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}
		return enSaveResults::svError;
	}
	

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientDateFromFile();
		bool Found = false;

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _Account.AccountNumber)
			{
				C._MarkedForDelete = true;
				Found = true;
				break;
			}
		}

		if (!Found)
			return false;

		_SaveCleintsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientDateFromFile();
	}
	void Deposit(double Amount)
	{
		_Account.AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _Account.AccountBalance)
		{
			return false;
		}
		else
		{
			_Account.AccountBalance -= Amount;
			Save();
			return true;
		}

	}
	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{
			TotalBalances += Client.getAccountBalance();
		}

		return TotalBalances;
	}
};
