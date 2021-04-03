#include "AccountController.h"
#include <iostream>

bool TestLoginAndChangePasswordAndLogout()
{
    std::string username = "tiendb";
    std::string password = "Aa12345";
    Account* user = Login(username, password);
    if (user != nullptr) {
        std::string newpassword = "12345Aa";
        bool status = ChangePassword(user, password, newpassword);
        std::cout << user->Username << std::endl;
        std::cout << user->Password << std::endl;
    }
    return Logout(user);
}