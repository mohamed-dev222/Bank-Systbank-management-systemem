#include <iostream>
#include "Ui/clsLoginScreen.h"
using namespace std;

/**
 * The main function serves as the entry point for the application.
 * It handles the initial user interaction and controls the flow of the login process.
 * TODO: Implement a loop to allow users to attempt logging in multiple times if they choose to do so.
 */
int main()
{
    char Answer = 'n';
    cout << "Do you want to log in?Y/N?  ";
    cin >> Answer;
    while ((Answer == 'Y') || (Answer == 'y'))
    {
        clsLoginScreen::ShowLoginScreen();
        cout << "Do you want to log in again?Y/N? ";
        cin >> Answer;
    }
    
    return 0;
}
