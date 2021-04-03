#ifndef COURSE_H
#define COURSE_H

#include "Lecturer.h"
#include <string>

struct Course {
    std::string CourseID;
    std::string CourseName;
    std::string Class;
    std::string LecturerAccount;
    Lecturer lecturer;
    std::string Classroom;
    std::string StartDate;
    std::string EndDate;
    std ::string StartHour;
    std::string EndHour;
    std::string DayOfWeek;
    std::string Semester;
    std::string AcademicYear;
};

struct CourseNode {
    int ID;
    Course* course;
    CourseNode* pNext;
};

struct CourseHead {
    CourseNode* head;
};

std::string ChooseFile(std::string semester, std::string academic, std::string classname);
short DetectCourse(std::string str, short t);
void SeperateLine(CourseNode*& current, std::string line);
bool ImportCourse(CourseHead& course, std::string semester, std::string academic, std::string classname);
bool SaveCourse(CourseHead course);
bool SaveAllCourse(CourseHead course);
bool GetCourse(CourseHead& course);
bool AddCourse(Course* course);
bool RemoveCourse(std::string courseID, std::string classname, std::string sem, std::string aca);
void DeleteCourse(CourseHead& course);
bool EditCourse(Course* course,std::string courseID, std::string classname);


#endif // COURSE_H
