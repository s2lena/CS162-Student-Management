#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "Student.h"
#include <string>

struct Enrollment {
    std::string studentID;
    std::string classname;
    std::string coursename;
    std::string semester;
    std::string academic;
    double midterm = 0;
    double final = 0;
    double lab = 0;
    double bonus = 0;
};

struct EnrollNode {
    Enrollment enrollment;
    EnrollNode* pNext;
};

void SaveEnrollment(std::string classname,  std::string coursename, std::string semester, std::string academic);
void GetEnrollment(EnrollNode*& pH);
void SaveAllEnrollment(EnrollNode* pH);
bool DeleteAEnrollment(std::string ID,std::string classname, std::string course, std::string sem, std::string aca);
bool AddSpecificStudent(std::string ID,std::string classname, std::string course, std::string sem, std::string aca);
void DeleteEnrollment(EnrollNode*& pH);
bool CheckExistCourse(std::string classname, std::string course, std::string sem, std::string aca);
bool RemoveStudentOfCourse(std::string classname, std::string course, std::string sem, std::string aca);
bool ExportScoreboard(std::string classname, std::string course, std::string sem, std::string aca);
bool EditEnrollment(Enrollment enrollment);
bool ImportScoreboard(EnrollNode*& pH, std::string className, std::string coursename, std::string sem, std::string aca);
std::string ChooseFile(std::string className, std::string coursename, std::string sem, std::string aca);
short DetectEnroll(std::string str, short t);
void SeperateLineEnroll(EnrollNode*& current, std::string line);
bool ScanScoreboard(EnrollNode* pH);

#endif // ENROLLMENT_H
