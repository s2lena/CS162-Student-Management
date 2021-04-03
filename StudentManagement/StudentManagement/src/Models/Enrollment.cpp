#include "Enrollment.h"
#include "Course.h"
#include <fstream>
#include <iostream>

void SaveEnrollment(std::string classname, std::string coursename, std::string semester, std::string academic)
{
    int numStudents = 0;
    Student** students = nullptr;
    GetStudents(&students, &numStudents);

    std::ofstream ofs;
    ofs.open("data/enrollment.txt", std::ios::app);
    for (int i = 0; i < numStudents; i++) {
        if (classname == students[i]->ClassName) {
            ofs << students[i]->AccountID << std::endl;
            ofs << classname << std::endl;
            ofs << coursename << std::endl;
            ofs << semester << std::endl;
            ofs << academic << std::endl;
            ofs << '0' << std::endl;
            ofs << '0' << std::endl;
            ofs << '0' << std::endl;
            ofs << '0' << std::endl;
        }
    }
    ofs.close();
    ClearStudents(students, numStudents);
}

void GetEnrollment(EnrollNode*& pH)
{
    EnrollNode* cur = nullptr;
    std::ifstream ifs;
    std::string tmp;
    ifs.open("data/enrollment.txt");
    while (ifs) {
        std::getline(ifs, tmp);
        if (tmp == "")
            break;
        if (pH == nullptr) {
            pH = new EnrollNode;
            pH->enrollment.studentID = tmp;
            std::getline(ifs, pH->enrollment.classname);
            std::getline(ifs, pH->enrollment.coursename);
            std::getline(ifs, pH->enrollment.semester);
            std::getline(ifs, pH->enrollment.academic);
            ifs >> pH->enrollment.midterm;
            ifs >> pH->enrollment.final;
            ifs >> pH->enrollment.lab;
            ifs >> pH->enrollment.bonus;
            ifs.ignore();
            pH->pNext = nullptr;
            cur = pH;
        } else {
            cur->pNext = new EnrollNode;
            cur = cur->pNext;
            cur->enrollment.studentID = tmp;
            std::getline(ifs, cur->enrollment.classname);
            std::getline(ifs, cur->enrollment.coursename);
            std::getline(ifs, cur->enrollment.semester);
            std::getline(ifs, cur->enrollment.academic);
            ifs >> cur->enrollment.midterm;
            ifs >> cur->enrollment.final;
            ifs >> cur->enrollment.lab;
            ifs >> cur->enrollment.bonus;
            ifs.ignore();
            cur->pNext = nullptr;
        }
    }
    ifs.close();
}

void SaveAllEnrollment(EnrollNode* pH)
{
    using namespace std;

    EnrollNode* cur = pH;
    ofstream ofs;
    ofs.open("data/enrollment.txt");
    while (cur != nullptr) {
        ofs << cur->enrollment.studentID << endl;
        ofs << cur->enrollment.classname << endl;
        ofs << cur->enrollment.coursename << endl;
        ofs << cur->enrollment.semester << endl;
        ofs << cur->enrollment.academic << endl;
        ofs << cur->enrollment.midterm << endl;
        ofs << cur->enrollment.final << endl;
        ofs << cur->enrollment.lab << endl;
        ofs << cur->enrollment.bonus << endl;
        cur = cur->pNext;
    }
    ofs.close();
}

bool DeleteAEnrollment(std::string ID, std::string classname, std::string course, std::string sem, std::string aca)
{
    if (!CheckExistCourse(classname, course, sem, aca))
        return false;

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);

    if (pH == nullptr)
        return false;

    if (pH->enrollment.studentID == ID && pH->enrollment.coursename == course) {
        if (pH->enrollment.semester == sem && pH->enrollment.academic == aca) {
            EnrollNode* tmp = pH;
            pH = pH->pNext;
            delete tmp;
            SaveAllEnrollment(pH);
            DeleteEnrollment(pH);
            return true;
        }
    } else {
        EnrollNode* cur = pH;
        while (cur->pNext != nullptr) {
            if (cur->pNext->enrollment.studentID == ID && cur->pNext->enrollment.coursename == course)
                if (cur->pNext->enrollment.semester == sem && cur->pNext->enrollment.academic == aca)
                    break;
            cur = cur->pNext;
        }

        if (cur->pNext == nullptr) {
            DeleteEnrollment(pH);
            return false;
        }

        EnrollNode* tmp = cur->pNext;
        cur->pNext = tmp->pNext;
        delete tmp;
        SaveAllEnrollment(pH);
        DeleteEnrollment(pH);
        return true;
    }
}

