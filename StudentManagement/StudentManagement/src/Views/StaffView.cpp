#include "StaffView.h"
#include "Models/AcademicSemester.h"
#include "Models/Class.h"
#include "Models/Course.h"
#include "Models/Enrollment.h"
#include <Windows.h>
#include <iomanip>
#include <iostream>
#include <string>

bool ImportView()
{
    Class classes;
    classes.head = nullptr;
    classes.count = 0;
    std::string classname;
    std::cout << "Input classname(19CTT1,...): ";
    std::cin.ignore();
    std::getline(std::cin, classname);
    if (!ImportClass(classes, classname))
        return false;
    SaveProfileStudent(classes);
    CreateAllAccount(classes);
    DeleteClass(classes);
    return true;
}

bool AddStudentView()
{
    std::string str;
    Student* student = new Student;
    std::cout << "StudentID: ";
    std::cin >> student->AccountID;
    std::cout << "First Name: ";
    std::cin.ignore();
    std::getline(std::cin, student->FirstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, student->LastName);
    std::cout << "Class Name(19CTT1,...): ";
    std::getline(std::cin, student->ClassName);
    std::cout << "Sex (Male or Famale): ";
    std::getline(std::cin, str);
    if (str == "Female")
        student->Sex = Sex::Female;
    else if (str == "Male")
        student->Sex = Sex::Male;
    else
        student->Sex = Sex::Unknown;
    std::cout << "Birthday (dd mm yyyy): ";
    std::cin >> student->Birthday.Day >> student->Birthday.Month >> student->Birthday.Year;
    if (!CheckExistClass(student->ClassName)) {
        delete student;
        std::cout << "This class is not exist" << std::endl;
        return false;
    }
    AddNewStudent(student);
    delete student;
    return true;
}

bool EditStudentView()
{
    int ID;
    std::cout << "Input studentID to change: ";
    std::cin >> ID;

    if (!RemoveAStudent(ID)) {
        std::cout << "This student does not exists" << std::endl;
        return false;
    }

    std::cout << "Information to change: " << std::endl;
    std::string str;
    Student* student = new Student;
    std::cout << "StudentID: ";
    std::cin >> student->AccountID;
    std::cout << "First Name: ";
    std::cin.ignore();
    std::getline(std::cin, student->FirstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, student->LastName);
    std::cout << "Class Name(19CTT1,...): ";
    std::getline(std::cin, student->ClassName);
    std::cout << "Sex (Male or Famale): ";
    std::getline(std::cin, str);
    if (str == "Female")
        student->Sex = Sex::Female;
    else if (str == "Male")
        student->Sex = Sex::Male;
    else
        student->Sex = Sex::Unknown;
    std::cout << "Birthday (dd mm yyyy): ";
    std::cin >> student->Birthday.Day >> student->Birthday.Month >> student->Birthday.Year;

    if (!CheckExistClass(student->ClassName)) {
        delete student;
        std::cout << "This class is not exist" << std::endl;
        return false;
    }

    AddNewStudent(student);
    delete student;
    return true;
}

bool RemoveAStudentView()
{
    int ID;
    std::cout << "Input studentID: ";
    std::cin >> ID;

    return RemoveAStudent(ID);
}

bool ChangeClassView()
{
    int ID;
    std::cout << "Input studentID to change: ";
    std::cin >> ID;

    Student* student = GetStudent(ID);
    if (student == nullptr) {
        std::cout << "This student does not exist" << std::endl;
        return false;
    }
    delete student;

    std::string classname;
    std::cout << "Input classname to change: ";

    std::cin.ignore();
    std::getline(std::cin, classname);

    if (!CheckExistClass(classname)) {
        std::cout << "This class is not exist" << std::endl;
        return false;
    }
    return ChangeStudentFromClassAtoClassB(ID, classname);
}

bool ViewListOfStudents()
{
    ViewListOfClasses();
    std::string classname;
    std::cout << "Input classname to view list of students: ";
    std::cin.ignore();
    std::getline(std::cin, classname);

    return ViewListOfStudent(classname);
}

