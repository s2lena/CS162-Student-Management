#ifndef CHECKIN_H
#define CHECKIN_H

#include "Common.h"
#include <string>

struct CheckIn {
    int CourseID;
    int StudentID;
    std::string CheckInDate;
    Status Status;
};

#endif // CHECKIN_H
