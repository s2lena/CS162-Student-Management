#include "Class.h"
#include <fstream>
#include <iostream>

std::string ChooseClass(std::string className)
{
    std::string file;
    if (className.compare("19CTT1") == 0)
        file = "C:\\Users\\Chopper\\Documents\\19CTT1.csv";
    else if (className.compare("19CTT2") == 0)
        file = "C:\\Users\\Chopper\\Documents\\19CTT2.csv";
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

void SeperateLine(Node*& current, std::string str)
{
    using namespace std;
    string tmp;
    int prev;
    int cur = 0;
    int status = 1;
    current->student = new Student;
    while (status <= 8) {
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
            current->student->Birthday.Day = 0;
            for (int i = prev; i < cur; i++)
                current->student->Birthday.Day = current->student->Birthday.Day * 10 + (str[i] - '0');
            break;
        case 7:
            current->student->Birthday.Month = 0;
            for (int i = prev; i < cur; i++)
                current->student->Birthday.Month = current->student->Birthday.Month * 10 + (str[i] - '0');
        case 8:
            current->student->Birthday.Year = 0;
            for (int i = prev; i < cur; i++)
                current->student->Birthday.Year = current->student->Birthday.Year * 10 + (str[i] - '0');
        default:
            break;
        }
        status++;
    }
}

bool ImportClass(Class& classes, std::string className)
{
    using namespace std;

    Node* cur = nullptr;
    string str;
    ifstream ifs;
    string file = ChooseClass(className);
    ifs.open(file);

    while (!ifs.eof()) {
        if (classes.head == nullptr) {
            classes.head = new Node;
            getline(ifs, str);
            SeperateLine(classes.head, str);
            classes.head->pNext = nullptr;
            cur = classes.head;
            str.erase(str.begin(), str.end());
        } else {
            cur->pNext = new Node;
            cur = cur->pNext;
            getline(ifs, str);
            SeperateLine(cur, str);
            cur->pNext = nullptr;
            str.erase(str.begin(), str.end());
        }
    }

    ifs.close();

    return true;
}

void AddNewStudent(Class& classes, Student student)
{
    Node* cur = classes.head;
    while (cur != nullptr && cur->pNext != nullptr) {
        cur = cur->pNext;
    }
    int no = cur->no;
    cur->pNext = new Node;
    cur = cur->pNext;
    cur->no = no + 1;
    cur->student = new Student;
    cur->student->AccountID = student.AccountID;
    cur->student->FirstName = student.FirstName;
    cur->student->LastName = student.LastName;
    cur->student->Sex = (Sex)student.Sex;
    cur->student->Birthday.Day = student.Birthday.Day;
    cur->student->Birthday.Month = student.Birthday.Month;
    cur->student->Birthday.Year = student.Birthday.Year;
    cur->pNext = nullptr;
}

bool EditExistingStudent(Class& classes, int studentID, Student student)
{
    Node* cur = classes.head;
    while (cur != nullptr && cur->student->AccountID != studentID) {
        cur = cur->pNext;
    }

    if (cur == nullptr)
        return false;

    cur->student->AccountID = student.AccountID;
    cur->student->FirstName = student.FirstName;
    cur->student->LastName = student.LastName;
    cur->student->Birthday.Day = student.Birthday.Day;
    cur->student->Birthday.Month = student.Birthday.Month;
    cur->student->Birthday.Year = student.Birthday.Year;
    cur->student->Sex = (Sex)student.Sex;
    return true;
}

bool SaveClass(Class classes, std::string className)
{
    using namespace std;

    Node* cur = classes.head;
    ofstream ofs;
    string file = ChooseClass(className);
    ofs.open(file);
    
    while (cur != nullptr) {
        ofs << cur->no << ",";
        ofs << cur->student->AccountID << ",";
        ofs << cur->student->FirstName << ",";
        ofs << cur->student->LastName << ",";
        if (cur->student->Sex == Sex::Female)
            ofs << "Female" << ",";
        else if (cur->student->Sex == Sex::Male)
            ofs << "Male" << ",";
        else
            ofs << "Unknown" << ",";
        ofs << (int)cur->student->Birthday.Day << ",";
        ofs << (int)cur->student->Birthday.Month << ",";
        ofs << (int)cur->student->Birthday.Year;
        cur = cur->pNext;
        if (cur != nullptr)
            ofs << endl;
    }
    ofs.close();
    return true;
}

bool RemoveAStudent(Class& classes, int studentID)
{
    Node* cur = classes.head;
    if (classes.head->student->AccountID == studentID) {
        classes.head = classes.head->pNext;
        delete cur;
        cur = nullptr;
        return true;
    } 
    else {
        while (cur->pNext != nullptr && cur->pNext->student->AccountID != studentID)
            cur = cur->pNext;

        if (cur->pNext == nullptr)
            return false;

        Node* tmp = cur->pNext;
        cur->pNext = tmp->pNext;
        delete tmp;

        cur = cur->pNext;
        while (cur != nullptr) {
            cur->no--;
            cur = cur->pNext;
        }

        return true;
    } 
}

bool ChangeStudentFromClassAtoClassB(std::string fileA, std::string fileB, int studentID)
{
    Class classA;
    classA.head = nullptr;
    ImportClass(classA, fileA);
    Class classB;
    classB.head = nullptr;
    ImportClass(classB, fileB);

    Node* cur = classA.head;
    while (cur != nullptr && cur->student->AccountID != studentID)
        cur = cur->pNext;
    if (cur == nullptr)
        return false;
    Student change;
    change.AccountID = cur->student->AccountID;
    change.FirstName = cur->student->FirstName;
    change.LastName = cur->student->LastName;
    change.Sex = (Sex)cur->student->Sex;
    change.Birthday.Day = cur->student->Birthday.Day;
    change.Birthday.Month = cur->student->Birthday.Month;
    change.Birthday.Year = cur->student->Birthday.Year;
    
    RemoveAStudent(classA, change.AccountID);
    SaveClass(classA, fileA);
    AddNewStudent(classB, change);
    SaveClass(classB, fileB);
    DeleteClass(classA);
    DeleteClass(classB);
    return true;
}

void DisplayClass(Class classes)
{
    using namespace std;

    Node* cur = classes.head;
    while (cur != nullptr) {
        cout << cur->no << " ";
        cout << cur->student->AccountID << " ";
        cout << cur->student->FirstName << " ";
        cout << cur->student->LastName << " ";
        cout << (int)cur->student->Sex << " ";
        cout << (int)cur->student->Birthday.Day << "/";
        cout << (int)cur->student->Birthday.Month << "/";
        cout << (int)cur->student->Birthday.Year << " ";
        cout << endl;
        cur = cur->pNext;
    }
}

void DeleteClass(Class& classes)
{
    Node* cur = classes.head;
    while (classes.head != nullptr) {
        classes.head = classes.head->pNext;
        delete cur->student;
        delete cur;
        cur = classes.head;
    }
}