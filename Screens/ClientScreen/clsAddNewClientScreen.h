#pragma once
#include "../../Models/clsScreen.h"
#include <string>
#include "../../Core/clsInputValidate.h"
#include "../../Models/clsBankClient.h"
using namespace std;
/*
    This screen will be used to add new client to the system, only users with permissions to add new client can access this screen.
*/
class clsAddNewClientScreen : protected clsScreen  
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.setFirstName(clsInputValidate::ReadString("Enter First Name: "));
        Client.setLastName(clsInputValidate::ReadString("Enter Last Name: "));
        Client.setEmail(clsInputValidate::ReadString("Enter Email: "));
        Client.setPhone(clsInputValidate::ReadString("Enter Phone: "));
        Client.setPinCode(clsInputValidate::ReadString("Enter PinCode: "));
        Client.setAccountBalance(clsInputValidate::ReadFloatNumber("Enter Account Balance: "));
    }
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
    static void _AddNewClient()
    {
        string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

        while (clsBankClient::isClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("\nAccount Number Is Already Used, Choose another one: ");
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }

    }
    public:
        static void AddNewClientScreen()
        {
            if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            {
                return;// this will exit the function and it will not continue
            }

            _DrawScreenHeader("      Add New Client Screen");
            _DrawUserAndDate(CurrentUser.GetUserName());
            _AddNewClient();
        }
   
};

