#include "StaffView.h"
#include "Models/Class.h"
#include <iostream>

bool ImportView()
{
    Class classes;
    classes.head = nullptr;
    classes.count = 0;
    std::string classname;
    std::cout << "Input classname: ";
    std::cin.ignore();
    std::getline(std::cin, classname);
    if (!ImportClass(classes, classname))
        return false;
    SaveProfileStudent(classes);
    CreateAllAccount(classes);
    DeleteClass(classes);
    return true;
}

bool AddStudentView()
{
    std::string str;
    Student* student = new Student;
    std::cout << "StudentID: ";
    std::cin >> student->AccountID;
    std::cout << "First Name: ";
    std::cin.ignore();
    std::getline(std::cin, student->FirstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, student->LastName);
    std::cout << "Class Name: ";
    std::getline(std::cin, student->ClassName);
    std::cout << "Sex: ";
    std::getline(std::cin, str);
    if (str == "Female")
        student->Sex = Sex::Female;
    else if (str == "Male")
        student->Sex = Sex::Male;
    else
        student->Sex = Sex::Unknown;
    std::cout << "Birthday: ";
    std::cin >> student->Birthday.Day >> student->Birthday.Month >> student->Birthday.Year;

    AddNewStudent(student);
    delete student;
    return true;
}

bool EditStudentView()
{
    int ID;
    std::cout << "Input studentID to change: ";
    std::cin >> ID;

    std::cout << "Information to change: " << std::endl;
    std::string str;
    Student* student = new Student;
    std::cout << "StudentID: ";
    std::cin >> student->AccountID;
    std::cout << "First Name: ";
    std::cin.ignore();
    std::getline(std::cin, student->FirstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, student->LastName);
    std::cout << "Class Name: ";
    std::getline(std::cin, student->ClassName);
    std::cout << "Sex: ";
    std::getline(std::cin, str);
    if (str == "Female")
        student->Sex = Sex::Female;
    else if (str == "Male")
        student->Sex = Sex::Male;
    else
        student->Sex = Sex::Unknown;
    std::cout << "Birthday: ";
    std::cin >> student->Birthday.Day >> student->Birthday.Month >> student->Birthday.Year;

    RemoveAStudent(ID);
    AddNewStudent(student);

    return true;
}

bool RemoveAStudentView()
{
    int ID;
    std::cout << "Input studentID: ";
    std::cin >> ID;

    return RemoveAStudent(ID);
}

bool ChangeClassView()
{
    int ID;
    std::cout << "Input studentID to change: ";
    std::cin >> ID;

    std::string classname;
    std::cout << "Input classname to change: ";
    std::cin.ignore();
    std::getline(std::cin, classname);

    return ChangeStudentFromClassAtoClassB(ID, classname);
}

bool ViewListOfStudents()
{
    std::string classname;
    std::cout << "Input classname to view list of students: ";
    std::cin.ignore();
    std::getline(std::cin, classname);

    return ViewListOfStudent(classname);
}

bool ViewListOfClasses()
{
    ClassNode* pH = nullptr;
    LoadListOfClasses(pH);
    
    ClassNode* cur = pH;
    while (pH != nullptr) {
        std::cout << pH->classname << std::endl;
        pH = pH->pNext;
        delete cur;
        cur = pH;
    }
    
    return true;
}

bool StaffView(int choice)
{
    switch (choice) {
    case 1:
        if (ImportView())
            std::cout << "Import successfully" << std::endl;
        else
            std::cout << "Import failed!" << std::endl;
        break;
    case 2:
        AddStudentView();
        std::cout << "Add Student successful" << std::endl;
        break;
    case 3:
        EditStudentView();
        std::cout << "Edit student successfully" << std::endl;
        break;
    case 4:
        if (RemoveAStudentView())
            std::cout << "Remove student succesfully" << std::endl;
        else
            std::cout << "Remove student failed!" << std::endl;
        break;
    case 5:
        if (ChangeClassView())
            std::cout << "Change class successfully" << std::endl;
        else
            std::cout << "Change class failed!" << std::endl;
        break;
    case 6:
        ViewListOfClasses();
        break;
    case 7:
        if (!ViewListOfStudents())
            std::cout << "Invalid classname" << std::endl;
        break;
    default:
        break;
    }
    return true;
}