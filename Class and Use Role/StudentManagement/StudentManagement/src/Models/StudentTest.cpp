#include "Student.h"

bool TestSaveAndGetStudents() {
    int numOfStudents = 3;

    Student** students = new Student* [3] { nullptr };

    students[0] = new Student;
    students[0]->AccountID = 19001;
    students[0]->FirstName = "Pham";
    students[0]->LastName = "Ha";
    students[0]->Sex = Sex::Female;
    students[0]->Birthday = { 28, 10, 2001 };
    students[0]->ClassName = "19CTT1";

    students[1] = new Student;
    students[1]->AccountID = 19002;
    students[1]->FirstName = "Pham";
    students[1]->LastName = "Hang";
    students[1]->Sex = Sex::Female;
    students[1]->Birthday = { 28, 11, 2001 };
    students[1]->ClassName = "19CTT2";

    students[2] = new Student;
    students[2]->AccountID = 19003;
    students[2]->FirstName = "Phuc";
    students[2]->LastName = "Minh";
    students[2]->Sex = Sex::Male;
    students[2]->Birthday = { 2, 10, 2001 };
    students[2]->ClassName = "19CTT2";

    SaveStudents(students, numOfStudents);

    Student** studentsGet = nullptr;
    int numOfStudentsGet = 0;

    GetStudents(&studentsGet, &numOfStudentsGet);

    if (numOfStudents != numOfStudentsGet)
        return false;

    for (int i = 0; i < numOfStudents; i++) {
        if (students[i]->AccountID != studentsGet[i]->AccountID)
            return false;
        if (students[i]->FirstName.compare(studentsGet[i]->FirstName) != 0)
            return false;
        if (students[i]->LastName.compare(studentsGet[i]->LastName) != 0)
            return false;
        if (students[i]->Sex != studentsGet[i]->Sex)
            return false;
        if (students[i]->Birthday.Day != studentsGet[i]->Birthday.Day)
            return false;
        if (students[i]->Birthday.Month != studentsGet[i]->Birthday.Month)
            return false;
        if (students[i]->Birthday.Year != studentsGet[i]->Birthday.Year)
            return false;
        if (students[i]->ClassName.compare(studentsGet[i]->ClassName) != 0)
            return false;
    }

    ClearStudents(students, numOfStudents);
    ClearStudents(studentsGet, numOfStudentsGet);

    return true;
}