bool ViewListOfClasses()
{
    ClassNode* pH = nullptr;
    LoadListOfClasses(pH);

    ClassNode* cur = pH;
    int i = 1;
    while (pH != nullptr) {
        if (pH->classname != "") {
            std::cout << i << " ";
            std::cout << pH->classname << std::endl;
            pH = pH->pNext;
            delete cur;
            cur = pH;
            i++;
        } else {
            break;
        }
    }
    DeleteClassNode(pH);
    return true;
}

bool AcademicView()
{
    // Clear screen + HDSD
    using namespace std;

    string sem, aca, newSem, newAca;
    Node* pH = nullptr;
    int choice;
    bool status = true;
    while (status) {
        cout << "1. Create semester and academic" << endl;
        cout << "2. Update semester and academic" << endl;
        cout << "3. Delete semester and academic" << endl;
        cout << "4. View semester and academic" << endl;
        cout << "0. Out function" << endl;
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            cout << "1. Create semester and academic" << endl;
            cout << "Input semester: ";
            cin.ignore();
            getline(cin, sem);
            cout << "Input academic: ";
            getline(cin, aca);
            CreateSemester(sem, aca);
            cout << "Create semester successfully" << endl;
            break;
        case 2:
            cout << "2. Update semester and academic" << endl;
            cout << "Input semester: ";
            cin.ignore();
            getline(cin, sem);
            cout << "Input academic: ";
            getline(cin, aca);
            cout << "Input new semester: ";
            getline(cin, newSem);
            cout << "Input new academic: ";
            getline(cin, newAca);

            LoadSemester(pH);
            if (!DeleteASemeter(pH, sem, aca)) {
                cout << "Not create this semester" << endl;
                DeleteSemester(pH);
                break;
            }
            SaveSemester(pH);
            cout << "Update successfully" << endl;
            DeleteSemester(pH);
            CreateSemester(newSem, newAca);
            break;
        case 3:
            cout << "3. Delete semester and academic" << endl;
            cout << "Input semester: ";
            cin.ignore();
            getline(cin, sem);
            cout << "Input academic: ";
            getline(cin, aca);
            LoadSemester(pH);
            if (!DeleteASemeter(pH, sem, aca)) {
                cout << "Not create this semester" << endl;
                DeleteSemester(pH);
                break;
            }
            SaveSemester(pH);
            cout << "Delete successfully" << endl;
            break;
        case 4:
            cout << "4. View semester and academic" << endl;
            LoadSemester(pH);
            ShowSemester(pH);
            DeleteSemester(pH);
            break;
        case 0:
            status = false;
            break;
        default:
            break;
        }

        bool status = true;
        while (status) {
            std::cout << std::endl;
            std::cout << "0. Back to menu" << std::endl;
            std::cout << "Your answer is: ";
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
    }

    return true;
}

bool ImportCourseView()
{
    std::string semester, academic, classname;
    std::cout << "Academic(2019-2020,...): ";
    std::cin.ignore();
    std::getline(std::cin, academic);
    std::cout << "Semester(HK1,...): ";
    std::getline(std::cin, semester);
    std::cout << "Class (19CTT1,...): ";
    std::getline(std::cin, classname);

    if (!CheckSemester(semester, academic)) {
        std::cout << "Not create this semester" << std::endl;
        return false;
    }

    CourseHead course;
    course.head = nullptr;

    if (!ImportCourse(course, semester, academic, classname))
        return false;
    SaveCourse(course);
    DeleteCourse(course);
    return true;
}

