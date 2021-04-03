#ifndef CLASS_H
#define CLASS_H

#include "Student.h"
#include <string>

struct StudentNode {
    int no;
    Student* student;
    StudentNode* pNext;
};

struct Class {
    StudentNode* head;
    int count;
};

struct ClassNode {
    std::string classname;
    ClassNode* pNext;
};

std::string ChooseClass(std::string className);
short Detect(std::string str, short t);
void SeperateLine(StudentNode*& current, std::string str);
bool ImportClass(Class& classes, std::string className);
void AddNewStudent(Student* student);
bool RemoveAStudent(int studentID);
bool ChangeStudentFromClassAtoClassB(int studentID, std::string classname);
void DeleteClass(Class& classes);
void DeleteClassNode(ClassNode*& pH);
bool CreateAccount(StudentNode* cur, Account** account, int begin);
bool CreateAllAccount(Class classes);
bool ViewListOfStudent(std::string classname);
bool SaveProfileStudent(Class classes);
void LoadListOfClasses(ClassNode*& pH);
bool CheckExistClass(std::string classname);

#endif // CLASS_H
