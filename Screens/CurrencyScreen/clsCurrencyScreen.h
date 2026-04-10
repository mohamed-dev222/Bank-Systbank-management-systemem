#pragma once
#include <iostream>
#include "../../Models/clsScreen.h"
#include "../../Global.h"
#include "../../Core/clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include <iomanip>
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;
class clsCurrencyScreen : protected clsScreen
{
private:
    enum enManageCurrencyMenueOption
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        Currencycalculator = 4,
        eMainMenue = 5
    };
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowCurrencyScreen();
    }
    static void _ShowListCurrencyScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesList();
    }
    static void _ShowFindCurrencyScreen()
    {
       clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateRateScreen()
    {
       clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static int _ReadCurrencyMenueOption(string Text)
    {
        cout << "\t\t\t\t " << Text;
        int num = clsInputValidate::ReadIntNumberBetween(1, 5);
        return num;
    }
    static void _PerformManageCurrencyMenueOption(enManageCurrencyMenueOption MenueOption)
    {
        switch (MenueOption)
        {
        case enManageCurrencyMenueOption::eListCurrencies:
        {
            system("cls");
            _ShowListCurrencyScreen();
            _GoBackToMainMenue();
            break;
        }

        case enManageCurrencyMenueOption::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToMainMenue();
            break;
        }

        case enManageCurrencyMenueOption::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToMainMenue();
            break;
        }

        case enManageCurrencyMenueOption::Currencycalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToMainMenue();
            break;
        }

        case enManageCurrencyMenueOption::eMainMenue:
        {
            break;
        }
        }
    }

public:
    static void ShowCurrencyScreen()
    {
        system("cls");
        _DrawScreenHeader("Currency Exchange Main Screen");
        _DrawUserAndDate(CurrentUser.GetUserName());
        cout << "\t\t\t\t ============================================";
        cout << "\n\t\t\t\t\t   " << setw(25) << "Currency Exchange Menue";
        cout << "\n\t\t\t\t ============================================\n";
        string Text[5] = {"List Currencies.", "Find Currency.", "Update Rate.", "Currency calculator.", "Main Menue."};
        _MenuOptionsScreen(5, Text);
        cout << "\t\t\t\t ============================================\n";

        _PerformManageCurrencyMenueOption((enManageCurrencyMenueOption)_ReadCurrencyMenueOption("Choose what do you want to do? [1 to 5]?"));
    }
};