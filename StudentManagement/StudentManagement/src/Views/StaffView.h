#ifndef STAFF_VIEW_H
#define STAFF_VIEW_H

#include "LecturerView.h"
#include "Models/Attendance.h"

bool StaffView(int choice);
bool ImportView();
bool AddStudentView();
bool EditStudentView();
bool RemoveAStudentView();
bool ChangeClassView();
bool ViewListOfStudents();
bool ViewListOfClasses();
bool AcademicView();
bool ImportCourseView();
bool AddCourseView();
bool RemoveCourseView();
bool EditCourseView();
bool RemoveSpecificStudentView();
bool AddSpecificStudentView();
bool ListOfCourseView();
bool ListOfStudentsInCourseView(bool check); //
bool FeatureLecturerView();
bool ExportScoreboardView();
bool ExportAttendanceView();

#endif // STAFF_VIEW_H