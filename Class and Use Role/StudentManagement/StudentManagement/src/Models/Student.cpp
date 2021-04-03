#include "Student.h"
#include <fstream>
#include <iostream>

bool GetStudents(Student*** outStudents, int* outNumOfStudents)
{
    using namespace std;

    ifstream ifs;
    ifs.open("data/student.txt");

    int numOfStudents = 0;
    ifs >> numOfStudents;

    int tmp = 0;
    Student** students = new Student* [numOfStudents] { nullptr };

    for (int i = 0; i < numOfStudents; i++) {
        students[i] = new Student;
        ifs >> students[i]->AccountID;
        ifs.ignore();
        getline(ifs, students[i]->FirstName);
        getline(ifs, students[i]->LastName);
        ifs >> tmp;
        students[i]->Sex = (Sex)tmp;
        ifs >> tmp;
        students[i]->Birthday.Day = (int)tmp;
        ifs >> tmp;
        students[i]->Birthday.Month = (int)tmp;
        ifs >> tmp;
        students[i]->Birthday.Year = (int)tmp;
        ifs.ignore();
        getline(ifs, students[i]->ClassName);
    }

    ifs.close();

    if (outNumOfStudents != nullptr)
        *outNumOfStudents = numOfStudents;
    if (outStudents != nullptr)
        *outStudents = students;
    return true;
}

bool SaveStudents(Student** students, int numOfStudents)
{
    using namespace std;

    ofstream ofs;
    ofs.open("data/student.txt");

    ofs << numOfStudents << endl;

    for (int i = 0; i < numOfStudents; i++) {
        ofs << students[i]->AccountID << endl;
        ofs << students[i]->FirstName << endl;
        ofs << students[i]->LastName << endl;
        ofs << (int)students[i]->Sex << endl;
        ofs << (int)students[i]->Birthday.Day << " ";
        ofs << (int)students[i]->Birthday.Month << " ";
        ofs << (int)students[i]->Birthday.Year << endl;
        ofs << students[i]->ClassName;
        if (i + 1 != numOfStudents)
            ofs << endl;
    }

    ofs.close();
    return true;
}

void ClearStudents(Student** students, int numOfStudents)
{
    for (int i = 0; i < numOfStudents; i++) {
        if (students[i] != nullptr) {
            delete students[i];
            students[i] = nullptr;
        }
    }
    delete[] students;
}

Student* GetStudent(int studentID)
{
    Student* found = nullptr;
    
    Student** students = nullptr;
    int numOfStudents = 0;

    GetStudents(&students, &numOfStudents);

    for (int i = 0; i < numOfStudents; i++) {
        if (students[i]->AccountID == studentID) {
            found = students[i];
            students[i] = nullptr;
            break;
        }
    }

    ClearStudents(students, numOfStudents);

    return found;
}
