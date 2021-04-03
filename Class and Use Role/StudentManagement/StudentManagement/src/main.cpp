#include "Views/AccountView.h"
#include "Views/LecturerView.h"
#include "Models/Class.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    Account* account = nullptr;

    if (!LoginMenu(&(account)))
        return 0;

    bool status = true;
    while (status) {
        int choice = 0;
        cout << "Please input a number you want to go:" << endl;
        cout << "1. View your profile" << endl;
        cout << "2. Change password" << endl;
        cout << "3. Show menu" << endl;
        cout << "4. Exit program" << endl;

        cin >> choice;
        switch (choice) {
        case 1:
            ProfileView(account);
            break;
        case 2:
            ChangePasswordView(account);
            break;
        case 3:
            ShowMenuView(account);
            break;
        case 4:
            status = false;
            break;
        default:
            cout << "Invalid way, try again!" << endl;
            break;
        }

    }

    delete account;
}