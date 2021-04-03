#include "LecturerController.h"
#include <iostream>

void ViewProfileLecturer(int ID)
{
    using namespace std;

    Lecturer* found = GetLecturer(ID);

    cout << "Lecturer ID: ";
    cout << found->AccountID << endl;
    cout << "Fullname of lecturer: ";
    cout << found->FirstName << " " << found->LastName << endl;
    cout << "Sex: ";
    if (found->Sex == Sex::Male)
        cout << "Male" << endl;
    else if (found->Sex == Sex::Female)
        cout << "Female" << endl;
    else
        cout << "Unknown" << endl;
    cout << "Title of lecturer: ";
    cout << found->Title << endl;   

    delete found;
}