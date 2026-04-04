#pragma once
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "clsWithdrawScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include <iomanip>
/*
    This screen will be used to display 
	the transaction menu and handle user selections
     for various transaction operations, only users with permissions
	  to perform transactions can access this screen.
*/
class clsTransactionsScreen :
    protected clsScreen
{
private:
	static short _ReadTransactionMenueOption(string Text)
	{
		cout << "\t\t\t\t " << Text;
		short Choose = clsInputValidate::ReadIntNumberBetween(1, 4);
		return Choose;
	}
	enum enTransactionMenueOptions {
		eDeposit = 1, eWithdraw = 2,
		eTotalBalances = 3, eMainMenue = 4
	};

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();

	}

	static void _PerfromTransactionMenueOption(enTransactionMenueOptions TransactionMenueOption)
	{
		switch (TransactionMenueOption)
		{
		case enTransactionMenueOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		};
		case enTransactionMenueOptions::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		};
		case enTransactionMenueOptions::eTotalBalances:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		};
		case enTransactionMenueOptions::eMainMenue:
		{
			break;
		};
		
		
		}

	}
public:
	static void ShowTransactionsMenue()
	{
		system("cls");
		if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;// this will exit the function and it will not continue
		}
		_DrawScreenHeader("      Transaction Screen");
		cout << "\t\t\t\t ============================================";
		cout << "\n\t\t\t\t\t      " << setw(25) << "Transaction Menue";
		cout << "\n\t\t\t\t ============================================\n";
		string Text[4] = { "Deposit.", "Withdraw.", "Total Balances.", "Main Menue." };
		_MenuOptionsScreen(4, Text);
		cout << "\t\t\t\t ============================================\n";
		_PerfromTransactionMenueOption((enTransactionMenueOptions)_ReadTransactionMenueOption("Choose What Do You Want To Do? [1 to 4]? "));

	}
};

