#include "Staff.h"
#include "Controllers/StaffController.h"
#include <iostream>

bool TestSaveAndGetDataStaff()
{
    using namespace std;

    int numOfStaffs = 3;

    Staff** staffs = new Staff* [3] { nullptr };

    staffs[0] = new Staff;
    staffs[0]->AccountID = 1;
    staffs[0]->FirstName = "Lam";
    staffs[0]->LastName = "Tram";
    staffs[0]->Sex = Sex::Male;

    staffs[1] = new Staff;
    staffs[1]->AccountID = 2;
    staffs[1]->FirstName = "Nguy";
    staffs[1]->LastName = "Vo Tien";
    staffs[1]->Sex = Sex::Male;

    staffs[2] = new Staff;
    staffs[2]->AccountID = 3;
    staffs[2]->FirstName = "Dao";
    staffs[2]->LastName = "Thuong";
    staffs[2]->Sex = Sex::Female;

    SaveStaffs(staffs, numOfStaffs);

    Staff** staffsGet = nullptr;
    int numOfStaffsGet = 0;

    GetStaffs(&staffsGet, &numOfStaffsGet);

    if (numOfStaffs != numOfStaffsGet)
        return false;

    for (int i = 0; i < numOfStaffs; i++) {
        if (staffs[i]->AccountID != staffsGet[i]->AccountID)
            return false;
        if (staffs[i]->FirstName.compare(staffsGet[i]->FirstName) != 0)
            return false;
        if (staffs[i]->LastName.compare(staffsGet[i]->LastName) != 0)
            return false;
        if (staffs[i]->Sex != staffsGet[i]->Sex)
            return false;
    }

    ClearStaffs(staffs, numOfStaffs);
    ClearStaffs(staffsGet, numOfStaffsGet);

    return true;
}
