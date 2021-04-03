#include "Class.h"
#include <fstream>

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
                current->student->Birthday.Year = current->student->Birthday.Year * 10 +(str[i] - '0');
        default:
            break;
        }
        status++;
    }
}

void ImportClass(Class& classes)
{
    using namespace std;

    Node* cur = nullptr;
    string str;
    ifstream ifs;
    ifs.open("C:\\Users\\Chopper\\Documents\\Book1.csv");

    while (!ifs.eof()) {
        if (classes.head == nullptr) {
            classes.head = new Node;
            getline(ifs, str);
            SeperateLine(classes.head, str);
            classes.head->pNext = nullptr;
            cur = classes.head;
            str.erase(str.begin(), str.end());
        } 
        else {
            cur->pNext = new Node;
            cur = cur->pNext;
            getline(ifs, str);
            SeperateLine(cur, str);
            cur->pNext = nullptr;
            str.erase(str.begin(), str.end());
        }
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