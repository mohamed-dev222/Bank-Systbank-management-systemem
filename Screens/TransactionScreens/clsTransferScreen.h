#pragma omnce
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "../../Global.h"
#include "../../Models/clsBankClient.h"
#include "../../Core/clsPerson.h"
using namespace std;
class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.getAccountBalance();
        cout << "\n___________________\n";
    }
    static string _ReadAccountNumber()
    {
        string AccountNumber;
        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number to Transfer From: ");
        while (!clsBankClient::isClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
        }
        return AccountNumber;
    }
    static float _ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > SourceClient.getAccountBalance())
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:
    static void ShowTransferScreen()
    {

        _DrawScreenHeader("\tTransfer Screen");
        _DrawUserAndDate(CurrentUser.GetUserName());

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = _ReadAmount(SourceClient);

        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.GetUserName()))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }
};
