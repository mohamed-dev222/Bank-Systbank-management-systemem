#pragma once
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>

using namespace std;
/*  
    This screen will be used to manage users in the system, only users with permissions to manage users can access this screen.
*/
class clsManageUsersScreen :protected clsScreen
{

private:
    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };
    static short _ReadUserMenueOption(string Text)
    {
        cout << "\t\t\t\t " << Text;
        short Choose = clsInputValidate::ReadIntNumberBetween(1, 6);
        return Choose;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUserList();

    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();

    }

    static void _ShowDeleteUserScreen()
    {
     
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }


    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("cls");

            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {
            break;
        }
        }

    }



public:


    static void ShowManageUsersMenue()
    {

        system("cls");
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader("\tManage Users Screen");
        _DrawUserAndDate(CurrentUser.GetUserName());

        cout << "\t\t\t\t ============================================";
        cout << "\n\t\t\t\t\t\t" << setw(25) << "Manage Users Menue";
        cout << "\n\t\t\t\t ============================================\n";
        string Text[6] = { "List Users." , "Add New User." , "Delete User." , "Update User." , "Find User." , "Main Menue."  };
        _MenuOptionsScreen(6, Text);
        cout << "\t\t\t\t ============================================\n";
        

        _PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadUserMenueOption("Choose what do you want to do? [1 to 6]?"));
    }

};

