#define _CRT_SECURE_NO_WARNINGS

#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "AcademicSemester.h"
#include "Account.h"
#include "Course.h"
#include "Enrollment.h"
#include <ctime>
#include <fstream>
#include <iostream>

struct Attendance {
    int studentID;
    int courseID;
    Date date;
    Status status;
};

struct AttendanceNode {
    Attendance attendance;
    AttendanceNode* pNext;
};

std::string GetCourseID(int ID);
void GetNowAcademic(std::string& sem, std::string& aca);
void SaveAttendance(AttendanceNode* pH);
void GetAttendance(AttendanceNode*& pH);
void ClearAttendance(AttendanceNode*& pH);
bool CheckExistAttendance(Attendance attend);
void Checkin(Account* account);
bool CheckEnrollment(int ID, std::string classname, std::string coursename, std::string sem, std::string aca);
Course* FindCourse(struct tm* curtime, int studentID, int& courseID);
bool CreateAllAttend(Attendance attend, Course* course);
bool EditAttendance(int ID, int courseID, Status status);
bool ExportAttendance(int ID, std::string course, std::string classname, std::string sem, std::string aca);

#endif // ATTENDANCE_H
