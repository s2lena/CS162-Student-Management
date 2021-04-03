#ifndef COMMON_H
#define COMMON_H

enum class Role {
    Student = 0,
    Lecturer,
    Staff,
};

enum class Sex {
    Male = 0,
    Female,
    Unknown,
};

enum class Status {
    Absent= 0,
    Present,
};

struct Date {
    short Day;
    short Month;
    short Year;
};

#endif // COMMON_H
