#include "Account.h"
#include "Lecturer.h"
#include "Staff.h"
#include "Student.h"
#include <fstream>

bool GetAccounts(Account*** outAccounts, int* outNumOfAccounts)
{
    using namespace std;

    ifstream ifs;

    ifs.open("data/accounts.txt");

    int numAccounts = 0;
    ifs >> numAccounts;

    Account** accounts = new Account* [numAccounts] { nullptr };

    int role = 0;

    for (int i = 0; i < numAccounts; i++) {
        accounts[i] = new Account();
        ifs >> accounts[i]->AccountID;
        ifs.ignore();
        getline(ifs, accounts[i]->Username);
        getline(ifs, accounts[i]->Password);
        ifs >> role;
        accounts[i]->Role = (Role)role;
        ifs >> accounts[i]->RoleID;
    }

    ifs.close();
    if (outNumOfAccounts != nullptr) {
        *outNumOfAccounts = numAccounts;
    }

    if (outAccounts != nullptr) {
        *outAccounts = accounts;
    }

    return true;
}

bool SaveAccounts(Account** accounts, const int numOfAccounts, bool changeNum)
{
    using namespace std;
    ofstream ofs;
    ofs.open("data/accounts.txt");
    if (changeNum)
        ofs << numOfAccounts - 1 << endl;
    else
        ofs << numOfAccounts << endl;

    int count = 1;
    for (int i = 0; i < numOfAccounts; i++) {
        if (accounts[i] != nullptr) {
            ofs << count << endl;
            ofs << accounts[i]->Username << endl;
            ofs << accounts[i]->Password << endl;
            ofs << (int)accounts[i]->Role << endl;
            ofs << accounts[i]->RoleID;
            count++;
            if (i + 2 == numOfAccounts && accounts[i + 1] == nullptr) {
            } 
            else if (i + 1 == numOfAccounts) {
            }
            else
                ofs << endl;
        }
    }

    ofs.close();
    return true;
}

void ClearAccounts(Account** accounts, int numOfAccounts)
{
    for (int i = 0; i < numOfAccounts; i++) {
        if (accounts[i] != nullptr) {
            delete accounts[i];
            accounts[i] = nullptr;
        }
    }
    delete[] accounts;
}