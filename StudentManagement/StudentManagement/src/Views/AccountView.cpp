#include "AccountView.h"
#include "LecturerView.h"
#include "Models/Class.h"
#include "StaffView.h"
#include "StudentView.h"
#include <Windows.h>
#include <iostream>

bool LoginMenu(Account** outAccount)
{
    while (true) {
        int choice = 0;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
        std::cout << "Please input a number you want to go: " << std::endl;
        SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
        std::cout << "1. Login" << std::endl
                  << "0. Exit program" << std::endl;
        std::cout << "Your answer is: ";
        std::cin >> choice;

        system("cls");
        if (choice == 0)
            return false;

        if (choice != 1) {
            std::cout << "!!!!!" << std::endl;
            continue;
        }

        std::string username;
        std::string password;
        SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
        std::cout << "Login to program, please input your account:" << std::endl;
        SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
        std::cout << "Username: ";
        std::cin.ignore();
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);

        system("cls");

        Account* account = Login(username, password);
        if (account == nullptr) {
            std::cout << "Login failed!" << std::endl;
            continue;
        }

        std::cout << "Login successfully!" << std::endl;
        if (outAccount != nullptr) {
            *outAccount = account;
        }
        return true;
    }
}

bool ProfileView(Account* account)
{
    system("cls");
    switch (account->Role) {
    case Role::Lecturer:
        ViewProfileLecturer(account->RoleID);
        break;
    case Role::Staff:
        ViewProfileStaff(account->RoleID);
        break;
    case Role::Student:
        ViewStudentProfile(account->RoleID);
        break;
    default:
        break;
    }
    bool status = true;
    int t;
    while (status) {
        std::cout << "0. Back to menu" << std::endl;
        std::cin >> t;
        switch (t) {
            system("cls");
        case 0:
            status = false;
            break;
        default:
            std::cout << "Not update" << std::endl;
            break;
        }
    }
    return true;
}
bool ChangePasswordView(Account* account)
{
    system("cls");
    bool status = true;
    while (status) {
        std::string currentPassword;
        std::string compareNewPassword;
        std::string newPassword;
        std::cout << "Current password: ";
        std::cin.ignore();
        std::getline(std::cin, currentPassword);
        std::cout << "New password: ";
        std::getline(std::cin, newPassword);
        std::cout << "New password: ";
        std::getline(std::cin, compareNewPassword);
        std::cout << "Are you sure to change password" << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "0. No" << std::endl;
        int t = 0;
        std::cin >> t;
        if (t == 1) {
            if (currentPassword.compare(account->Password) != 0) {
                std::cout << "Current password is wrong!" << std::endl;
            } else if (newPassword.compare(compareNewPassword) != 0) {
                std::cout << "2 new password is not same!!" << std::endl;
            }
        } else {
            std::cout << "Cancel to change password!" << std::endl;
        }
        int choice;
        while (status) {
            std::cout << "0. Back to menu" << std::endl;
            std::cin >> choice;
            if (choice == 0)
                status = false;
            else
                std::cout << "Not update" << std::endl;
        }
    }
    return true;
}

void LecturerMenu(Account* account)
{
    system("cls");
    bool status = true;
    while (status) {
        std::cout << "1. View list of courses in the current semester" << std::endl;
        std::cout << "2. View list of students of a course" << std::endl;
        std::cout << "3. View attendance list of a course" << std::endl;
        std::cout << "4. Edit an attendance" << std::endl;
        std::cout << "5. Import scoreboard of a course from a csv file" << std::endl;
        std::cout << "6. Edit grade of a student" << std::endl;
        std::cout << "7. View a scoreboard" << std::endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
        std::cout << "0. Return to main menu" << std::endl;
        std::cout << "Your answer is: ";
        SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 0:
            status = false;
            break;
        default:
            LecturerView(choice, account);
            break;
        }
    }
}

void StaffMenu(Account* account)
{
    system("cls");
    bool status = true;
    while (status) {
        std::cout << "1. Import students of a class from a csv file" << std::endl;
        std::cout << "2. Add a new student to a class" << std::endl;
        std::cout << "3. Edit an existing student" << std::endl;
        std::cout << "4. Remove a student" << std::endl;
        std::cout << "5. Change students from class A to class B" << std::endl;
        std::cout << "6. View list of classes" << std::endl;
        std::cout << "7. View list of students in a class" << std::endl;
        std::cout << "8. Create/ update/ delete/ view academic years and semesters" << std::endl;
        std::cout << "9. Import courses from a csv file" << std::endl;
        std::cout << "10. Add a new course" << std::endl;
        std::cout << "11. Remove a course" << std::endl;
        std::cout << "12. Edit an existing course" << std::endl;
        std::cout << "13. Remove a specific student from a course" << std::endl;
        std::cout << "14. Add a specific student to a course" << std::endl;
        std::cout << "15. View list of courses in the current semester" << std::endl;
        std::cout << "16. View list of students of a course" << std::endl;
        std::cout << "17. View attendance list of a course" << std::endl;
        std::cout << "18. Create/ update/ delete/ view all lecturers" << std::endl;
        std::cout << "19. Search and view the scoreboard of a course" << std::endl;
        std::cout << "20. Export a scoreboard to a csv file" << std::endl;
        std::cout << "21. Search and view attendance list of a course" << std::endl;
        std::cout << "22. Export a attendance list to a csv file" << std::endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
        std::cout << "0. Return to main menu" << std::endl;
        std::cout << "Your answer is: ";
        SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);

        int choice;
        std::cin >> choice;
        switch (choice) {
        case 0:
            status = false;
            break;
        default:
            StaffView(choice);
            break;
        }
    }
}

void StudentMenu(Account* account)
{
    system("cls");
    bool status = true;
    while (status) {
        std::cout << "1. Check-in" << std::endl;
        std::cout << "2. View check-in result" << std::endl;
        std::cout << "3. View schedules" << std::endl;
        std::cout << "4. View scores of a course" << std::endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
        std::cout << "0. Return to main menu" << std::endl;
        std::cout << "Your answer is: ";
        SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);

        int choice;
        std::cin >> choice;
        switch (choice) {
        case 0:
            status = false;
            break;
        default:
            StudentView(choice, account);
            break;
        }
    }
}

bool ShowMenuView(Account* account)
{
    switch (account->Role) {
    case Role::Staff:
        StaffMenu(account);
        break;
    case Role::Lecturer:
        LecturerMenu(account);
        break;
    case Role::Student:
        StudentMenu(account);
        break;
    default:
        break;
    }
    return true;
}