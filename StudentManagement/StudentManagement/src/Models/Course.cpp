#include "Course.h"
#include "Models/Enrollment.h"
#include <fstream>
#include <iostream>

std::string ChooseFile(std::string semester, std::string academic, std::string classname)
{
    std::string file = "C:/Users/Chopper/Documents/Test Of Project/";
    file = file + classname + "-" + semester + "-" + academic + ".csv";
    return file;
}

short DetectCourse(std::string str, short t)
{
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',' && i > t)
            return i;
    }
    return str.length();
}

void SeperateLine(CourseNode*& current, std::string line)
{
    using namespace std;
    string tmp;
    int prev;
    int cur = 0;
    int status = 1;
    current->course = new Course;
    while (status <= 15) {
        prev = cur + 1;
        if (cur == 0)
            prev--;
        cur = DetectCourse(line, cur);
        switch (status) {
        case 1:
            current->ID = 0;
            for (int i = prev; i < cur; i++)
                current->ID = current->ID * 10 + (line[i] - '0');
            break;
        case 2:
            for (int i = prev; i < cur; i++)
                current->course->CourseID.push_back(line[i]);
            break;
        case 3:
            for (int i = prev; i < cur; i++)
                current->course->CourseName.push_back(line[i]);
            break;
        case 4:
            for (int i = prev; i < cur; i++)
                current->course->Class.push_back(line[i]);
            break;
        case 5:
            for (int i = prev; i < cur; i++)
                current->course->LecturerAccount.push_back(line[i]);
            break;
        case 6:
            for (int i = prev; i < cur; i++)
                current->course->lecturer.FirstName.push_back(line[i]);
            break;
        case 7:
            for (int i = prev; i < cur; i++)
                current->course->lecturer.LastName.push_back(line[i]);
            break;
        case 8:
            for (int i = prev; i < cur; i++)
                current->course->lecturer.Title.push_back(line[i]);
            break;
        case 9:
            for (int i = prev; i < cur; i++)
                tmp.push_back(line[i]);
            if (tmp == "Male")
                current->course->lecturer.Sex = Sex::Male;
            else if (tmp == "Female")
                current->course->lecturer.Sex = Sex::Female;
            else
                current->course->lecturer.Sex = Sex::Unknown;
            break;
        case 10:
            for (int i = prev; i < cur; i++)
                current->course->StartDate.push_back(line[i]);
            break;
        case 11:
            for (int i = prev; i < cur; i++)
                current->course->EndDate.push_back(line[i]);
            break;
        case 12:
            for (int i = prev; i < cur; i++)
                current->course->DayOfWeek.push_back(line[i]);
            break;
        case 13:
            for (int i = prev; i < cur; i++)
                current->course->StartHour.push_back(line[i]);
            break;
        case 14:
            for (int i = prev; i < cur; i++)
                current->course->EndHour.push_back(line[i]);
            break;
        case 15:
            for (int i = prev; i < cur; i++)
                current->course->Classroom.push_back(line[i]);
            break;
        default:
            break;
        }
        status++;
    }
}

bool ImportCourse(CourseHead& course, std::string semester, std::string academic, std::string classname)
{

    using namespace std;

    CourseNode* cur = nullptr;
    string str;
    ifstream ifs;
    string file = ChooseFile(semester, academic, classname);
    cout << "The path of file: \"" << file << "\"\n"; //
    ifs.open(file);
    if (ifs.is_open()) {
        std::getline(ifs, str);
        str.erase(str.begin(), str.end());
        while (!ifs.eof() && ifs) {
            getline(ifs, str);
            if (str == "")
                break;

            if (course.head == nullptr) {
                course.head = new CourseNode;
                SeperateLine(course.head, str);
                course.head->course->Semester = semester;
                course.head->course->AcademicYear = academic;
                course.head->pNext = nullptr;
                cur = course.head;
            } else {
                cur->pNext = new CourseNode;
                cur = cur->pNext;
                SeperateLine(cur, str);
                cur->course->Semester = semester;
                cur->course->AcademicYear = academic;
                cur->pNext = nullptr;
            }

            SaveEnrollment(cur->course->Class, cur->course->CourseID, semester, academic);
            CreateProfileLecturer(cur->course->LecturerAccount, cur->course->lecturer);
            str.erase(str.begin(), str.end());
        }
        ifs.close();
        return true;
    } else {
        ifs.close();
        return false;
    }
}

