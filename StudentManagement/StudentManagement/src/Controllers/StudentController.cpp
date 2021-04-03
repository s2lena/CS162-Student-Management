#include "StudentController.h"
#include <iostream>

void ViewStudentProfile(int studentID)
{
    Student* found = GetStudent(studentID);

    std::cout << "Student ID: ";
    std::cout << found->AccountID << std::endl;
    std::cout << "Student Fuillnmame: ";
    std::cout << found->FirstName << " " << found->LastName << std::endl;
    std::cout << "Sex: ";
    if (found->Sex == Sex::Female)
        std::cout << "Female" << std::endl;
    else if (found->Sex == Sex::Male)
        std::cout << "Male" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
    std::cout << "Student Birthday: ";
    if ((int)found->Birthday.Day < 10)
        std::cout << "0";
    std::cout << (int)found->Birthday.Day << " ";
    if ((int)found->Birthday.Month < 10)
        std::cout << "0";
    std::cout << (int)found->Birthday.Month << " ";
    std::cout << (int)found->Birthday.Year << std::endl;
    std::cout << "Student Class: ";
    std::cout << found->ClassName << std::endl;

    delete found;
}