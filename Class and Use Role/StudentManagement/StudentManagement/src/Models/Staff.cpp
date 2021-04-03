#include "Staff.h"
#include <fstream>
#include <iostream>

bool GetStaffs(Staff*** outStaffs, int* outNumOfStaffs)
{
    using namespace std;

    ifstream ifs;
    ifs.open("data/staff.txt");

    int numOfStaffs;
    ifs >> numOfStaffs;

    Staff** staffs = new Staff* [numOfStaffs] { nullptr };

    int sex = 0;

    for (int i = 0; i < numOfStaffs; i++) {
        staffs[i] = new Staff;
        ifs >> staffs[i]->AccountID;
        ifs.ignore();
        getline(ifs, staffs[i]->FirstName);
        getline(ifs, staffs[i]->LastName);
        ifs >> sex;
        staffs[i]->Sex = (Sex)sex;
    }

    ifs.close();

    if (outStaffs != nullptr) {
        *outStaffs = staffs;
    }
    if (outNumOfStaffs != nullptr) {
        *outNumOfStaffs = numOfStaffs;
    }

    return true;
}

bool SaveStaffs(Staff** staffs, const int numOfStaffs)
{
    using namespace std;

    ofstream ofs;
    ofs.open("data/staff.txt");

    ofs << numOfStaffs << endl;

    for (int i = 0; i < numOfStaffs; i++) {
        ofs << staffs[i]->AccountID << endl;
        ofs << staffs[i]->FirstName << endl;
        ofs << staffs[i]->LastName << endl;
        ofs << (int)staffs[i]->Sex;
        if (i + 1 != numOfStaffs)
            ofs << endl;
    }

    ofs.close();
    return true;
}

void ClearStaffs(Staff** staffs, int numOfStaffs)
{
    for (int i = 0; i < numOfStaffs; i++) {
        if (staffs[i] != nullptr) {
            delete staffs[i];
            staffs[i] = nullptr;
        }
    }
    delete[] staffs;
}

Staff* GetStaff(int staffID)
{
    Staff** staffs = nullptr;
    int numOfStaffs = 0;

    bool status = GetStaffs(&staffs, &numOfStaffs);

    Staff* staff = nullptr;

    for (int i = 0; i < numOfStaffs; i++) {
        if (staffs[i]->AccountID == staffID) {
            staff = staffs[i];
            staffs[i] = nullptr;
            break;
        }
    }

    ClearStaffs(staffs, numOfStaffs);

    return staff;
}