bool AddCourseView()
{
    std::string tmp;
    Course* course = new Course;
    std::cout << "Input information of course: " << std::endl;
    std::cout << "Academic year(2019-2020): ";
    std::cin.ignore();
    std::getline(std::cin, course->AcademicYear);
    std::cout << "Semester(HK1, HK2, HK3): ";
    std::getline(std::cin, course->Semester);

    if (!CheckSemester(course->Semester, course->AcademicYear)) {
        std::cout << "Not create this semester" << std::endl;
        delete course;
        return false;
    }

    std::cout << "Class(19CTT1,...): ";
    std::getline(std::cin, course->Class);

    if (!CheckExistClass(course->Class)) {
        std::cout << "This class is not exist" << std::endl;
        delete course;
        return false;
    }

    std::cout << "Course ID: ";
    std::getline(std::cin, course->CourseID);
    std::cout << "Course name: ";
    std::getline(std::cin, course->CourseName);
    std::cout << "Lecturer Account: ";
    std::getline(std::cin, course->LecturerAccount);
    std::cout << "Lecturer first name: ";
    std::getline(std::cin, course->lecturer.FirstName);
    std::cout << "Lecturer last name: ";
    std::getline(std::cin, course->lecturer.LastName);
    std::cout << "Lecture tilte: ";
    std::getline(std::cin, course->lecturer.Title);
    std::cout << "Lecture gender (Male or Female): ";
    std::getline(std::cin, tmp);
    if (tmp == "Male")
        course->lecturer.Sex = Sex::Male;
    else if (tmp == "Female")
        course->lecturer.Sex = Sex::Female;
    else
        course->lecturer.Sex = Sex::Unknown;
    std::cout << "Start date (yyyy-mm-dd): ";
    std::getline(std::cin, course->StartDate);
    std::cout << "End date (yyyy-mm-dd): ";
    std::getline(std::cin, course->EndDate);
    std::cout << "Day of week(Mon, Tue, Web...): ";
    std::getline(std::cin, course->DayOfWeek);
    std::cout << "Start hour (hh:mm): ";
    std::getline(std::cin, course->StartHour);
    std::cout << "End hour (hh:mm): ";
    std::getline(std::cin, course->EndHour);
    std::cout << "Classroom: ";
    std::getline(std::cin, course->Classroom);

    if (CheckExistCourse(course->Class, course->CourseID, course->Semester, course->AcademicYear)) {
        delete course;
        std::cout << "This course has existed" << std::endl;
        return false;
    }
    AddCourse(course);
    SaveEnrollment(course->Class, course->CourseID, course->Semester, course->AcademicYear);
    if (!CheckExistLecturer(course->lecturer))
        CreateProfileLecturer(course->LecturerAccount, course->lecturer);
    delete course;
    return true;
}

bool RemoveCourseView()
{
    std::string courseID, classname, sem, aca;
    std::cout << "CourseID: ";
    std::cin.ignore();
    std::getline(std::cin, courseID);
    std::cout << "Classname(19CTT1,...): ";
    std::getline(std::cin, classname);
    std::cout << "Semester(HK1,...): ";
    std::getline(std::cin, sem);
    std::cout << "Academic year(2019-2020,...): ";
    std::getline(std::cin, aca);
    if (CheckExistCourse(classname, courseID, sem, aca)) {
        RemoveStudentOfCourse(classname, courseID, sem, aca);
        RemoveCourse(courseID, classname, sem, aca);
        return true;
    } else {
        std::cout << "This course has not exist" << std::endl;
        return false;
    }
}

