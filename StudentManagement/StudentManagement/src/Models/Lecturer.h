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

bool SaveLecturers(Lecturer** lecturers, int numOfLecturers, bool changeNum);
bool GetLecturers(Lecturer*** outLecturers, int* outNumOfLecturers);
Lecturer* GetLecturer(int lecturerID);
bool CheckExistLecturer(Lecturer lecterer);
bool CreateProfileLecturer(std::string account, Lecturer newLecturer);
void ClearLecturers(Lecturer** lecturers, int numOfLectuerers);
bool DeleteLecturer(std::string account, Lecturer lecturer);

#endif // LECTURER_H
