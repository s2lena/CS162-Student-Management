#include "Class.h"
#include <iostream>

bool TestImportClassAndEditStudent()
{
    using namespace std;
    cout << "Debug" << endl;

    Class classes;
    classes.head = nullptr;
    ImportClass(classes, "19CTT1");
    Student student;
    student.AccountID = 19005;
    student.FirstName = "Ho";
    student.LastName = "Duong";
    student.Sex = Sex::Male;
    student.Birthday = { 8, 10, 2001 };
    AddNewStudent(classes, student);
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
   
    student.AccountID = 19002;
    student.FirstName = "Nguy";
    student.LastName = "Lam";
    student.Birthday = { 28, 10, 2001 };
    student.Sex = Sex::Male;
    
    cout << EditExistingStudent(classes, student.AccountID, student) << endl;
    int ID = 19003;
    cout << RemoveAStudent(classes, ID) << endl;
    cout << SaveClass(classes, "19CTT1") << endl;
    cur = classes.head;
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

bool TestChangeClass()
{
    using namespace std;

    cout << ChangeStudentFromClassAtoClassB("19CTT1", "19CTT2", 19002) << endl;
    return true;
}