bool EditCourseView()
{
    std::string courseID, classname, sem, aca, tmp;
    std::cout << "CourseID: ";
    std::cin.ignore();
    std::getline(std::cin, courseID);
    std::cout << "Classname(19CTT1,...): ";
    std::getline(std::cin, classname);
    std::cout << "Semester(HK1,...): ";
    std::getline(std::cin, sem);
    std::cout << "Academic year(2019-2020,...): ";
    std::getline(std::cin, aca);

    if (CheckExistCourse(classname, courseID, sem, aca)) {
        RemoveStudentOfCourse(classname, courseID, sem, aca);
    } else {
        std::cout << "This course has not exist" << std::endl;
        return false;
    }

    Course* course = new Course;
    std::cout << "Input information of course to edit: " << std::endl;
    std::cout << "Academic year(2019-2020,...): ";
    std::getline(std::cin, course->AcademicYear);
    std::cout << "Semester(HK1,...): ";
    std::getline(std::cin, course->Semester);
    std::cout << "Class(19CTT1,...): ";
    std::getline(std::cin, course->Class);
    std::cout << "Course ID: ";
    std::getline(std::cin, course->CourseID);
    std::cout << "Course name: ";
    std::getline(std::cin, course->CourseName);
    std::cout << "Lecturer Account: ";
    std::getline(std::cin, course->LecturerAccount);
    std::cout << "Lecturer first name: ";
    std::getline(std::cin, course->lecturer.FirstName);
    std::cout << "Lecturer last name: ";
    std::getline(std::cin, course->lecturer.LastName);
    std::cout << "Lecture tilte: ";
    std::getline(std::cin, course->lecturer.Title);
    std::cout << "Lecture gender (Male or Female): ";
    std::getline(std::cin, tmp);
    if (tmp == "Male")
        course->lecturer.Sex = Sex::Male;
    else if (tmp == "Female")
        course->lecturer.Sex = Sex::Female;
    else
        course->lecturer.Sex = Sex::Unknown;
    std::cout << "Start date (yyyy-mm-dd): ";
    std::getline(std::cin, course->StartDate);
    std::cout << "End date (yyyy-mm-dd): ";
    std::getline(std::cin, course->EndDate);
    std::cout << "Day of week: ";
    std::getline(std::cin, course->DayOfWeek);
    std::cout << "Start hour (hh:mm): ";
    std::getline(std::cin, course->StartHour);
    std::cout << "End hour (hh:mm): ";
    std::getline(std::cin, course->EndHour);
    std::cout << "Classroom: ";
    std::getline(std::cin, course->Classroom);

    while (!CheckSemester(course->Semester, course->AcademicYear)) {
        std::cout << "Not create this semester" << std::endl;
        std::cout << "Please input again: " << std::endl;
        std::cout << "Academic year(2019-2020,...): ";
        std::getline(std::cin, course->AcademicYear);
        std::cout << "Semester(HK1,...): ";
        std::getline(std::cin, course->Semester);
    }

    while (!CheckExistClass(course->Class)) {
        std::cout << "This class is not exist" << std::endl;
        std::cout << "Please input again: " << std::endl;
        std::cout << "Class(19CTT1,...): ";
        std::getline(std::cin, course->Class);
        return false;
    }

    EditCourse(course, courseID, classname);
    SaveEnrollment(course->Class, course->CourseID, course->Semester, course->AcademicYear);
    if (!CheckExistLecturer(course->lecturer))
        CreateProfileLecturer(course->LecturerAccount, course->lecturer);
    delete course;
    return true;
}

bool RemoveSpecificStudentView()
{
    std::string ID, classname, course, sem, aca;
    std::cout << "Student ID: ";
    std::cin.ignore();
    std::getline(std::cin, ID);
    Student* student = GetStudent(std::stoi(ID));
    if (student == nullptr) {
        std::cout << "This student does not exist" << std::endl;
        return false;
    }
    delete student;
    std::cout << "Classname: ";
    std::getline(std::cin, classname);
    std::cout << "Course name: ";
    std::getline(std::cin, course);
    std::cout << "Semester: ";
    std::getline(std::cin, sem);
    std::cout << "Academic year: ";
    std::getline(std::cin, aca);

    return DeleteAEnrollment(ID, classname, course, sem, aca);
}

bool AddSpecificStudentView()
{
    std::string studentID, course, sem, aca, classname;
    std::cout << "Student ID: ";
    std::cin.ignore();
    std::getline(std::cin, studentID);

    Student* student = GetStudent(std::stoi(studentID));
    if (student == nullptr) {
        std::cout << "This student does not exist" << std::endl;
        return false;
    }
    delete student;

    std::cout << "Course name: ";
    std::getline(std::cin, course);
    std::cout << "Classname: ";
    std::getline(std::cin, classname);
    std::cout << "Semester: ";
    std::getline(std::cin, sem);
    std::cout << "Academic: ";
    std::getline(std::cin, aca);

    return AddSpecificStudent(studentID, classname, course, sem, aca);
}

