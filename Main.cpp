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
    
    while ((true))
    {
        if(!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
        
    }
    system("pause>0");
    
    return 0;
}
