#ifndef LECTURER_H
#define LECTURER_H

#include "Common.h"
#include "Account.h"
#include <string>

struct Lecturer {
    int AccountID;
    std::string FirstName;
    std::string LastName;
    Sex Sex;
    std::string Title;
};

bool SaveLecturers(Lecturer** lecturers, int numOfLecturers);
bool GetLecturers(Lecturer*** outLecturers, int* outNumOfLecturers);
Lecturer* GetLecturer(int lecturerID);
bool TestSaveAndGetLecturers();
bool TestViewLecturerProfile();
void ClearLecturers(Lecturer** lecturers, int numOfLectuerers);

#endif // LECTURER_H
