#pragma once

#include <iostream>
#include "../../Models/clsScreen.h"
#include <iomanip>
#include <fstream>
#include "../../Models/clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{

private:
    static void _PrintTransferLogRecordLine(stTrnsferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName  << "|\n";
    }

public:
    static void ShowTransferLogScreen()
    {

        vector<stTrnsferLogRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();

        string Title = "    Transfer Log List Screen";
        string SubTitle = "(" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        _DrawUserAndDate(CurrentUser.GetUserName());
        cout << "\t+------------------------+---------+---------+---------+-----------+-----------+---------+\n";
        cout << left;
        cout << "\t|" << setw(24) << "Date/Time" << "|";
        cout << setw(9) << "s.Acct" << "|";
        cout << setw(9) << "d.Acct" << "|";
        cout << setw(9) << "Amount" << "|";
        cout << setw(11) << "s.Balance" << "|";
        cout << setw(11) << "d.Balance" << "|";
        cout << setw(9) << "User" << "|\n";
        cout << "\t+------------------------+---------+---------+---------+-----------+-----------+---------+\n";

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (stTrnsferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogRecordLine(Record);
            }

        cout << "\t+------------------------+---------+---------+---------+-----------+-----------+---------+\n";
    }
};
