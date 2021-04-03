#include "Lecturer.h"
#include <fstream>
#include <iostream>

bool GetLecturers(Lecturer*** outLecturers, int* outNumOfLecturers)
{
    using namespace std;

    ifstream ifs;

    ifs.open("data/lecturer.txt");

    int numOfLecturers = 0;
    ifs >> numOfLecturers;

    Lecturer** lecturers = new Lecturer* [numOfLecturers] { nullptr };

    int sex = 0;

    for (int i = 0; i < numOfLecturers; i++) {
        lecturers[i] = new Lecturer();
        ifs >> lecturers[i]->AccountID;
        ifs.ignore();
        getline(ifs, lecturers[i]->FirstName);
        getline(ifs, lecturers[i]->LastName);
        ifs >> sex;
        lecturers[i]->Sex = (Sex)sex;
        ifs.ignore();
        getline(ifs, lecturers[i]->Title);
    }

    ifs.close();
    if (outNumOfLecturers != nullptr) {
        *outNumOfLecturers = numOfLecturers;
    }

    if (outLecturers != nullptr) {
        *outLecturers = lecturers;
    }

    return true;
}

bool SaveLecturers(Lecturer** lecturers, int numOfLecturers, bool changeNum)
{
    using namespace std;

    ofstream ofs;
    ofs.open("data/lecturer.txt");

    if (changeNum)
        ofs << numOfLecturers - 1 << endl;
    else
        ofs << numOfLecturers << endl;
    int count = 1;
    for (int i = 0; i < numOfLecturers; i++) {
        if (lecturers[i] != nullptr) {
            ofs << count << endl;
            ofs << lecturers[i]->FirstName << endl;
            ofs << lecturers[i]->LastName << endl;
            ofs << (int)lecturers[i]->Sex << endl;
            ofs << lecturers[i]->Title;
            if (i + 2 == numOfLecturers && lecturers[i + 1] == nullptr) {
            } 
            else if (i + 1 == numOfLecturers) {
            } 
            else
                ofs << endl;
            count++;
        }
    }

    ofs.close();
    return true;
}

void ClearLecturers(Lecturer** lecturers, int numOfLectuerers)
{
    for (int i = 0; i < numOfLectuerers; i++) {
        if (lecturers[i] != nullptr) {
            delete lecturers[i];
            lecturers[i] = nullptr;
        }
    }
    delete[] lecturers;
}

Lecturer* GetLecturer(int lecturerID)
{
    Lecturer** lecturers = nullptr;
    int numOfLecturers = 0;

    bool status = GetLecturers(&lecturers, &numOfLecturers);

    Lecturer* lecturer = nullptr;

    for (int i = 0; i < numOfLecturers; i++) {
        if (lecturers[i]->AccountID == lecturerID) {
            lecturer = lecturers[i];
            lecturers[i] = nullptr;
            break;
        }
    }

    ClearLecturers(lecturers, numOfLecturers);

    return lecturer;
}

bool CheckExistLecturer(Lecturer lecturer)
{
    int numOfLecturers = 0;
    Lecturer** lecturers = nullptr;
    GetLecturers(&lecturers, &numOfLecturers);

    for (int i = 0; i < numOfLecturers; i++) {
        if (lecturers[i]->FirstName == lecturer.FirstName)
            if (lecturers[i]->LastName == lecturer.LastName)
                if (lecturers[i]->Title == lecturer.Title)
                    if (lecturers[i]->Sex == lecturer.Sex) {
                        ClearLecturers(lecturers, numOfLecturers);
                        return true;
                    }
    }
    if (numOfLecturers != 0)
        ClearLecturers(lecturers, numOfLecturers);
    return false;
}

bool CreateProfileLecturer(std::string account, Lecturer lecturer)
{
    if (CheckExistLecturer(lecturer))
        return false;

    int numOfBefore = 0;
    Lecturer** before = nullptr;
    GetLecturers(&before, &numOfBefore);

    int numOfLecturers = numOfBefore + 1;
    Lecturer** lecturers = new Lecturer*[numOfBefore + 1];
    int i = 0;
    if (numOfBefore != 0) {
        for (; i < numOfBefore; i++) {
            lecturers[i] = new Lecturer;
            lecturers[i]->AccountID = before[i]->AccountID;
            lecturers[i]->FirstName = before[i]->FirstName;
            lecturers[i]->LastName = before[i]->LastName;
            lecturers[i]->Title = before[i]->Title;
            lecturers[i]->Sex = before[i]->Sex;
        }
    }
    lecturers[i] = new Lecturer;
    lecturers[i]->AccountID = numOfBefore + 1;
    lecturers[i]->FirstName = lecturer.FirstName;
    lecturers[i]->LastName = lecturer.LastName;
    lecturers[i]->Title = lecturer.Title;
    lecturers[i]->Sex = lecturer.Sex;

    int numOfAccounts = 0;
    Account** accounts = nullptr;
    GetAccounts(&accounts, &numOfAccounts);

    int numOfNewAccount = numOfAccounts + 1;
    Account** newAccount = new Account*[numOfAccounts + 1];
    i = 0;
    if (numOfAccounts != 0) {
        for (; i < numOfAccounts; i++) {
            newAccount[i] = new Account;
            newAccount[i]->AccountID = accounts[i]->AccountID;
            newAccount[i]->Username = accounts[i]->Username;
            newAccount[i]->Password = accounts[i]->Password;
            newAccount[i]->Role = accounts[i]->Role;
            newAccount[i]->RoleID = accounts[i]->RoleID;
        }
    }
    newAccount[i] = new Account;
    newAccount[i]->AccountID = numOfAccounts + 1;
    newAccount[i]->Username = account;
    newAccount[i]->Password = "Aa12345";
    newAccount[i]->Role = Role::Lecturer;
    newAccount[i]->RoleID = numOfBefore + 1;

    SaveLecturers(lecturers, numOfLecturers, false);
    SaveAccounts(newAccount, numOfNewAccount, false);
    if (numOfBefore != 0)
        ClearLecturers(before, numOfBefore);
    ClearLecturers(lecturers, numOfLecturers);
    if (numOfAccounts != 0)
        ClearAccounts(accounts, numOfAccounts);
    ClearAccounts(newAccount, numOfNewAccount);
    return true;
}

bool DeleteLecturer(std::string account, Lecturer lecturer)
{
    bool check = false;
    int num = 0;
    Lecturer** lecturers = nullptr;
    GetLecturers(&lecturers, &num);

    for (int i = 0; i < num; i++) {
        if (lecturers[i]->FirstName == lecturer.FirstName)
            if (lecturers[i]->LastName == lecturer.LastName)
                if (lecturers[i]->Title == lecturer.Title)
                    if (lecturers[i]->Sex == lecturer.Sex) {
                        Lecturer* tmp = lecturers[i];
                        lecturers[i] = nullptr;
                        check = true;
                        delete tmp;
                    }
    }

    if (check)
        SaveLecturers(lecturers, num, true);
    ClearLecturers(lecturers, num);
    if (!check)
        return false;

    int numAcc = 0;
    Account** accounts = nullptr;

    GetAccounts(&accounts, &numAcc);

    for (int i = 0; i < numAcc; i++) {
        if (accounts[i]->Username == account) {
            Account* tmp = accounts[i];
            accounts[i] = nullptr;
            delete tmp;
            check = false;
            break;
        }
    }
    if (check == false)
        SaveAccounts(accounts, numAcc, true);
    ClearAccounts(accounts, numAcc);

    return true;
}