#include "StudentView.h"
#include <Windows.h>
#include <iomanip>
using namespace std;

bool ViewCheckin(int ID)
{
    AttendanceNode* pH = nullptr;
    GetAttendance(pH);
    AttendanceNode* cur = pH;
    bool check = false;
    while (cur != nullptr) {
        if (cur->attendance.studentID == ID && cur->attendance.status == Status::Present) {
            check = true;
            cout << cur->attendance.studentID << " ";
            cout << GetCourseID(cur->attendance.courseID) << " ";
            cout << cur->attendance.date.Day << " ";
            cout << cur->attendance.date.Month << " ";
            cout << cur->attendance.date.Year << " ";
            cout << "Present" << endl;
        }
        cur = cur->pNext;
    }

    if (!check)
        cout << "No check in to show" << endl;

    ClearAttendance(pH);
    return true;
}

bool GetACourse(std::string courseID, std::string classname, std::string sem, std::string aca)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);
    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->Semester == sem && cur->course->AcademicYear == aca) {
            if (cur->course->CourseID == courseID && cur->course->Class == classname) {
                cout << left << setw(10) << cur->course->CourseID;
                cout << left << setw(10) << cur->course->DayOfWeek;
                cout << left << setw(10) << cur->course->StartHour;
                cout << left << setw(8) << cur->course->EndHour;
                cout << cur->course->Classroom << endl;
                // cout << left << setW(...) << ... to set equal space.
                break;
            }
        }
        cur = cur->pNext;
    }
    DeleteCourse(pH);
    return true;
}

bool ViewSchedule(Account* account)
{
    std::string sem, aca;
    GetNowAcademic(sem, aca);

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    bool check = false;
    int count = 1;
    while (cur != nullptr) {
        if (cur->enrollment.studentID == to_string(account->RoleID))
            if (sem == cur->enrollment.semester && aca == cur->enrollment.academic) {
                if (count == 1) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << left << setw(3) << "No " << left << setw(10) << "Course"
                         << left << setw(15) << "Date"
                         << left << setw(7) << "TimeStart"
                         << left << setw(8) << "TimeEnd"
                         << "Room\n";
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                }
                cout << left << setw(3) << count;
                check = GetACourse(cur->enrollment.coursename, cur->enrollment.classname, sem, aca);
                count++;
            }
        cur = cur->pNext;
    }
    if (!check)
        cout << "No course to view" << endl;
    DeleteEnrollment(pH);
    return true;
}

bool ViewScore(int ID)
{
    string course, semester, academic;
    cout << "Academic(2019-2020,...): ";
    cin.ignore();
    getline(cin, academic);
    cout << "Semester(HK1, HK2, HK3): ";
    getline(cin, semester);
    cout << "Coursename: ";
    getline(cin, course);

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    bool check = false;
    int count = 1;
    while (cur != nullptr) {
        if (cur->enrollment.academic == academic && cur->enrollment.semester == semester) {
            if (cur->enrollment.coursename == course && cur->enrollment.studentID == to_string(ID)) {
                if (!check) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << "No StudentID  Fullname            Classname Midterm Final Lab Bonus" << endl;
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                }
                Student* student = GetStudent(stoi(cur->enrollment.studentID));
                cout << left << setw(3) << count;
                cout << left << setw(11) << cur->enrollment.studentID;
                cout << left << setw(20) << student->FirstName + ' ' + student->LastName;
                cout << left << setw(10) << student->ClassName;
                cout << left << setw(8) << cur->enrollment.midterm;
                cout << left << setw(6) << cur->enrollment.final;
                cout << left << setw(4) << cur->enrollment.lab;
                cout << cur->enrollment.bonus << endl;
                check = true;
                delete student;
                break;
            }
        }
        cur = cur->pNext;
    }
    if (!check)
        cout << "Can not find this course" << endl;
    DeleteEnrollment(pH);
    return true;
}

bool StudentView(int choice, Account* account)
{
    system("cls");
    switch (choice) {
    case 1:
        cout << "1. Check in" << endl;
        Checkin(account);
        break;
    case 2:
        cout << "2. View checkin result" << endl;
        ViewCheckin(account->RoleID);
        break;
    case 3:
        cout << "3. View schedule of student" << endl;
        ViewSchedule(account);
        break;
    case 4:
        cout << "4. View scoreboard of a course of student" << endl;
        ViewScore(account->RoleID);
        break;
    default:
        cout << "Not update" << endl;
        break;
    }

    bool status = true;
    while (status) {
        std::cout << "0. Back to menu" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 0:
            system("cls");
            status = false;
            break;
        default:
            std::cout << "Not update" << std::endl;
            break;
        }
    }

    return true;
}