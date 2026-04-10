#pragma once

#include <iostream>
#include "../Models/clsScreen.h"
#include "../Models/clsUser.h"
#include <iomanip>
#include "clsMaineScreen.h"
#include "../Global.h"
/*
    This screen will be used to handle user login functionality, allowing users to enter their credentials and access the system based on their permissions.
*/
class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 3;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                FaildLoginCount--;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You Have " << FaildLoginCount << " Trials to Login.\n\n";
            }
            if (FaildLoginCount == 0)
            {
                cout << "\nYou have exceeded the maximum number of login attempts. Exiting the program.\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();
            

        } while (LoginFaild && FaildLoginCount > 0);
        CurrentUser.RegisterLogin();
        clsMaineScreen::ShowMainMenue();
        return true;

    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _DrawUserAndDate();
        return _Login();
        

    }

};

