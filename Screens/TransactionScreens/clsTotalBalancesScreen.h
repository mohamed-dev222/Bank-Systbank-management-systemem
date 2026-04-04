#pragma once
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Models/clsBankClient.h"
#include "../../Core/clsUtil.h"
#include <iomanip>
/*
    This screen will be used to display the total balances of all clients in the system, only users with permissions to view total balances can access this screen.
*/
class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << "\t| " << setw(14) << left << Client.AccountNumber();
        cout << "| " << setw(29) << left << Client.FullName();
        cout << "| " << setw(8) << left << Client.getAccountBalance() << "|" << endl;

    }
public:
    

    static void ShowTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        cout << "\n\t\t\tBalance List (" << vClients.size() << ") Clients.\n\n";
        cout << "\t+---------------+------------------------------+---------+\n";
        cout << left;
        cout << "\t|" << setw(15) << "Account Number" << "|";
        cout << setw(30) << "Client Name" << "|";
        cout << setw(9) << "Balance" << "|\n";
        cout << "\t+---------------+------------------------------+---------+\n";
        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordBalanceLine(C);
            }
        }
        cout << "\t+---------------+------------------------------+---------+\n";
     
        double TotalBalances = clsBankClient::GetTotalBalances();
        cout << "\t"<< setw(8) << left << "" << "Total Balances = " << TotalBalances << endl;
        cout << "\t    "<< setw(8) << left << "" << "( " << to_string(TotalBalances )<< " )";
    }

    };

