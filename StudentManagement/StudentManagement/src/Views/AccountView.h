#ifndef ACCOUNT_VIEW_H
#define ACCOUNT_VIEW_H

#include "Models/Account.h"
#include "Controllers/AccountController.h"
#include "Controllers/StaffController.h"
#include "Controllers/LecturerController.h"
#include "Controllers/StudentController.h"

bool LoginMenu(Account** outAccount);
bool ProfileView(Account* account);
bool ChangePasswordView(Account* account);
bool ShowMenuView(Account* account);
void LecturerMenu(Account* account);
void StaffMenu(Account* account);
void StudentMenu(Account* account);

#endif // ACCOUNT_VIEW_H
