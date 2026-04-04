#pragma once
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Core/clsPerson.h"
#include "../../Models/clsUser.h"
#include "../../Core/clsInputValidate.h"
/*
    This screen will be used to delete existing users from the system, only users with permissions to manage users can access this screen.
*/
class clsDeleteUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        while (!clsUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};

