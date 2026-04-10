#pragma once
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Core/clsPerson.h"
#include "../../Models/clsUser.h"
#include "../../Core/clsInputValidate.h"
/*
    This screen will be used to find existing users in the system, only users with permissions to manage users can access this screen.
 */
class clsFindUserScreen :protected clsScreen
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

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");
        _DrawUserAndDate(CurrentUser.GetUserName());
        string UserName;
        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        while (!clsUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};

