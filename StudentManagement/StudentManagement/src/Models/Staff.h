#ifndef STAFF_H
#define STAFF_H

#include "Common.h"
#include "Account.h"
#include <string>

struct Staff {
    int AccountID;
    std::string FirstName;
    std::string LastName;
    Sex Sex;
};

Staff* GetStaff(int staffID);
bool GetStaffs(Staff*** outStaffs, int* outNumOfStaffs);
bool SaveStaffs(Staff** staffs, const int numOfStaffs);
void ClearStaffs(Staff** staffs, int numOfStaffs);

#endif // STAFF_H
