#pragma once
#include "../../Models/clsScreen.h"
#include "../../Global.h"
#include <iomanip>
#include "../../Models/clsCurrency.h"
#include <string>
class clsCurrenciesListScreen : protected clsScreen
{
private:
static void _PrinCurrencyList(clsCurrency CurrencyList)
    {

        cout << "\t| " << setw(29) << left << CurrencyList.Country();
        cout << "| " << setw(9) << left << CurrencyList.CurrencyCode();
        cout << "| " << setw(39) << left << CurrencyList.CurrencyName();
        cout << "| " << setw(9) << left << CurrencyList.Rate() << "|" << endl;

    }
public:
static void ShowCurrenciesList()
{
    vector <clsCurrency> vCurrencyList = clsCurrency::GetCurrenciesList();
    string Text = "("+ to_string(vCurrencyList.size()) + ") Currency.";
    _DrawScreenHeader("    Currencies List Screen", Text);
    _DrawUserAndDate(CurrentUser.GetUserName());
    cout << "\t+------------------------------+----------+----------------------------------------+----------+\n";
        cout << left;
        cout << "\t|" << setw(30) << "Country " << "|";
        cout << setw(10) << "Code" << "|";
        cout << setw(40) << "Name" << "|";
        cout << setw(10) << "Rate/(1$)" << "|\n";
    cout << "\t+------------------------------+----------+----------------------------------------+----------+\n";
        if (vCurrencyList.empty())
        {
            cout << "\t\t\t\tNo Currency Available In the System!";
        }
        else
        {
            for (clsCurrency &Record : vCurrencyList)
            {

                _PrinCurrencyList(Record);
            }
        }
    cout << "\t+------------------------------+----------+----------------------------------------+----------+\n";
    
}
};