bool ListOfCourseView()
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
    bool status = true;
    char* fullName = new char[50];
    while (cur != nullptr) {
        if (cur->course->Semester == semester && cur->course->AcademicYear == academic) {
            if (status) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                cout << "No " << left << setw(10) << "CourseID" << left << setw(25)
                     << "CourseName" << left << setw(7) << "Class"
                     << left << setw(9) << "Account" << left << setw(20) << "Lecturer Name"
                     << left << setw(7) << "Degree" << left << setw(7) << "Sex"
                     << left << setw(11) << "DateStart" << left << setw(11) << "DateEnd"
                     << left << setw(4) << "Day" << left << setw(7) << "StartH"
                     << left << setw(7) << "EndH" << left << setw(5) << "Room"
                     << left << setw(4) << "Sem"
                     << "Academic Year" << endl;
                SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
            }
            status = false;
            cout << left << setw(3) << count;
            cout << left << setw(10) << cur->course->CourseID;
            cout << left << setw(25) << cur->course->CourseName;
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
            cout << left << setw(7) << cur->course->StartHour;
            cout << left << setw(7) << cur->course->EndHour;
            cout << left << setw(5) << cur->course->Classroom;
            cout << left << setw(4) << cur->course->Semester;
            cout << cur->course->AcademicYear << endl;
            count++;
        }
        cur = cur->pNext;
    }
    if (status)
        cout << "Dont have any course in this semester\n";
    delete[] fullName;
    return true;
}

bool ListOfStudentsInCourseView(bool check)
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
                if (i == 1 && check) {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2 | FOREGROUND_INTENSITY);
                    cout << "No " << left << setw(9) << "ID"
                         << left << setw(20) << "Fullname"
                         << left << setw(7) << "Class"
                         << left << setw(8) << "Midterm"
                         << left << setw(6) << "Final"
                         << left << setw(4) << "Lab"
                         << left << setw(6) << "Bonus\n";
                    SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
                } else if (i == 1) {
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
                if (check) {
                    cout << left << setw(8) << (double)cur->enrollment.midterm;
                    cout << left << setw(6) << (double)cur->enrollment.final;
                    cout << left << setw(4) << (double)cur->enrollment.lab;
                    cout << left << setw(6) << (double)cur->enrollment.bonus << endl;
                } else {
                    cout << left << setw(7) << course;
                    cout << left << setw(9) << cur->enrollment.semester;
                    cout << left << setw(9) << cur->enrollment.academic << endl;
                }
                delete student;
                i++;
            }
        }
        cur = cur->pNext;
    }
    DeleteEnrollment(pH);
    return true;
}

