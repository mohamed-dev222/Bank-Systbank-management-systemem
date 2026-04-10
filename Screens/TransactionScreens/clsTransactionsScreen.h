#pragma once
#include "../../Models/clsScreen.h"
#include "../../Core/clsInputValidate.h"
#include "clsWithdrawScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "../LogScreen/clsTransferLogScreen.h"
#include <iomanip>



class clsTransactionsScreen :
    protected clsScreen
{
private:
	static short _ReadTransactionMenueOption(string Text)
	{
		cout << "\t\t\t\t " << Text;
		short Choose = clsInputValidate::ReadIntNumberBetween(1, 6);
		return Choose;
	}
	enum enTransactionMenueOptions {
		eDeposit = 1, eWithdraw = 2,
		eTotalBalances = 3, eTransfer = 4,eTransferLog = 5, eMainMenue = 6
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
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
      static void _ShowTransfersLogScreen()
	  {
		clsTransferLogScreen::ShowTransferLogScreen();
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
		case enTransactionMenueOptions::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		};
		case enTransactionMenueOptions::eTransferLog:
		{
			system("cls");
			 _ShowTransfersLogScreen();
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
		_DrawUserAndDate(CurrentUser.GetUserName());
		cout << "\t\t\t\t ============================================";
		cout << "\n\t\t\t\t\t      " << setw(25) << "Transaction Menue";
		cout << "\n\t\t\t\t ============================================\n";
		string Text[6] = { "Deposit.", "Withdraw.", "Total Balances.","Transfer.","Transfer Log.", "Main Menue." };
		_MenuOptionsScreen(6, Text);
		cout << "\t\t\t\t ============================================\n";
		_PerfromTransactionMenueOption((enTransactionMenueOptions)_ReadTransactionMenueOption("Choose What Do You Want To Do? [1 to 6]? "));

	}
};