bool CheckExistCourse(std::string classname, std::string course, std::string sem, std::string aca)
{
    CourseHead pH;
    pH.head = nullptr;
    GetCourse(pH);

    CourseNode* cur = pH.head;
    while (cur != nullptr) {
        if (cur->course->CourseID == course && cur->course->Class == classname && cur->course->Semester == sem && cur->course->AcademicYear == aca) {
            DeleteCourse(pH);
            return true;
        }
        cur = cur->pNext;
    }
    DeleteCourse(pH);
    return false;
}

bool AddSpecificStudent(std::string ID, std::string classname, std::string course, std::string sem, std::string aca)
{
    if (!CheckExistCourse(classname, course, sem, aca))
        return false;

    int numStudents = 0;
    Student** students = nullptr;
    GetStudents(&students, &numStudents);
    bool check = false;
    int i = 0;
    for (; i < numStudents; i++) {
        if (students[i]->AccountID == std::stoi(ID)) {
            check = true;
            break;
        }
    }
    if (!check) {
        ClearStudents(students, numStudents);
        return false;
    }
    ClearStudents(students, numStudents);

    std::ofstream ofs;
    ofs.open("data/enrollment.txt", std::ios::app);
    ofs << ID << std::endl;
    ofs << classname << std::endl;
    ofs << course << std::endl;
    ofs << sem << std::endl;
    ofs << aca << std::endl;
    ofs << '0' << std::endl;
    ofs << '0' << std::endl;
    ofs << '0' << std::endl;
    ofs << '0' << std::endl;
    ofs.close();

    return true;
}

bool RemoveStudentOfCourse(std::string classname, std::string course, std::string sem, std::string aca)
{
    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    int ID = 0;
    EnrollNode* cur = pH;
    while (cur != nullptr) {
        if (cur->enrollment.coursename == course && cur->enrollment.classname == classname)
            if (cur->enrollment.academic == aca && cur->enrollment.semester == sem) {
                DeleteAEnrollment(cur->enrollment.studentID, classname, course, sem, aca);
            }
        cur = cur->pNext;
    }
    DeleteEnrollment(pH);
    return true;
}

void DeleteEnrollment(EnrollNode*& pH)
{
    EnrollNode* cur = pH;
    while (pH != nullptr) {
        pH = pH->pNext;
        delete cur;
        cur = pH;
    }
}

bool ExportScoreboard(std::string classname, std::string course, std::string sem, std::string aca)
{
    using namespace std;

    ofstream ofs;
    string file = "C:/Users/Chopper/Documents/Test Of Project/" + classname + "-" + course + "-SCOREBOARD-" + sem + "-" + aca + ".csv";
    ofs.open(file);

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    int count = 1;
    ofs << "No,StudentID,Firstname,Lastname,Classname,Midterm,Final,Lab,Bonus" << endl;
    while (cur != nullptr) {
        if (cur->enrollment.classname == classname && cur->enrollment.coursename == course)
            if (cur->enrollment.semester == sem && cur->enrollment.academic == aca) {
                Student* student = GetStudent(stoi(cur->enrollment.studentID));
                ofs << count << ",";
                ofs << cur->enrollment.studentID << ",";
                ofs << student->FirstName << ",";
                ofs << student->LastName << ",";
                ofs << student->ClassName << ",";
                ofs << cur->enrollment.midterm << ",";
                ofs << cur->enrollment.final << ",";
                ofs << cur->enrollment.lab << ",";
                ofs << cur->enrollment.bonus << endl;
                count++;
                delete student;
            }
        cur = cur->pNext;
    }

    DeleteEnrollment(pH);
    ofs.close();
    return true;
}

bool EditEnrollment(Enrollment enrollment)
{
    using namespace std;

    EnrollNode* pH = nullptr;
    GetEnrollment(pH);
    EnrollNode* cur = pH;
    bool check = false;
    while (cur != nullptr) {
        if (cur->enrollment.studentID == enrollment.studentID)
            if (cur->enrollment.classname == enrollment.classname && cur->enrollment.coursename == enrollment.coursename)
                if (cur->enrollment.semester == enrollment.semester && cur->enrollment.academic == enrollment.academic) {
                    cur->enrollment.midterm = enrollment.midterm;
                    cur->enrollment.final = enrollment.final;
                    cur->enrollment.lab = enrollment.lab;
                    cur->enrollment.bonus = enrollment.bonus;
                    check = true;
                    break;
                }
        cur = cur->pNext;
    }
    SaveAllEnrollment(pH);
    DeleteEnrollment(pH);

    return check;
}

std::string ChooseFile(std::string className, std::string coursename, std::string sem, std::string aca)
{
    std::string file = "C:/Users/Chopper/Documents/Test Of Project/";
    file = file + coursename + "-" + className + "-" + sem + "-" + aca + ".csv";
    return file;
}

short DetectEnroll(std::string str, short t)
{
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',' && i > t)
            return i;
    }
    return str.length();
}