bool FeatureLecturerView()
{
    using namespace std;
    Lecturer lecturer;
    string tmp, account;
    int num = 0;
    bool status = true;
    Lecturer** lecturers = nullptr;
    while (status) {
        cout << "1. Create lecturer" << endl;
        cout << "2. Update lecturer" << endl;
        cout << "3. Delete lecturer" << endl;
        cout << "4. View lecturer" << endl;
        cout << "0. Out function" << endl;
        cout << "Your answer is: ";
        int choice;
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1:
            cout << "1. Create lecturer" << endl;
            cout << "Account: ";
            cin.ignore();
            getline(cin, account);
            cout << "First name: ";
            getline(cin, lecturer.FirstName);
            cout << "Last name: ";
            getline(cin, lecturer.LastName);
            cout << "Gender: ";
            getline(cin, tmp);
            if (tmp == "Female")
                lecturer.Sex = Sex::Female;
            else if (tmp == "Male")
                lecturer.Sex = Sex::Male;
            else
                lecturer.Sex = Sex::Unknown;
            cout << "Title: ";
            getline(cin, lecturer.Title);
            CreateProfileLecturer(account, lecturer);
            cout << "Create lecturer successfully" << endl;
            break;
        case 2:
            cout << "2. Update lecturer" << endl;
            cout << "Account: ";
            cin.ignore();
            getline(cin, account);
            cout << "First name: ";
            getline(cin, lecturer.FirstName);
            cout << "Last name: ";
            getline(cin, lecturer.LastName);
            cout << "Gender: ";
            getline(cin, tmp);
            if (tmp == "Female")
                lecturer.Sex = Sex::Female;
            else if (tmp == "Male")
                lecturer.Sex = Sex::Male;
            else
                lecturer.Sex = Sex::Unknown;
            cout << "Title: ";
            getline(cin, lecturer.Title);
            if (!CheckExistLecturer) {
                cout << "This lecturer has not existed" << endl;
                break;
            }
            DeleteLecturer(account, lecturer);
            cout << "Account: ";
            cin.ignore();
            getline(cin, account);
            cout << "First name: ";
            getline(cin, lecturer.FirstName);
            cout << "Last name: ";
            getline(cin, lecturer.LastName);
            cout << "Gender: ";
            getline(cin, tmp);
            if (tmp == "Female")
                lecturer.Sex = Sex::Female;
            else if (tmp == "Male")
                lecturer.Sex = Sex::Male;
            else
                lecturer.Sex = Sex::Unknown;
            cout << "Title: ";
            getline(cin, lecturer.Title);
            CreateProfileLecturer(account, lecturer);
            cout << "Update lecturer successfully" << endl;
            break;
        case 3:
            cout << "3. Delete lecturer" << endl;
            cout << "Account: ";
            cin.ignore();
            getline(cin, account);
            cout << "First name: ";
            getline(cin, lecturer.FirstName);
            cout << "Last name: ";
            getline(cin, lecturer.LastName);
            cout << "Gender: ";
            getline(cin, tmp);
            if (tmp == "Female")
                lecturer.Sex = Sex::Female;
            else if (tmp == "Male")
                lecturer.Sex = Sex::Male;
            else
                lecturer.Sex = Sex::Unknown;
            cout << "Title: ";
            getline(cin, lecturer.Title);
            if (DeleteLecturer(account, lecturer))
                cout << "Delete lecturer successfully" << endl;
            else
                cout << "Delete lecturer failed!" << endl;
            break;
        case 4:
            cout << "4. View lecturer" << endl;
            GetLecturers(&lecturers, &num);
            for (int i = 0; i < num; i++) {
                cout << lecturers[i]->AccountID << " ";
                cout << lecturers[i]->FirstName << " ";
                cout << lecturers[i]->LastName << " ";
                if (lecturers[i]->Sex == Sex::Female)
                    cout << "Female ";
                else if (lecturers[i]->Sex == Sex::Male)
                    cout << "Male ";
                else
                    cout << "Unknown ";
                cout << lecturers[i]->Title << endl;
            }
            ClearLecturers(lecturers, num);
            break;
        case 0:
            status = false;
            cout << "Out function successfully" << endl;
            break;
        default:
            break;
        }

        bool status = true;
        while (status) {
            std::cout << std::endl;
            std::cout << "0. Back to menu" << std::endl;
            std::cout << "Your answer is: ";
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
    }
    return true;
}

bool ExportScoreboardView()
{
    using namespace std;

    string course, semester, academic, classname;
    cout << "Academic: ";
    cin.ignore();
    getline(cin, academic);
    cout << "Semester: ";
    getline(cin, semester);
    cout << "Coursename: ";
    getline(cin, course);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckExistCourse(classname, course, semester, academic)) {
        cout << "This course has not existed" << endl;
        return false;
    }

    ExportScoreboard(classname, course, semester, academic);
    return true;
}

bool ExportAttendanceView()
{
    using namespace std;

    string course, semester, academic, classname;
    GetNowAcademic(semester, academic);
    cout << "Coursename: ";
    cin.ignore();
    getline(cin, course);
    cout << "Classname: ";
    getline(cin, classname);

    if (!CheckExistCourse(classname, course, semester, academic)) {
        cout << "This course has not existed" << endl;
        return false;
    }
    int ID = GetID(academic, semester, course, classname);
    if (ExportAttendance(ID, course, classname, semester, academic))
        return true;
    else
        return false;
}

