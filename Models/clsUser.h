#pragma once
#include <iostream>
#include <string>
#include "../Core/clsDate.h"
#include "../Core/clsPerson.h"
#include "../Core/clsString.h"
#include "../Core/clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;
/*
    This class represents a user in the system, it inherits from clsPerson and contains additional information related to the user's account, such as username, password, and permissions. It also includes methods for loading and saving user data to a file, as well as methods for updating and adding new users.
*/
struct stLogRegisterRecord
{
    string DateTime;
    string UserName;
    string Password;
    int Permissions;
};

class clsUser : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        if (vUserData.size() < 7)
        {
            return _GetEmptyUserObject();
        }

        return clsUser(enMode::UpdateMode,
                       vUserData[0], vUserData[1], vUserData[2],
                       vUserData[3], vUserData[4],
                       clsUtil::DecryptText(vUserData[5]),
                       stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.getFirstName() + Seperator;
        UserRecord += User.getLastName() + Seperator;
        UserRecord += User.getEmail() + Seperator;
        UserRecord += User.getPhone() + Seperator;
        UserRecord += User.GetUserName() + Seperator;
        UserRecord += clsUtil::EncryptText(User.GetPassword()) + Seperator;
        UserRecord += to_string(User.GetPermissions());

        return UserRecord;
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {

        vector<clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                if (Line.empty())
                    continue;
                clsUser User = _ConvertLinetoUserObject(Line);
                if (!User.IsEmpty())
                    vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    // we only write records that are not marked for delete.
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.GetUserName() == GetUserName())
            {
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PreparelLogInRecord(string Seperator = "#//#")
    {
        string LogInRecord = "";
        LogInRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LogInRecord += GetUserName() + Seperator;
        LogInRecord += clsUtil::EncryptText(GetPassword()) + Seperator;
        LogInRecord += to_string(GetPermissions());

        return LogInRecord;
    }
    static stLogRegisterRecord _ConvertLineToLoginRegisterRecord(string Line, string Seperator = "#//#")
    {
        vector<string> vData;
        vData = clsString::Split(Line, Seperator);

        stLogRegisterRecord Record;

        if (vData.size() < 4)
            return Record;

        Record.DateTime = vData[0];
        Record.UserName = vData[1];
        Record.Password = clsUtil::DecryptText(vData[2]);
        Record.Permissions = stoi(vData[3]);

        return Record;
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string UserName, string Password,
            int Permissions) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }
    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pLoginRegister = 128
    };
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2,
        svErroe = 3
    };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                // We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
        return enSaveResults::svErroe;
    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.GetUserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->GetPermissions() == enPermissions::eAll)
            return true;

        if ((Permission & this->GetPermissions()) == Permission)
            return true;
        else
            return false;
    }
    void RegisterLogin()
    {
        string DateLine = _PreparelLogInRecord();
        fstream MyFile;
        MyFile.open("LoginHistory.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << DateLine << endl;
            MyFile.close();
        }
    }
    static vector<stLogRegisterRecord> GetLoginRegisterList()
    {
        vector<stLogRegisterRecord> vRecords;

        fstream MyFile;
        MyFile.open("LoginHistory.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stLogRegisterRecord Record = _ConvertLineToLoginRegisterRecord(Line);
                vRecords.push_back(Record);
            }

            MyFile.close();
        }

        return vRecords;
    }
};
