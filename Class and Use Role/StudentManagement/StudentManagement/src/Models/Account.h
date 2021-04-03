#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Common.h"
#include <string>

struct Account {
    int AccountID;
    std::string Username;
    std::string Password;
    Role Role;
    int RoleID;
};

bool GetAccounts(Account*** outAccounts, int* outNumOfAccounts);
bool SaveAccounts(Account** accounts, const int numOfAccounts);
bool TestSaveAndGetDataAccounts();
bool TestLoginAndChangePasswordAndLogout();
void ClearAccounts(Account** Accounts, int numOfAccounts);

#endif // ACCOUNT_H