bool StaffView(int choice)
{
    system("cls");
    switch (choice) {
    case 1:
        std::cout << "1. Import students of a class from a csv file" << std::endl;
        if (ImportView())
            std::cout << "Import successfully" << std::endl;
        else
            std::cout << "Import failed!" << std::endl;
        break;
    case 2:
        std::cout << "2. Add a new student to a class" << std::endl;
        if (!AddStudentView())
            std::cout << "Add student failed!!" << std::endl;
        else
            std::cout << "Add Student successful" << std::endl;
        break;
    case 3:
        std::cout << "3. Edit an existing student" << std::endl;
        if (!EditStudentView())
            std::cout << "Can not find student!!" << std::endl;
        else
            std::cout << "Edit student successfully" << std::endl;
        break;
    case 4:
        std::cout << "4. Remove a student" << std::endl;
        if (RemoveAStudentView())
            std::cout << "Remove student succesfully" << std::endl;
        else
            std::cout << "Remove student failed!" << std::endl;
        break;
    case 5:
        std::cout << "5. Change students from class A to class B" << std::endl;
        if (ChangeClassView())
            std::cout << "Change class successfully" << std::endl;
        else
            std::cout << "Change class failed!" << std::endl;
        break;
    case 6:
        std::cout << "6. View list of classes" << std::endl;
        ViewListOfClasses();
        break;
    case 7:
        std::cout << "7. View list of students in a class" << std::endl;
        if (!ViewListOfStudents())
            std::cout << "Invalid classname" << std::endl;
        break;
    case 8:
        std::cout << "8. Create/ update/ delete/ view academic years and semesters" << std::endl;
        AcademicView();
        break;
    case 9:
        std::cout << "9. Import courses from a csv file" << std::endl;
        if (ImportCourseView())
            std::cout << "Import course successfully" << std::endl;
        else
            std::cout << "Import course failed!" << std::endl;
        break;
    case 10:
        std::cout << "10. Add a new course" << std::endl;
        if (!AddCourseView())
            std::cout << "Add a course failed!!" << std::endl;
        else
            std::cout << "Add a course successfully" << std::endl;
        break;
    case 11:
        std::cout << "11. Remove a course" << std::endl;
        if (RemoveCourseView())
            std::cout << "Remove course successfully" << std::endl;
        else
            std::cout << "Remove course failed!!" << std::endl;
        break;
    case 12:
        std::cout << "12. Edit an existing course" << std::endl;
        if (!EditCourseView())
            std::cout << "Can not find course" << std::endl;
        else
            std::cout << "Edit Course successfully" << std::endl;
        break;
    case 13:
        std::cout << "13. Remove a specific student from a course" << std::endl;
        if (!RemoveSpecificStudentView())
            std::cout << "Remove specific student failed!!" << std::endl;
        else
            std::cout << "Remove specific student successfully" << std::endl;
        break;
    case 14:
        std::cout << "14. Add a specific student to a course" << std::endl;
        if (!AddSpecificStudentView())
            std::cout << "Add specific student failed!!" << std::endl;
        else
            std::cout << "Add specific student successfully" << std::endl;
        break;
    case 15:
        std::cout << "15. View list of courses in the current semester" << std::endl;
        ListOfCourseView();
        break;
    case 16:
        std::cout << "16. View list of students of a course" << std::endl;
        ListOfStudentsInCourseView(false);
        break;
    case 17:
        std::cout << "17. View attendance list of a course" << std::endl;
        ViewAttendanceOfACourse();
        break;
    case 18:
        std::cout << "18. Create/ update/ delete/ view all lecturers" << std::endl;
        FeatureLecturerView();
        break;
    case 19:
        std::cout << "19. Search and view the scoreboard of a course" << std::endl;
        ListOfStudentsInCourseView(true);
        break;
    case 20:
        std::cout << "20. Export a scoreboard to a csv file" << std::endl;
        if (ExportScoreboardView())
            std::cout << "Export successfully" << std::endl;
        else
            std::cout << "Export failed!!" << std::endl;
        break;
    case 21:
        std::cout << "21. Search and view attendance list of a course" << std::endl;
        ViewAttendanceOfACourse();
        break;
    case 22:
        std::cout << "22. Export a attendance list to a csv file" << std::endl;
        if (ExportAttendanceView())
            std::cout << "Export successfully" << std::endl;
        else
            std::cout << "Export failed!!" << std::endl;
        break;
    default:
        std::cout << "Not update" << std::endl;
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