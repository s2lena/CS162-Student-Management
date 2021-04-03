#include "Class.h"
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

std::string ChooseClass(std::string className)
{
    std::for_each(className.begin(), className.end(), [](char& c) {
        c = ::toupper(c);
    });
    std::string file = "C:/Users/Chopper/Documents/Test Of Project/";
    file = file + className + ".csv";
    return file;
}

short Detect(std::string str, short t)
{
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',' && i > t)
            return i;
    }
    return str.length();
}

void SeperateLine(StudentNode*& current, std::string str)
{
    using namespace std;
    string tmp;
    int prev;
    int cur = 0;
    int status = 1;
    current->student = new Student;
    while (status <= 6) {
        prev = cur + 1;
        if (cur == 0)
            prev--;
        cur = Detect(str, cur);
        switch (status) {
        case 1:
            current->no = 0;
            for (int i = prev; i < cur; i++)
                current->no = current->no * 10 + (str[i] - '0');
            break;
        case 2:
            current->student->AccountID = 0;
            for (int i = prev; i < cur; i++)
                current->student->AccountID = current->student->AccountID * 10 + (str[i] - '0');
            break;
        case 3:
            for (int i = prev; i < cur; i++)
                current->student->FirstName.push_back(str[i]);
            break;
        case 4:
            for (int i = prev; i < cur; i++)
                current->student->LastName.push_back(str[i]);
            break;
        case 5:
            for (int i = prev; i < cur; i++) {
                tmp.push_back(str[i]);
            }
            if (tmp.compare("Female") == 0)
                current->student->Sex = Sex::Female;
            else if (tmp.compare("Male") == 0)
                current->student->Sex = Sex::Male;
            else
                current->student->Sex = Sex::Unknown;
            break;
        case 6:
            current->student->Birthday.Year = 0;
            for (int i = prev; i < prev + 4; i++)
                current->student->Birthday.Year = current->student->Birthday.Year * 10 + (str[i] - '0');
            current->student->Birthday.Month = 0;
            for (int i = prev + 5; i < prev + 7; i++)
                current->student->Birthday.Month = current->student->Birthday.Month * 10 + (str[i] - '0');
            current->student->Birthday.Day = 0;
            for (int i = prev + 8; i < cur; i++)
                current->student->Birthday.Day = current->student->Birthday.Day * 10 + (str[i] - '0');
            break;
        default:
            break;
        }
        status++;
    }
}

