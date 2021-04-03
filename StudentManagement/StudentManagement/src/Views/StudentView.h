#ifndef STUDENT_VIEW_H
#define STUDENT_VIEW_H

#include "Models/Account.h"
#include "Models/Attendance.h"
#include "StaffView.h"
#include <iostream>

bool ViewCheckin(int ID);
bool GetACourse(std::string courseID, std::string classname, std::string sem, std::string aca);
bool ViewSchedule(Account* account);
bool ViewScore(int ID);
bool StudentView(int choice, Account* account);

#endif // STUDENT_VIEW_H