bool SaveCourse(CourseHead course)
{
    std::ofstream ofs;
    ofs.open("data/course.txt", std::ios::app);
    CourseNode* cur = course.head;
    while (cur != nullptr) {
        ofs << cur->course->CourseID << std::endl;
        ofs << cur->course->CourseName << std::endl;
        ofs << cur->course->Class << std::endl;
        ofs << cur->course->LecturerAccount << std::endl;
        ofs << cur->course->lecturer.FirstName << std::endl;
        ofs << cur->course->lecturer.LastName << std::endl;
        ofs << cur->course->lecturer.Title << std::endl;
        ofs << (int)cur->course->lecturer.Sex << std::endl;
        ofs << cur->course->StartDate << std::endl;
        ofs << cur->course->EndDate << std::endl;
        ofs << cur->course->DayOfWeek << std::endl;
        ofs << cur->course->StartHour << std::endl;
        ofs << cur->course->EndHour << std::endl;
        ofs << cur->course->Classroom << std::endl;
        ofs << cur->course->Semester << std::endl;
        ofs << cur->course->AcademicYear << std::endl;
        cur = cur->pNext;
    }
    ofs.close();
    return true;
}

bool SaveAllCourse(CourseHead course)
{
    std::ofstream ofs;
    ofs.open("data/course.txt");
    CourseNode* cur = course.head;
    while (cur != nullptr) {
        ofs << cur->course->CourseID << std::endl;
        ofs << cur->course->CourseName << std::endl;
        ofs << cur->course->Class << std::endl;
        ofs << cur->course->LecturerAccount << std::endl;
        ofs << cur->course->lecturer.FirstName << std::endl;
        ofs << cur->course->lecturer.LastName << std::endl;
        ofs << cur->course->lecturer.Title << std::endl;
        ofs << (int)cur->course->lecturer.Sex << std::endl;
        ofs << cur->course->StartDate << std::endl;
        ofs << cur->course->EndDate << std::endl;
        ofs << cur->course->DayOfWeek << std::endl;
        ofs << cur->course->StartHour << std::endl;
        ofs << cur->course->EndHour << std::endl;
        ofs << cur->course->Classroom << std::endl;
        ofs << cur->course->Semester << std::endl;
        ofs << cur->course->AcademicYear << std::endl;
        cur = cur->pNext;
    }
    ofs.close();
    return true;
}

bool GetCourse(CourseHead& course)
{
    using namespace std;
    string tmp;
    CourseNode* cur = nullptr;
    ifstream ifs;
    ifs.open("data/course.txt");
    while (ifs) {
        getline(ifs, tmp);
        if (tmp == "")
            break;
        if (course.head == nullptr) {
            course.head = new CourseNode;
            course.head->ID = 1;
            course.head->course = new Course;
            course.head->course->CourseID = tmp;
            getline(ifs, course.head->course->CourseName);
            getline(ifs, course.head->course->Class);
            getline(ifs, course.head->course->LecturerAccount);
            getline(ifs, course.head->course->lecturer.FirstName);
            getline(ifs, course.head->course->lecturer.LastName);
            getline(ifs, course.head->course->lecturer.Title);
            getline(ifs, tmp);
            if (tmp == "0")
                course.head->course->lecturer.Sex = Sex::Male;
            else if (tmp == "1")
                course.head->course->lecturer.Sex = Sex::Female;
            else
                course.head->course->lecturer.Sex = Sex::Unknown;
            getline(ifs, course.head->course->StartDate);
            getline(ifs, course.head->course->EndDate);
            getline(ifs, course.head->course->DayOfWeek);
            getline(ifs, course.head->course->StartHour);
            getline(ifs, course.head->course->EndHour);
            getline(ifs, course.head->course->Classroom);
            getline(ifs, course.head->course->Semester);
            getline(ifs, course.head->course->AcademicYear);
            course.head->pNext = nullptr;
            cur = course.head;
        } else {
            cur->pNext = new CourseNode;
            cur->pNext->ID = cur->ID + 1;
            cur = cur->pNext;
            cur->course = new Course;
            cur->course->CourseID = tmp;
            getline(ifs, cur->course->CourseName);
            getline(ifs, cur->course->Class);
            getline(ifs, cur->course->LecturerAccount);
            getline(ifs, cur->course->lecturer.FirstName);
            getline(ifs, cur->course->lecturer.LastName);
            getline(ifs, cur->course->lecturer.Title);
            getline(ifs, tmp);
            if (tmp == "0")
                cur->course->lecturer.Sex = Sex::Male;
            else if (tmp == "1")
                cur->course->lecturer.Sex = Sex::Female;
            else
                cur->course->lecturer.Sex = Sex::Unknown;
            getline(ifs, cur->course->StartDate);
            getline(ifs, cur->course->EndDate);
            getline(ifs, cur->course->DayOfWeek);
            getline(ifs, cur->course->StartHour);
            getline(ifs, cur->course->EndHour);
            getline(ifs, cur->course->Classroom);
            getline(ifs, cur->course->Semester);
            getline(ifs, cur->course->AcademicYear);
            cur->pNext = nullptr;
        }
    }
    ifs.close();

    return true;
}

