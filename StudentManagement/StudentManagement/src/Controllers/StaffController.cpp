#include "StaffController.h"
#include <iostream>

void ViewProfileStaff(int ID) {
    using namespace std;

    Staff* found = GetStaff(ID);

    cout << "Staff ID: ";
    cout << found->AccountID << endl;
    cout << "Fullname of staff: ";
    cout << found->FirstName << " " << found->LastName << endl;
    cout << "Sex: ";
    if (found->Sex == Sex::Male)
        cout << "Male" << endl;
    else if (found->Sex == Sex::Female)
        cout << "Female" << endl;
    else
        cout << "Unknown" << endl;

    delete found;
}