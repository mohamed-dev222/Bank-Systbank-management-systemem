#pragma once
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "../../Models/clsBankClient.h"
class clsUpdateClientScreen :
    protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& Client)
	{

		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name  : " << Client.getFirstName();
		cout << "\nLast Name   : " << Client.getLastName();
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.getEmail();
		cout << "\nPhone       : " << Client.getPhone();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.getPinCode();
		cout << "\nBalance     : " << Client.getAccountBalance();
		cout << "\n___________________\n";
	}
	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.setFirstName(clsInputValidate::ReadString("Enter First Name: "));
		Client.setLastName(clsInputValidate::ReadString("Enter Last Name: "));
		Client.setEmail(clsInputValidate::ReadString("Enter Email: "));
		Client.setPhone(clsInputValidate::ReadString("Enter Phone: "));
		Client.setPinCode(clsInputValidate::ReadString("Enter PinCode: "));
		Client.setAccountBalance(clsInputValidate::ReadFloatNumber("Enter Account Balance: "));
	}
	static void _UpdateClient()
	{
		string AccountNumber = clsInputValidate::ReadString("Please Enter Client Account Number: ");
		while (!clsBankClient::isClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString("Account Number Is Not Found , choose Auther one: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		
		char Answer;
		cout << "Are You Sure You Want To Update This Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate Client Info:-";
			cout << "\n______________________\n";
			_ReadClientInfo(Client);
			cout << "\n______________________\n";
			clsBankClient::enSaveResults SaveResults;
			SaveResults = Client.Save();
			switch (SaveResults)
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Update Successfuly :-) \n";
				Client.Print();
				break;
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nEror Account Was Not Saved Because it's Empty";
				break;
			}
		}

	}
public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;// this will exit the function and it will not continue
		}
		_DrawScreenHeader("    Update Client Screen.");
		_UpdateClient();
	}
};

