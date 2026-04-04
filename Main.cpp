#include <iostream>
#include "Ui/clsLoginScreen.h"
using namespace std;



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
