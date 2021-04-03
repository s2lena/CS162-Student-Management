#include "Account.h"
#include <iostream>

bool TestSaveAndGetDataAccounts()
{
    using namespace std;

    int numOfAccounts = 3;
    Account** accounts = new Account* [numOfAccounts] { nullptr };

    accounts[0] = new Account();
    accounts[0]->AccountID = 1;
    accounts[0]->Username = "tuht";
    accounts[0]->Password = "Aa12345";
    accounts[0]->Role = Role::Staff;
    accounts[0]->RoleID = 1;

    accounts[1] = new Account();
    accounts[1]->AccountID = 2;
    accounts[1]->Username = "tiendb";
    accounts[1]->Password = "Aa12345";
    accounts[1]->Role = Role::Lecturer;
    accounts[1]->RoleID = 1;

    accounts[2] = new Account();
    accounts[2]->AccountID = 3;
    accounts[2]->Username = "190001";
    accounts[2]->Password = "Aa12345";
    accounts[2]->Role = Role::Student;
    accounts[2]->RoleID = 190001;

    SaveAccounts(accounts, numOfAccounts);

    Account** accountsGet = nullptr;
    int numOfAccountsGet = 0;

    bool status = GetAccounts(&accountsGet, &numOfAccountsGet);

    if (numOfAccounts != numOfAccountsGet)
        return false;

    for (int i = 0; i < numOfAccounts; i++) {
        if (accounts[i]->AccountID != accountsGet[i]->AccountID)
            return false;
        if (accounts[i]->Username.compare(accountsGet[i]->Username) != 0)
            return false;
        if (accounts[i]->Password.compare(accountsGet[i]->Password) != 0)
            return false;
        if (accounts[i]->Role != accountsGet[i]->Role)
            return false;
        if (accounts[i]->RoleID != accountsGet[i]->RoleID)
            return false;
    }

    ClearAccounts(accounts, numOfAccounts);
    ClearAccounts(accountsGet, numOfAccountsGet);
    return true;
}

