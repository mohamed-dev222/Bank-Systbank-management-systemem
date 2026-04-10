#pragma once
#include <iomanip>
#include "../../Models/clsScreen.h"
#include "../../Models/clsUser.h"
using namespace std;
class clsLoginRegisterScreen : protected clsScreen
{
    private:
   
    static void _PrintLoginRegisterRecordLine(stLogRegisterRecord LoginRegisterRecord)
    {

        cout << "\t| " << setw(29) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(19) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(19) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(19) << left << LoginRegisterRecord.Permissions << "|" << endl;

    }
    static void _ShowLoginRegisterList()
    {
        vector <stLogRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
  
        string Title = "  Login Register List Screen";
        string SubTitle =  "(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        _DrawUserAndDate(CurrentUser.GetUserName());
        cout << "\t+------------------------------+--------------------+--------------------+--------------------+\n";
        cout << left;
        cout << "\t|" << setw(30) << "Date / Time " << "|";
        cout << setw(20) << "User Name" << "|";
        cout << setw(20) << "Password" << "|";
        cout << setw(20) << "Permissions" << "|\n";
        cout << "\t+------------------------------+--------------------+--------------------+--------------------+\n";
        if (vLoginRegisterRecord.empty())
        {
            cout << "\t\t\t\tNo Logins Available In the System!";
        }
        else
        {
            for (stLogRegisterRecord &Record : vLoginRegisterRecord)
            {

                _PrintLoginRegisterRecordLine(Record);
            }
        }
        cout << "\t+------------------------------+--------------------+--------------------+--------------------+\n";
    
    }
    public:
    static void ShowLoginRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }
        _ShowLoginRegisterList();
    }


};