bool AddCourse(Course* course)
{
    std::ofstream ofs;
    ofs.open("data/course.txt", std::ios::app);
    ofs << course->CourseID << std::endl;
    ofs << course->CourseName << std::endl;
    ofs << course->Class << std::endl;
    ofs << course->LecturerAccount << std::endl;
    ofs << course->lecturer.FirstName << std::endl;
    ofs << course->lecturer.LastName << std::endl;
    ofs << course->lecturer.Title << std::endl;
    ofs << (int)course->lecturer.Sex << std::endl;
    ofs << course->StartDate << std::endl;
    ofs << course->EndDate << std::endl;
    ofs << course->DayOfWeek << std::endl;
    ofs << course->StartHour << std::endl;
    ofs << course->EndHour << std::endl;
    ofs << course->Classroom << std::endl;
    ofs << course->Semester << std::endl;
    ofs << course->AcademicYear << std::endl;
    ofs.close();
    return true;
}

bool RemoveCourse(std::string courseID, std::string classname, std::string sem, std::string aca)
{
    CourseHead course;
    course.head = nullptr;
    GetCourse(course);

    if (course.head == nullptr)
        return false;

    CourseNode* tmp;
    if (course.head->course->CourseID == courseID && course.head->course->Class == classname && course.head->course->Semester == sem && course.head->course->AcademicYear == aca) {
        tmp = course.head;
        course.head = course.head->pNext;
        delete tmp;
    } else {
        CourseNode* cur = course.head;
        while (cur->pNext != nullptr) {
            if (cur->pNext->course->CourseID == courseID && cur->course->Class == classname && cur->pNext->course->Semester == sem && course.head->course->AcademicYear == aca)
                break;
            cur = cur->pNext;
        }

        if (cur->pNext == nullptr) {
            DeleteCourse(course);
            return false;
        }

        tmp = cur->pNext;
        cur->pNext = tmp->pNext;
        delete tmp;
    }
    SaveAllCourse(course);
    return true;
}

void DeleteCourse(CourseHead& course)
{
    CourseNode* cur = course.head;
    while (course.head != nullptr) {
        course.head = course.head->pNext;
        if (cur->course != nullptr)
            delete cur->course;
        delete cur;
        cur = course.head;
    }
}

bool EditCourse(Course* course, std::string courseID, std::string classname)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);
    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->AcademicYear == course->AcademicYear && cur->course->Semester == course->Semester)
            if (cur->course->CourseID == courseID && cur->course->Class == classname) {
                Course* tmp = cur->course;
                cur->course = course;
                delete tmp;
                break;
            }
        cur = cur->pNext;
    }
    SaveAllCourse(pH);
    cur->course = nullptr;
    DeleteCourse(pH);
    return true;
}