#include "LecturerView.h"
#include <Windows.h> //
#include <iomanip> //
using namespace std;

int GetID(string academic, string semester, string coursename, string classname)
{
    int ID = -1;
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);

    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->CourseID == coursename && cur->course->Class == classname && cur->course->Semester == semester && cur->course->AcademicYear == academic) {
            ID = cur->ID;
            break; //
        }
        cur = cur->pNext;
    }

    DeleteCourse(pH);
    return ID;
}

bool ViewAttendanceOfACourse()
{
    string academic, semester, coursename, classname;
    GetNowAcademic(semester, academic);
    cout << "Coursename: ";
    cin.ignore();
    getline(cin, coursename);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckExistCourse(classname, coursename, semester, academic)) {
        cout << "This course has not existed" << endl;
        return false;
    }

    int ID = GetID(academic, semester, coursename, classname);
    AttendanceNode* pH = nullptr;
    GetAttendance(pH);
    AttendanceNode* cur = pH;
    bool check = false;
    int i = 1;
    while (cur != nullptr) {
        if (cur->attendance.courseID == ID) {
            if (!check) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                cout << "No " << left << setw(9) << "ID"
                     << left << setw(20) << "Fullname"
                     << left << setw(10) << "Class"
                     << left << setw(10) << "Course"
                     << left << setw(14) << "Date(d-m-y)"
                     << "Attendance" << endl;
                SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
            }
            check = true;
            cout << left << setw(3) << i;
            cout << left << setw(9) << cur->attendance.studentID;
            Student* student = GetStudent(cur->attendance.studentID);
            cout << left << setw(20) << student->FirstName + ' ' + student->LastName;
            cout << left << setw(10) << student->ClassName;
            cout << left << setw(10) << coursename;
            if (cur->attendance.date.Day < 10)
                cout << "0";
            cout << cur->attendance.date.Day << "-";
            if (cur->attendance.date.Month < 10)
                cout << "0";
            cout << cur->attendance.date.Month << "-";
            cout << cur->attendance.date.Year << "    ";
            if (cur->attendance.status == Status::Present)
                cout << "Present" << endl;
            else
                cout << "Absent" << endl;
            delete student;
            i++;
        }
        cur = cur->pNext;
    }
    if (!check)
        cout << "There is no attendance of this course" << endl;
    ClearAttendance(pH);
    return true;
}

bool EditAttendanceView(Account* account)
{
    string academic, semester, coursename, classname;
    int studentID, tmp, courseID;
    Status status;
    GetNowAcademic(semester, academic);
    cin.ignore();
    cout << "Coursename: ";
    getline(cin, coursename);
    cout << "Classname: ";
    getline(cin, classname);
    if (!CheckLecturerAccountNew(account->Username, coursename, classname)) {
        cout << "You do not have permission to edit grade of this course" << endl;
        return false;
    }
    cout << "Student ID: ";
    cin >> studentID;
    cout << "Status 1 for present and 0 for absent: ";
    cin >> tmp;
    status = (Status)tmp;
    courseID = GetID(academic, semester, coursename, classname);
    if (EditAttendance(studentID, courseID, status))
        cout << "Edit attendance successfully" << endl;
    else
        cout << "This student does not enrollment this course or this course now does not open! " << endl;
    return true;
}

char CheckLectureraccount(std::string account, std::string course, std::string classname, std::string aca, std::string sem)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);

    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->CourseID == course && cur->course->Class == classname && cur->course->Semester == sem && cur->course->AcademicYear == aca) {
            if (cur->course->LecturerAccount == account) {
                DeleteCourse(pH);
                return true;
            }
        }
        cur = cur->pNext;
    }
    DeleteCourse(pH);
    return false;
}

bool ImportScoreboardView(Account* account)
{
    string classname, coursename, sem, aca;
    cout << "Classname: ";
    cin.ignore();
    getline(cin, classname);
    cout << "Coursename: ";
    getline(cin, coursename);
    cout << "Semester: ";
    getline(cin, sem);
    cout << "Academic: ";
    getline(cin, aca);

    if (!CheckExistCourse(classname, coursename, sem, aca)) {
        cout << "This course has not existed" << endl;
        return false;
    }

    if (!CheckLectureraccount(account->Username, coursename, classname, aca, sem)) {
        cout << "You do not have permission for this course" << endl;
        return false;
    }

    EnrollNode* pH = nullptr;
    if (!ImportScoreboard(pH, classname, coursename, sem, aca))
        return false;
    ScanScoreboard(pH);
    DeleteEnrollment(pH);
    return true;
}

bool EditGradeView(Account* account)
{
    Enrollment enrollment;
    GetNowAcademic(enrollment.semester, enrollment.academic);
    cout << "Classname: ";
    cin.ignore();
    getline(cin, enrollment.classname);
    cout << "Coursename: ";
    getline(cin, enrollment.coursename);

    if (!CheckLectureraccount(account->Username, enrollment.coursename, enrollment.classname, enrollment.academic, enrollment.semester)) {
        cout << "You do not have permission to edit grade of this course" << endl;
        return false;
    }

    cout << "StudentID: ";
    getline(cin, enrollment.studentID);
    cout << "Midterm: ";
    cin >> enrollment.midterm;
    cout << "Final: ";
    cin >> enrollment.final;
    cout << "Lab: ";
    cin >> enrollment.lab;
    cout << "Bonus: ";
    cin >> enrollment.bonus;
    return EditEnrollment(enrollment);
}

