#pragma once
#include "../Models/clsScreen.h"
#include "../Core/clsInputValidate.h"
#include "../Screens/ClientScreen/clsClientListScreen.h"
#include "../Screens/ClientScreen/clsAddNewClientScreen.h"
#include <iomanip>
#include "../Screens/ClientScreen/clsDeleteClientScreen.h"
#include "../Screens/ClientScreen/clsUpdateClientScreen.h"
#include "../Screens/ClientScreen/clsShowFindClientScreen.h"
#include "../Screens/TransactionScreens/clsTransactionsScreen.h"
#include "../Screens/UserScreen/clsManageUsersScreen.h"
#include "../Global.h"
#include "../Screens/LogScreen/clsLoginRegisterScreen.h"
#include "../Screens/CurrencyScreen/clsCurrencyScreen.h"
/*
	This screen will be used as the main entry point for the application, providing access to all available features based on the user's permissions.
*/
class clsMaineScreen : protected clsScreen
{
private:
	enum enMainMenueOptions
	{
		eListClients = 1,
		eAddNewClient = 2,
		eDeleteClient = 3,
		eUpdateClient = 4,
		eFindClient = 5,
		eShowTransactionsMenue = 6,
		eManageUsers = 7,
		eLoginRegister = 8,
		eCurrencyExchange = 9,
		eLogin = 10,
		eExit = 11
	};
	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::AddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsShowFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}
	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _ShowCurrencyScreen()
	{
		clsCurrencyScreen::ShowCurrencyScreen();
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static short _ReadMainMenueOption(string Text)
	{
		cout << "\t\t\t\t " << Text;
		short Choose = clsInputValidate::ReadIntNumberBetween(1, 11);
		return Choose;
	}
	static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eShowTransactionsMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
		    ShowMainMenue();
			break;
		};
		case enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ShowManageUsersMenue();
		    ShowMainMenue();
			break;
		};
		case enMainMenueOptions::eLoginRegister:
		{
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		};
		case enMainMenueOptions::eCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyScreen();
		    ShowMainMenue();
			break;
		};
		case enMainMenueOptions::eLogin:
		{
			system("cls");
			_Logout();
			break;
		};
		case enMainMenueOptions::eExit:
		{
			exit(0);
			break;
		};
	}
}

public:

	static void ShowMainMenue()
	{
		system("cls");
		cout << left;
		_DrawScreenHeader("\tMain Screen");
		_DrawUserAndDate(CurrentUser.GetUserName());
		cout << "\t\t\t\t ============================================";
		cout << "\n\t\t\t\t\t\t" << setw(25) << "Main Menue";
		cout << "\n\t\t\t\t ============================================\n";
		string Text[11] = {"Show Client List.", "Add New Client.", "Delete Client.", "Update Client Info.", "Find Client.", "Transaction.", "Manage Users.", "Login Register.", "Currency Exchange.", "Logout.", "Exit."};
		_MenuOptionsScreen(11, Text);
		cout << "\t\t\t\t ============================================\n";
		_PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption("Choose What Do You Want To Do? [1 to 11]? "));
	}
};