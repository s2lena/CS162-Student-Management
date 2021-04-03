#include "Class.h"
#include <iostream>

bool TestImportClass()
{
    using namespace std;
    cout << "Debug" << endl;

    Class classes;
    classes.head = nullptr;
    ImportClass(classes);

    Node* cur = classes.head;
    while (cur != nullptr) {
        cout << cur->no << " ";
        cout << cur->student->AccountID << " ";
        cout << cur->student->FirstName << " ";
        cout << cur->student->LastName << " ";
        cout << (int)cur->student->Sex << " ";
        cout << (int)cur->student->Birthday.Day << "/";
        cout << (int)cur->student->Birthday.Month << "/";
        cout << (int)cur->student->Birthday.Year << " ";
        cout << endl;
        cur = cur->pNext;
    }
    DeleteClass(classes);
    return true;
}