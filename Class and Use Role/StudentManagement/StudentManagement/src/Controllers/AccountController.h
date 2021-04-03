#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include "Models/Account.h"
#include <string>

// return null if failed
Account* Login(std::string username, std::string password);

// return true if success
bool ChangePassword(Account* account, std::string currentPassword, std::string newPassword);

bool Logout(Account* account);

#endif // ACCOUNT_CONTROLLER_H
