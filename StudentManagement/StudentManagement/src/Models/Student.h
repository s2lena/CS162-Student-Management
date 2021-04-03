#ifndef STUDENT_H
#define STUDENT_H

#include "Common.h"
#include "Account.h"
#include <string>

struct Student {
    int AccountID;
    std::string FirstName;
    std::string LastName;
    Sex Sex;
    Date Birthday;
    std::string ClassName;
};

bool GetStudents(Student*** outStudents, int* outNumOfStudents);
bool SaveStudents(Student** students, int numOfStudents, bool changeNum);
void ClearStudents(Student** students, int numOfStudents);
Student* GetStudent(int studentID);

#endif // STUDENT_H