void SeperateLineEnroll(EnrollNode*& current, std::string line)
{
    using namespace std;
    string tmp;
    int prev;
    int cur = 0;
    int status = 1;
    while (status <= 6) {
        double t = 10;
        prev = cur + 1;
        if (cur == 0)
            prev--;
        cur = DetectEnroll(line, cur);
        switch (status) {
        case 1:
            break;
        case 2:
            for (int i = prev; i < cur; i++)
                current->enrollment.studentID.push_back(line[i]);
            break;
        case 3:
            current->enrollment.midterm = 0;
            for (int i = prev; i < cur; i++) {
                if (line[i] == '.')
                    t = t * 0.1;
                else {
                    current->enrollment.midterm = current->enrollment.midterm * 10 + (line[i] - '0');
                    if (t != 10)
                        t = t * 0.1;
                    if (i + 1 == cur && t != 10)
                        current->enrollment.midterm = current->enrollment.midterm * t;
                }
            }
            break;
        case 4:
            current->enrollment.final = 0;
            for (int i = prev; i < cur; i++) {
                if (line[i] == '.')
                    t = t * 0.1;
                else {
                    current->enrollment.final = current->enrollment.final * 10 + (line[i] - '0');
                    if (t != 10)
                        t = t * 0.1;
                    if (i + 1 == cur && t != 10)
                        current->enrollment.final = current->enrollment.final * t;
                }
            }
            break;
        case 5:
            current->enrollment.lab = 0;
            for (int i = prev; i < cur; i++) {
                if (line[i] == '.')
                    t = t * 0.1;
                else {
                    current->enrollment.lab = current->enrollment.lab * 10 + (line[i] - '0');
                    if (t != 10)
                        t = t * 0.1;
                    if (i + 1 == cur && t != 10)
                        current->enrollment.lab = current->enrollment.lab * t;
                }
            }
            break;
        case 6:
            current->enrollment.bonus = 0;
            for (int i = prev; i < cur; i++) {
                if (line[i] == '.')
                    t = t * 0.1;
                else {
                    current->enrollment.bonus = current->enrollment.bonus * 10 + (line[i] - '0');
                    if (t != 10)
                        t = t * 0.1;
                    if (i + 1 == cur && t != 10)
                        current->enrollment.bonus = current->enrollment.bonus * t;
                }
            }
            break;
        default:
            break;
        }
        status++;
    }
}

bool ImportScoreboard(EnrollNode*& pH, std::string className, std::string coursename, std::string sem, std::string aca)
{
    using namespace std;

    EnrollNode* cur = nullptr;
    string str;
    ifstream ifs;
    string file = ChooseFile(className, coursename, sem, aca);
    ifs.open(file);

    if (ifs.is_open()) {
        std::getline(ifs, str);
        str.erase(str.begin(), str.end());
        while (!ifs.eof() && ifs) {
            getline(ifs, str);
            if (str == "")
                break;

            if (pH == nullptr) {
                pH = new EnrollNode;
                SeperateLineEnroll(pH, str);
                pH->enrollment.classname = className;
                pH->enrollment.coursename = coursename;
                pH->enrollment.semester = sem;
                pH->enrollment.academic = aca;
                pH->pNext = nullptr;
                cur = pH;
            } else {
                cur->pNext = new EnrollNode;
                cur = cur->pNext;
                SeperateLineEnroll(cur, str);
                cur->enrollment.classname = className;
                cur->enrollment.coursename = coursename;
                cur->enrollment.semester = sem;
                cur->enrollment.academic = aca;
                cur->pNext = nullptr;
            }

            str.erase(str.begin(), str.end());
        }
        ifs.close();
        return true;
    } else {
        ifs.close();
        return false;
    }
    return true;
}

bool ScanScoreboard(EnrollNode* pH)
{
    EnrollNode* pHead = nullptr;
    GetEnrollment(pHead);
    EnrollNode* tmp = pH;
    EnrollNode* cur = pHead;
    while (tmp != nullptr) {
        while (cur != nullptr) {
            if (cur->enrollment.academic == tmp->enrollment.academic)
                if (cur->enrollment.semester == tmp->enrollment.semester)
                    if (cur->enrollment.coursename == tmp->enrollment.coursename)
                        if (cur->enrollment.studentID == tmp->enrollment.studentID) {
                            cur->enrollment.midterm = tmp->enrollment.midterm;
                            cur->enrollment.final = tmp->enrollment.final;
                            cur->enrollment.lab = tmp->enrollment.lab;
                            cur->enrollment.bonus = tmp->enrollment.bonus;
                            cur = pHead;
                            break;
                        }
            cur = cur->pNext;
        }
        tmp = tmp->pNext;
    }
    SaveAllEnrollment(pHead);
    DeleteEnrollment(pHead);
    return true;
}