bool ImportClass(Class& classes, std::string className)
{
    using namespace std;

    StudentNode* cur = nullptr;
    string str;
    ifstream ifs;
    string file = ChooseClass(className);
    ifs.open(file);

    if (ifs.is_open()) {
        std::ofstream ofs;
        ofs.open("data/class.txt", std::fstream::app);
        ofs << className << std::endl;
        ofs.close();

        std::getline(ifs, str);
        str.erase(str.begin(), str.end());
        
        while (!ifs.eof() && ifs) {
        
            getline(ifs, str);
            if (str == "")
                break;

            if (classes.head == nullptr) {
                classes.head = new StudentNode;
                SeperateLine(classes.head, str);
                classes.head->student->ClassName = className;
                classes.count++;
                classes.head->pNext = nullptr;
                cur = classes.head;
            } else {
                cur->pNext = new StudentNode;
                cur = cur->pNext;
                SeperateLine(cur, str);
                cur->student->ClassName = className;
                classes.count++;
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
}

void AddNewStudent(Student* student)
{
    Class classes;
    classes.head = new StudentNode;
    classes.head->student = new Student;
    classes.head->no = 1;
    classes.head->pNext = nullptr;
    classes.head->student->AccountID = student->AccountID;
    classes.head->student->FirstName = student->FirstName;
    classes.head->student->LastName = student->LastName;
    classes.head->student->ClassName = student->ClassName;
    classes.head->student->Sex = student->Sex;
    classes.head->student->Birthday.Day = student->Birthday.Day;
    classes.head->student->Birthday.Month = student->Birthday.Month;
    classes.head->student->Birthday.Year = student->Birthday.Year;
    classes.count = 1;
    student = nullptr;
    SaveProfileStudent(classes);
    CreateAllAccount(classes);
    DeleteClass(classes);
}

bool RemoveAStudent(int studentID)
{
    bool check = false;
    int num = 0;
    Student** student = nullptr;
    GetStudents(&student, &num);

    for (int i = 0; i < num; i++) {
        if (student[i]->AccountID == studentID) {
            Student* tmp = student[i];
            delete tmp;
            student[i] = nullptr;
            check = true;
            break;
        }
    }

    if (check == true)
        SaveStudents(student, num, true);
    ClearStudents(student, num);
    if (!check)
        return false;

    int numAcc = 0;
    Account** account = nullptr;

    GetAccounts(&account, &numAcc);

    for (int i = 0; i < numAcc; i++) {
        if (account[i]->Username == std::to_string(studentID)) {
            Account* tmp = account[i];
            account[i] = nullptr;
            delete tmp;
            check = false;
            break;
        }
    }
    if (check == false)
        SaveAccounts(account, numAcc, true);
    ClearAccounts(account, numAcc);

    return true;
}

bool ChangeStudentFromClassAtoClassB(int studentID, std::string classname)
{
    bool check = true;
    int num = 0;
    Student** student = nullptr;

    GetStudents(&student, &num);

    for (int i = 0; i < num; i++) {
        if (student[i]->AccountID == studentID) {
            student[i]->ClassName = classname;
            check = false;
            break;
        }
    }
    SaveStudents(student, num, false);
    ClearStudents(student, num);

    if (check)
        return false;
}

bool CreateAccount(StudentNode* cur, Account** account, int begin)
{
    Account* member = new Account;
    member->AccountID = cur->no + begin;
    member->Username = std::to_string(cur->student->AccountID);
    std::string pass;
    pass.push_back((cur->student->Birthday.Day / 10) + '0');
    pass.push_back((cur->student->Birthday.Day % 10) + '0');
    pass.push_back((cur->student->Birthday.Month / 10) + '0');
    pass.push_back((cur->student->Birthday.Month % 10) + '0');
    pass.push_back((cur->student->Birthday.Year / 1000) + '0');
    cur->student->Birthday.Year = cur->student->Birthday.Year % 1000;
    pass.push_back((cur->student->Birthday.Year / 100) + '0');
    cur->student->Birthday.Year = cur->student->Birthday.Year % 100;
    pass.push_back((cur->student->Birthday.Year / 10) + '0');
    pass.push_back((cur->student->Birthday.Year % 10) + '0');
    member->Password = pass;
    member->Role = Role::Student;
    member->RoleID = cur->student->AccountID;
    if (account != nullptr)
        *account = member;
    return true;
}

bool CreateAllAccount(Class classes)
{
    Account** before = nullptr;
    int numBefore = 0;
    GetAccounts(&before, &numBefore);
    classes.count = classes.count + numBefore;
    StudentNode* cur = classes.head;
    if (cur != nullptr) {
        Account** member = new Account*[classes.count];
        int i = 0;
        for (; i < numBefore; i++) {
            member[i] = new Account;
            member[i]->AccountID = before[i]->AccountID;
            member[i]->Username = before[i]->Username;
            member[i]->Password = before[i]->Password;
            member[i]->Role = before[i]->Role;
            member[i]->RoleID = before[i]->RoleID;
        }

        while (cur != nullptr) {
            bool status = CreateAccount(cur, &member[i], numBefore);
            cur = cur->pNext;
            i++;
        }
        SaveAccounts(member, classes.count, false);
        ClearAccounts(member, classes.count);
    }
    ClearAccounts(before, numBefore);
    return true;
}

bool SaveProfileStudent(Class classes)
{
    Student** before = nullptr;
    int numBefore = 0;
    GetStudents(&before, &numBefore);

    Student** student = new Student*[classes.count + numBefore];
    StudentNode* cur = classes.head;
    if (cur != nullptr) {
        int i = 0;
        for (; i < numBefore; i++) {
            student[i] = new Student;
            student[i]->AccountID = before[i]->AccountID;
            student[i]->FirstName = before[i]->FirstName;
            student[i]->LastName = before[i]->LastName;
            student[i]->Sex = before[i]->Sex;
            student[i]->Birthday.Day = before[i]->Birthday.Day;
            student[i]->Birthday.Month = before[i]->Birthday.Month;
            student[i]->Birthday.Year = before[i]->Birthday.Year;
            student[i]->ClassName = before[i]->ClassName;
        }

        while (cur != nullptr) {
            student[i] = new Student;
            student[i]->AccountID = cur->student->AccountID;
            student[i]->FirstName = cur->student->FirstName;
            student[i]->LastName = cur->student->LastName;
            student[i]->Sex = cur->student->Sex;
            student[i]->Birthday.Day = cur->student->Birthday.Day;
            student[i]->Birthday.Month = cur->student->Birthday.Month;
            student[i]->Birthday.Year = cur->student->Birthday.Year;
            student[i]->ClassName = cur->student->ClassName;
            cur = cur->pNext;
            i++;
        }
        SaveStudents(student, classes.count + numBefore, false);
        ClearStudents(student, classes.count + numBefore);
    }
    if (numBefore > 0)
        ClearStudents(before, numBefore);
    return true;
}

void LoadListOfClasses(ClassNode*& pH)
{
    std::string line;
    std::ifstream ifs;
    ClassNode* cur = pH;
    ifs.open("data/class.txt");
    while (ifs) {
        std::getline(ifs, line);

        if (pH == nullptr) {
            pH = new ClassNode;
            pH->classname = line;
            pH->pNext = nullptr;
            cur = pH;
        } else {
            cur->pNext = new ClassNode;
            cur = cur->pNext;
            cur->classname = line;
            cur->pNext = nullptr;
        }
    }
    ifs.close();
}

bool ViewListOfStudent(std::string classname)
{
    bool check = false;
    ClassNode* classes = nullptr;
    LoadListOfClasses(classes);
    ClassNode* cur = classes;
    while (classes != nullptr) {
        if (classes->classname == classname)
            check = true;
        classes = classes->pNext;
        delete cur;
        cur = classes;
    }

    if (!check)
        return false;

    int num = 0;
    Student** student = nullptr;
    GetStudents(&student, &num);

    int count = 1;
    char* aa = new char[50]; //fullname
    int length1 = 0; //
    int length2 = 0; //
    bool status = true; //
    for (int i = 0; i < num; i++) {
        if (student[i]->ClassName == classname) {
            if (check) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 3 | FOREGROUND_INTENSITY);
                std::cout << "No " << std::left << std::setw(9) << "ID"
                          << std::left << std::setw(20) << "FullName"
                          << std::left << std::setw(7) << "Sex"
                          << std::left << std::setw(11) << "Birthday"
                          << "Class" << std::endl;
                SetConsoleTextAttribute(hConsole, 7 | FOREGROUND_INTENSITY);
            }
            check = false;
            length1 = student[i]->FirstName.length(); //
            for (int j = 0; j < length1; j++) //
                aa[j] = student[i]->FirstName[j]; //
            length2 = student[i]->LastName.length(); //
            aa[length1] = ' ';
            for (int j = 1; j < length2 + 1; j++) //
                aa[j + length1] = student[i]->LastName[j - 1]; //
            aa[length1 + length2 + 1] = '\0';
            std::cout << std::left << std::setw(3) << count;
            std::cout << std::left << std::setw(9) << student[i]->AccountID;
            std::cout << std::left << std::setw(20) << aa;
            std::cout << std::left << std::setw(7);
            if (student[i]->Sex == Sex::Female)
                std::cout << "Female";
            else if (student[i]->Sex == Sex::Male)
                std::cout << "Male";
            else
                std::cout << "Unkown";
            if (student[i]->Birthday.Day < 10)
                std::cout << "0";
            std::cout << student[i]->Birthday.Day << "/";
            if (student[i]->Birthday.Month < 10)
                std::cout << "0";
            std::cout << student[i]->Birthday.Month << "/"
                      << student[i]->Birthday.Year << " ";
            std::cout << student[i]->ClassName << std::endl;
            count++;
        }
    }
    delete[] aa;

    DeleteClassNode(classes);
    if (check == true)
        return false;
    return true;
}

void DeleteClassNode(ClassNode*& pH)
{
    ClassNode* cur = pH;
    while (pH != nullptr) {
        pH = pH->pNext;
        delete cur;
        cur = pH;
    }
}

void DeleteClass(Class& classes)
{
    StudentNode* cur = classes.head;
    while (classes.head != nullptr) {
        classes.head = classes.head->pNext;
        delete cur->student;
        delete cur;
        cur = classes.head;
    }
}

bool CheckExistClass(std::string classname)
{
    ClassNode* pH = nullptr;
    LoadListOfClasses(pH);
    ClassNode* cur = pH;
    while (cur != nullptr) {
        if (cur->classname == classname) {
            DeleteClassNode(pH);
            return true;
        }
        cur = cur->pNext;
    }
    DeleteClassNode(pH);
    return false;
}