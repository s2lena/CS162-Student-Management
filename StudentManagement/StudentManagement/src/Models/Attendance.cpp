#define _CRT_SECURE_NO_WARNINGS

#include "Attendance.h"

void SaveAttendance(AttendanceNode* pH)
{
    using namespace std;

    ofstream ofs;
    ofs.open("data/attendance.txt");
    AttendanceNode* cur = pH;
    while (cur != nullptr) {
        ofs << cur->attendance.studentID << endl;
        ofs << cur->attendance.courseID << endl;
        ofs << cur->attendance.date.Day << endl;
        ofs << cur->attendance.date.Month << endl;
        ofs << cur->attendance.date.Year << endl;
        ofs << (int)cur->attendance.status << endl;
        cur = cur->pNext;
    }
    ofs.close();
}

void GetAttendance(AttendanceNode*& pH)
{
    using namespace std;

    AttendanceNode* cur = nullptr;
    string tmp;
    int t;
    ifstream ifs;
    ifs.open("data/attendance.txt");
    while (ifs) {
        getline(ifs, tmp);
        if (tmp == "")
            break;
        if (pH == nullptr) {
            pH = new AttendanceNode;
            pH->attendance.studentID = stoi(tmp);
            ifs >> pH->attendance.courseID;
            ifs >> pH->attendance.date.Day;
            ifs >> pH->attendance.date.Month;
            ifs >> pH->attendance.date.Year;
            ifs >> t;
            ifs.ignore();
            if (t == 0)
                pH->attendance.status = Status::Absent;
            else
                pH->attendance.status = Status::Present;
            pH->pNext = nullptr;
            cur = pH;
        } else {
            cur->pNext = new AttendanceNode;
            cur = cur->pNext;
            cur->attendance.studentID = stoi(tmp);
            ifs >> cur->attendance.courseID;
            ifs >> cur->attendance.date.Day;
            ifs >> cur->attendance.date.Month;
            ifs >> cur->attendance.date.Year;
            ifs >> t;
            ifs.ignore();
            if (t == 0)
                cur->attendance.status = Status::Absent;
            else
                cur->attendance.status = Status::Present;
            cur->pNext = nullptr;
        }
    }
    ifs.close();
}

void ClearAttendance(AttendanceNode*& pH)
{
    AttendanceNode* cur = pH;
    while (pH != nullptr) {
        pH = pH->pNext;
        delete cur;
        cur = pH;
    }
}

bool EditAttendance(int ID, int courseID, Status status)
{
    AttendanceNode* pH = nullptr;
    GetAttendance(pH);
    AttendanceNode* cur = pH;

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    bool found = false;
    while (cur != nullptr) {
        if (cur->attendance.studentID == ID && cur->attendance.courseID == courseID)
            if (cur->attendance.date.Day == curtime->tm_mday
                && cur->attendance.date.Month == (curtime->tm_mon + 1) && cur->attendance.date.Year == (curtime->tm_year + 1900)) {
                found = true;
                cur->attendance.status = status;
                SaveAttendance(pH);
                break;
            }
        cur = cur->pNext;
    }

    ClearAttendance(pH);
    return found;
}

bool CheckExistAttendance(Attendance attend)
{
    AttendanceNode* pH = nullptr;
    GetAttendance(pH);
    AttendanceNode* cur = pH;
    bool found = false;
    while (cur != nullptr) {
        if (cur->attendance.studentID == attend.studentID && cur->attendance.courseID == attend.courseID)
            if (cur->attendance.date.Day == attend.date.Day && cur->attendance.date.Month == attend.date.Month && cur->attendance.date.Year == attend.date.Year) {
                found = true;
                if (cur->attendance.status == Status::Absent) {
                    cur->attendance.status = Status::Present;
                    std::cout << "Check in successfully" << std::endl;
                    SaveAttendance(pH);
                    goto END;
                } else {
                    std::cout << "You had checked in before" << std::endl;
                    goto END;
                }
            }
        cur = cur->pNext;
    }

END:
    ClearAttendance(pH);
    return found;
}

bool CheckEnrollment(int ID, std::string classname, std::string coursename, std::string sem, std::string aca)
{
    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    while (cur != nullptr) {
        if (cur->enrollment.semester == sem && cur->enrollment.academic == aca)
            if (cur->enrollment.coursename == coursename && cur->enrollment.classname == classname)
                if (cur->enrollment.studentID == std::to_string(ID)) {
                    DeleteEnrollment(pH);
                    return true;
                }
        cur = cur->pNext;
    }
    DeleteEnrollment(pH);
    return false;
}

void GetNowAcademic(std::string& sem, std::string& aca)
{
    Node* pH = nullptr;
    LoadSemester(pH);
    Node* cur = pH;
    while (cur != nullptr) {
        if (cur->pNext == nullptr) {
            sem = cur->semester;
            aca = cur->academic;
        }
        cur = cur->pNext;
    }
    DeleteSemester(pH);
}

