#ifndef COURSE_H
#define COURSE_H

#include <string>

struct Course {
    int CourseID;
    std::string CourseName;
    int LecturerID;
    std::string Classroom;
    std::string Schedule;
};

#endif // COURSE_H
