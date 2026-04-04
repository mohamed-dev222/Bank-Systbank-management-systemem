#pragma once
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "../../Models/clsBankClient.h"
class clsDeleteClientScreen :
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
	static void _DeleteClient()
	{
		string AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
		while (!(clsBankClient::isClientExist(AccountNumber)))
		{
			AccountNumber = clsInputValidate::ReadString("Account Number Is Not Found, Choose Another One: ");
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		Client1.Print();
		char Answer = 'n';
		cout << "\nAre You Sure You Want to Delete This Client y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";


				_PrintClient(Client1);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}

		}
		else
		{
			cout << "Deletion has been canceled.\n";
		}

	}
public:

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;// this will exit the function and it will not continue
		}
		_DrawScreenHeader("    Delete Client Screen.");
		_DeleteClient();
	}


};

