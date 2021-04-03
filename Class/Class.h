#ifndef CLASS_H
#define CLASS_H

#include "Student.h"
#include <string>

struct Node {
    int no;
    Student* student;
    Node* pNext;
};

struct Class {
    Node* head;
}; 

std::string ChooseClass(std::string className);
short Detect(std::string str, short t);
void SeperateLine(Node*& current, std::string str);
bool ImportClass(Class& classes, std::string className);
void AddNewStudent(Class& classes, Student student);
bool EditExistingStudent(Class& classes, int StudentID, Student student);
bool RemoveAStudent(Class& classes, int studentID);
bool ChangeStudentFromClassAtoClassB(std::string fileA, std::string fileB, int studentID);
bool SaveClass(Class classes, std::string className);
void DisplayClass(Class classes);
void DisplayListOfClass();
void DeleteClass(Class& classes);
bool TestImportClassAndEditStudent();
bool TestChangeClass();

#endif // CLASS_H
