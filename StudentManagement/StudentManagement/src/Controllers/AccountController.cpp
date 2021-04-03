#include "AccountController.h"
#include <iostream>

Account* Login(std::string username, std::string password)
{
    Account** accounts = nullptr;
    int numOfAccounts = 0;
    bool status = GetAccounts(&accounts, &numOfAccounts);

    Account* found = nullptr;

    for (int i = 0; i < numOfAccounts; i++) {
        if (username.compare(accounts[i]->Username) == 0)
            if (password.compare(accounts[i]->Password) == 0) {
                found = accounts[i];
                accounts[i] = nullptr;
                break;
            }
    }
    ClearAccounts(accounts, numOfAccounts);
    return found;
}

bool ChangePassword(Account* account, std::string currentPassword, std::string newPassword)
{

    if (currentPassword.compare(account->Password) != 0)
        return false;
    account->Password = newPassword;

    Account** accounts = nullptr;
    int numOfAccounts = 0;
    bool status = GetAccounts(&accounts, &numOfAccounts);
    for (int i = 0; i < numOfAccounts; i++) {
        if (accounts[i]->Username.compare(account->Username) == 0)
            if (accounts[i]->Password.compare(currentPassword) == 0) {
                accounts[i]->Password = newPassword;
                break;
            }
    }

    SaveAccounts(accounts, numOfAccounts, false);
    ClearAccounts(accounts, numOfAccounts);

    return true;
}

bool Logout(Account* account)
{
    if (account != nullptr) {
        delete account;
        return true;
    }
    return false;
}