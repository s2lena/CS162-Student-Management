#ifndef LECTURER_VIEW_H
#define LECTURER_VIEW_H

#include "Models/Lecturer.h"
#include "StaffView.h"
#include <iostream>
#include <string>

int GetID(std::string academic, std::string semester, std::string coursename, std::string classname);
bool ViewAttendanceOfACourse();
bool EditAttendanceView(Account* account);
bool ImportScoreboardView(Account* account);
bool EditGradeView(Account* account);
bool LecturerView(int choice, Account* account);
char CheckLectureraccount(std::string account, std::string course, std::string classname, std::string aca, std::string sem);
bool ListOfCourseOfLecturerView(Account* account);
bool EnrolmentOfACourse(Account* account);
bool CheckPermission(Account* account, std::string classname, std::string course, std::string sem, std::string aca);
bool ListOfStudentsInCourseViewLecturer(bool check, Account* account);
char CheckLecturerAccountNew(std::string account, std::string course, std::string classname);
bool ViewAttendanceOfACourseLecturer(Account* account);

#endif // LECTURER_VIEW_H