Course* FindCourse(struct tm* curtime, int ID, int& courseID)
{
    std::string sem, aca;
    GetNowAcademic(sem, aca);

    std::string day[7] = { "Sun", "Mon", "Tue", " Wed", "Thu", "Fri", "Sat" };
    CourseHead course;
    course.head = nullptr;
    GetCourse(course);
    CourseNode* current = course.head;
    Course* found = nullptr;
    int s_h, s_m;
    while (current != nullptr) {
        if (current->course->AcademicYear == aca && current->course->Semester == sem) {
            if (current->course->DayOfWeek == day[curtime->tm_wday]) {
                if (CheckEnrollment(ID, current->course->Class, current->course->CourseID, sem, aca)) {
                    s_h = (current->course->StartHour[0] - '0') * 10 + (current->course->StartHour[1] - '0');
                    if (curtime->tm_hour == s_h) {
                        s_m = (current->course->StartHour[3] - '0') * 10 + (current->course->StartHour[4] - '0');
                        if (curtime->tm_min >= s_m) {
                            courseID = current->ID;
                            found = current->course;
                            current->course = nullptr;
                            break;
                        }
                    } else if (curtime->tm_hour == (s_h + 1)) {
                        s_m = (current->course->StartHour[3] - '0') * 10 + (current->course->StartHour[4] - '0');
                        if (curtime->tm_min <= s_m) {
                            courseID = current->ID;
                            found = current->course;
                            current->course = nullptr;
                            break;
                        }
                    }
                }
            }
        }
        current = current->pNext;
    }
    DeleteCourse(course);
    return found;
}

void Checkin(Account* account)
{
    using namespace std;

    time_t _tm = time(NULL);

    struct tm* curtime = localtime(&_tm);
    cout << asctime(curtime) << endl;

    int courseID = 0;
    Course* found = FindCourse(curtime, account->RoleID, courseID);
    if (found == nullptr)
        cout << "No course to check in" << endl;
    else {
        int tmp = 0;
        cout << found->CourseID << " ";
        cout << found->lecturer.FirstName << " ";
        cout << found->lecturer.LastName << " ";
        cout << found->Classroom << endl;
        while (tmp != 1) {
            cout << "Present(1): ";
            cin >> tmp;
        }
        Attendance attend;
        attend.studentID = account->RoleID;
        attend.courseID = courseID;
        attend.date.Day = curtime->tm_mday;
        attend.date.Month = (curtime->tm_mon + 1);
        attend.date.Year = curtime->tm_year + 1900;
        attend.status = (Status)tmp;
        if (CheckExistAttendance(attend)) {
        } else {
            CreateAllAttend(attend, found);
            cout << "Check in successfully" << endl;
        }
        delete found;
    }
}

bool CreateAllAttend(Attendance attend, Course* course)
{
    using namespace std;

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    ofstream ofs;

    ofs.open("data/attendance.txt", ios::app);

    while (cur != nullptr) {
        if (cur->enrollment.semester == course->Semester)
            if (cur->enrollment.academic == course->AcademicYear) {
                if (cur->enrollment.coursename == course->CourseID) {
                    if (cur->enrollment.classname == course->Class) {
                        ofs << cur->enrollment.studentID << endl;
                        ofs << attend.courseID << endl;
                        ofs << attend.date.Day << endl;
                        ofs << attend.date.Month << endl;
                        ofs << attend.date.Year << endl;
                        if (cur->enrollment.studentID == to_string(attend.studentID))
                            ofs << (int)Status::Present << endl;
                        else
                            ofs << (int)Status::Absent << endl;
                    }
                }
            }
        cur = cur->pNext;
    }

    ofs.close();

    DeleteEnrollment(pH);
    return true;
}

std::string GetCourseID(int ID)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);
    std::string found;
    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->ID == ID) {
            found = cur->course->CourseID;
            break;
        }
        cur = cur->pNext;
    }
    DeleteCourse(pH);
    return found;
}

bool ExportAttendance(int ID, std::string course, std::string classname, std::string sem, std::string aca)
{
    using namespace std;

    ofstream ofs;
    string file = "C:/Users/Chopper/Documents/Test Of Project/" + classname + "-" + course + "-ATTENDANCE-" + sem + "-" + aca + ".csv";
    ofs.open(file);

    if (ofs.is_open()) {

        AttendanceNode* pH = nullptr;
        GetAttendance(pH);
        AttendanceNode* cur = pH;
        int count = 1;
        ofs << "No,StudentID,Firstname,Lastname,Date,Status" << endl;
        while (cur != nullptr) {
            if (cur->attendance.courseID = ID) {
                Student* student = GetStudent(cur->attendance.studentID);
                ofs << count << ",";
                ofs << cur->attendance.studentID << ",";
                ofs << student->FirstName << "," << student->LastName << ",";
                ofs << student->ClassName << ",";
                ofs << cur->attendance.date.Year << "-";
                ofs << cur->attendance.date.Month << "-";
                ofs << cur->attendance.date.Day << ",";
                if (cur->attendance.status == Status::Absent)
                    ofs << "Absent" << endl;
                else
                    ofs << "Present" << endl;
                count++;
                delete student;
            }
            cur = cur->pNext;
        }
        cout << "Path:\"file\"\n";
        ClearAttendance(pH);
        ofs.close();
        return true;
    } else {
        cout << "Can not open file to store!\n";
        return false;
    }
}