#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "../../Models/clsScreen.h"
#include "../../Models/clsBankClient.h"
using namespace std;
    /*
    This screen will be used to display a list of all clients in the system, only users with permissions to view client lists can access this screen.
    */
class clsClientListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "\t| " << setw(13) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(13) << left << Client.getPhone();
        cout << "| " << setw(18) << left << Client.getEmail();
        cout << "| " << setw(8) << left << Client.getPinCode();
        cout << "| " << setw(8) << left << Client.getAccountBalance() << "|" << endl;

    }
public:
    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        _DrawScreenHeader("       Clients List Screen","  (" + to_string(vClients.size()) + ") Clint(s).");
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+---------+\n";
        cout << left;
        cout << "\t|" << setw(14) << "Account Number" << "|";
        cout << setw(21) << "Client Name" << "|";
        cout << setw(14) << "Phone" << "|";
        cout << setw(19) << "Email" << "|";
        cout << setw(9) << "PinCode" << "|";
        cout << setw(9) << "Balance" << "|\n";
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+---------+\n";
        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordLine(C);
            }
        }
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+---------+\n";
    }

};

