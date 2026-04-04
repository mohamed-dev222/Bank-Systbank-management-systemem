#pragma once
#include "../../Models/clsScreen.h"
#include "../../Models/clsBankClient.h"
#include "../../Core/clsInputValidate.h"
class clsShowFindClientScreen :
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
public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;// this will exit the function and it will not continue
		}
		_DrawScreenHeader("    Find Client Screen");
		string AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
		while (!(clsBankClient::isClientExist(AccountNumber)))
		{
			AccountNumber = clsInputValidate::ReadString("Account Number Is Not Found, Choose Another One: ");
		}
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_PrintClient(Client);
	}
};

