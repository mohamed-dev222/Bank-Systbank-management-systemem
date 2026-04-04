#pragma once
#include "../../Models/clsScreen.h"
#include "../../Models/clsUser.h"
#include <iomanip>
/*
    This screen will be used to display a list of all users in the system, only users with permissions to view user lists can access this screen.
*/
class clsListUsersScreen :
    protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsUser User)
    {

        cout << "\t| " << setw(13) << left << User.GetUserName();
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(13) << left << User.getPhone();
        cout << "| " << setw(18) << left << User.getEmail();
        cout << "| " << setw(8) << left << User.GetPassword();
        cout << "| " << setw(8) << left << User.GetPermissions() << "  |" << endl;

    }
public:
    static void ShowUserList()
    {
        vector <clsUser> vClients = clsUser::GetUsersList();
        _DrawScreenHeader("       User List Screen", "  (" + to_string(vClients.size()) + ") User(s).");
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+-----------+\n";
        cout << left;
        cout << "\t|" << setw(14) << "Account Number" << "|";
        cout << setw(21) << "User Name" << "|";
        cout << setw(14) << "Phone" << "|";
        cout << setw(19) << "Email" << "|";
        cout << setw(9) << "Password" << "|";
        cout << setw(9) << "Permissions" << "|\n";
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+-----------+\n";
        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsUser& C : vClients)
            {
                _PrintClientRecordLine(C);
            }
        }
        cout << "\t+--------------+---------------------+--------------+-------------------+---------+-----------+\n";
    }

};