bool ListOfCourseOfLecturerView(Account* account)
{
    using namespace std;

    std::string semester, academic;
    GetNowAcademic(semester, academic);

    if (!CheckSemester(semester, academic)) {
        std::cout << "Not create this semester" << std::endl;
        return false;
    }

    CourseHead course;
    course.head = nullptr;
    GetCourse(course);
    CourseNode* cur = course.head;
    int count = 1;
    while (cur != nullptr) {
        if (cur->course->LecturerAccount == account->Username) {
            if (cur->course->Semester == semester && cur->course->AcademicYear == academic) {
                if (count == 1) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << "No ID    Coursename          Class  Username Fullname            "
                         << "Degree Sex    DateStart  DateEnd    Day TimeStart TimeEnd Room "
                         << "Semester "
                         << "Academic" << endl;
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                }
                cout << left << setw(3) << count;
                cout << left << setw(6) << cur->course->CourseID;
                cout << left << setw(20) << cur->course->CourseName;
                cout << left << setw(7) << cur->course->Class;
                cout << left << setw(9) << cur->course->LecturerAccount;
                cout << left << setw(20) << cur->course->lecturer.FirstName + ' ' + cur->course->lecturer.LastName;
                cout << left << setw(7) << cur->course->lecturer.Title;
                cout << left << setw(7);
                if (cur->course->lecturer.Sex == Sex::Male)
                    cout << "Male";
                else if (cur->course->lecturer.Sex == Sex::Female)
                    cout << "Female";
                else
                    cout << "Unknown";
                cout << left << setw(11) << cur->course->StartDate;
                cout << left << setw(11) << cur->course->EndDate;
                cout << left << setw(4) << cur->course->DayOfWeek;
                cout << left << setw(10) << cur->course->StartHour;
                cout << left << setw(8) << cur->course->EndHour;
                cout << left << setw(5) << cur->course->Classroom;
                cout << left << setw(9) << cur->course->Semester;
                cout << cur->course->AcademicYear << endl;
                count++;
            }
        }
        cur = cur->pNext;
    }
    return true;
}
bool CheckPermission(Account* account, std::string classname, std::string course, std::string sem, std::string aca)
{
    CourseHead Course;
    Course.head = nullptr;
    GetCourse(Course);
    CourseNode* current = Course.head;
    bool check = false;
    while (current != nullptr) {
        if (current->course->LecturerAccount == account->Username) {
            if (current->course->AcademicYear == aca && current->course->Semester == sem) {
                if (current->course->CourseID == course && current->course->Class == classname) {
                    check = true;
                    break;
                }
            }
        }
        current = current->pNext;
    }
    DeleteCourse(Course);
    return check;
}

bool EnrolmentOfACourse(Account* account)
{
    using namespace std;

    string course, semester, academic, classname;
    cout << "Academic(2019-2020,...): ";
    cin.ignore();
    getline(cin, academic);
    cout << "Semester(HK1, HK2, HK3): ";
    getline(cin, semester);
    cout << "Coursename: ";
    getline(cin, course);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckPermission(account, classname, course, semester, academic)) {
        cout << "You do not have permission for this course" << endl;
        return false;
    }

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    int i = 1;
    while (cur != nullptr) {
        if (cur->enrollment.academic == academic && cur->enrollment.semester == semester) {
            if (cur->enrollment.coursename == course && cur->enrollment.classname == classname) {
                if (i == 1) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << "No StudentID Fullname            Class  Midterm Final Lab Bonus" << endl;
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                }
                Student* student = GetStudent(stoi(cur->enrollment.studentID));
                cout << left << setw(3) << i;
                cout << left << setw(10) << cur->enrollment.studentID;
                cout << left << setw(20) << student->FirstName + ' ' + student->LastName;
                cout << left << setw(7) << student->ClassName;
                cout << left << setw(8) << (double)cur->enrollment.midterm;
                cout << left << setw(6) << (double)cur->enrollment.final;
                cout << left << setw(4) << (double)cur->enrollment.lab;
                cout << left << setw(6) << (double)cur->enrollment.bonus << endl;
                delete student;
                i++;
            }
        }
        cur = cur->pNext;
    }
    DeleteEnrollment(pH);
    return true;
}

bool LecturerView(int choice, Account* account)
{
    system("cls");
    switch (choice) {
    case 1:
        cout << "1. List of course of lecturer in this current semester" << endl;
        ListOfCourseOfLecturerView(account);
        break;
    case 2:
        cout << "2. List of students of a course" << endl;
        ListOfStudentsInCourseViewLecturer(false, account);
        break;
    case 3:
        cout << "3. View attendance of a course" << endl;
        ViewAttendanceOfACourseLecturer(account);
        break;
    case 4:
        cout << "4. Edit an attendance of a course" << endl;
        EditAttendanceView(account);
        break;
    case 5:
        cout << "5. Import scoreboard from a csv file" << endl;
        if (ImportScoreboardView(account))
            cout << "Import scoreboard successfully" << endl;
        else
            cout << "Import scoreboard failed!!" << endl;
        break;
    case 6:
        cout << "6. Edit grade of a student" << endl;
        if (EditGradeView(account))
            cout << "Edit score successfully" << endl;
        else
            cout << "Edit score failed!!" << endl;
        break;
    case 7:
        cout << "7. View a scoreboard" << endl;
        EnrolmentOfACourse(account);
        break;
    default:
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
bool ListOfStudentsInCourseViewLecturer(bool check, Account* account)
{
    using namespace std;
    string course, semester, academic, classname;
    cout << "Academic(2019-2020,...): ";
    cin.ignore();
    getline(cin, academic);
    cout << "Semester(HK1, HK2, HK3): ";
    getline(cin, semester);

    if (!CheckSemester(semester, academic)) {
        std::cout << "Not create this semester" << std::endl;
        return false;
    }

    cout << "Coursename: ";
    getline(cin, course);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckLectureraccount(account->Username, course, classname, academic, semester)) {
        cout << "You do not have permission to edit grade of this course" << endl;
        return false;
    }

    if (!CheckExistCourse(classname, course, semester, academic)) {
        cout << "This course has not existed" << endl;
        return false;
    }

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    int i = 1;
    while (cur != nullptr) {
        if (cur->enrollment.academic == academic && cur->enrollment.semester == semester) {
            if (cur->enrollment.coursename == course && cur->enrollment.classname == classname) {
                if (i == 1) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << "No " << left << setw(9) << "ID"
                         << left << setw(20) << "Fullname"
                         << left << setw(7) << "Class"
                         << left << setw(7) << "Course"
                         << left << setw(9) << "Semester"
                         << "Academic" << endl;
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                }
                Student* student = GetStudent(stoi(cur->enrollment.studentID));
                cout << left << setw(3) << i;
                cout << left << setw(9) << cur->enrollment.studentID;
                cout << left << setw(20) << student->FirstName + ' ' + student->LastName;
                cout << student->ClassName << " ";
                cout << left << setw(7) << course;
                cout << left << setw(9) << cur->enrollment.semester;
                cout << left << setw(9) << cur->enrollment.academic << endl;
                delete student;
                i++;
            }
        }
        cur = cur->pNext;
    }
    if (i == 1)
        cout << "Don't have any students participating in this course" << endl;
    DeleteEnrollment(pH);
    return true;
}
char CheckLecturerAccountNew(std::string account, std::string course, std::string classname)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);

    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->CourseID == course && cur->course->Class == classname) {
            if (cur->course->LecturerAccount == account) {
                DeleteCourse(pH);
                return true;
            }
        }
        cur = cur->pNext;
    }
    DeleteCourse(pH);
    return false;
}
bool ViewAttendanceOfACourseLecturer(Account* account)
{
    string academic, semester, coursename, classname;
    GetNowAcademic(semester, academic);
    cout << "Coursename: ";
    cin.ignore();
    getline(cin, coursename);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckExistCourse(classname, coursename, semester, academic)) {
        cout << "This course has not existed" << endl;
        return false;
    }
    if (!CheckLecturerAccountNew(account->Username, coursename, classname)) {
        cout << "You do not have permission to edit grade of this course" << endl;
        return false;
    }
    int ID = GetID(academic, semester, coursename, classname);
    AttendanceNode* pH = nullptr;
    GetAttendance(pH);
    AttendanceNode* cur = pH;
    bool check = false;
    int i = 1;
    while (cur != nullptr) {
        if (cur->attendance.courseID == ID) {
            if (!check) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                cout << "No " << left << setw(9) << "ID"
                     << left << setw(20) << "Fullname"
                     << left << setw(7) << "Class"
                     << left << setw(7) << "Course"
                     << left << setw(11) << "Date(d-m-y)"
                     << "Attendance" << endl;
                SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
            }
            check = true;
            cout << left << setw(3) << i;
            cout << left << setw(9) << cur->attendance.studentID;
            Student* student = GetStudent(cur->attendance.studentID);
            cout << left << setw(20) << student->FirstName + ' ' + student->LastName;
            cout << left << setw(7) << student->ClassName;
            cout << left << setw(7) << coursename;
            if (cur->attendance.date.Day < 10)
                cout << "0";
            cout << cur->attendance.date.Day << "-";
            if (cur->attendance.date.Month < 10)
                cout << "0";
            cout << cur->attendance.date.Month << "-";
            cout << cur->attendance.date.Year << " ";
            if (cur->attendance.status == Status::Present)
                cout << "Present" << endl;
            else
                cout << "Absent" << endl;
            delete student;
            i++;
        }
        cur = cur->pNext;
    }
    if (!check)
        cout << "There is no attendance of this course" << endl;
    ClearAttendance(pH);
    return true;
}