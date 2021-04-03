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

short Detect(std::string str, short t);
void SeperateLine(Node*& current, std::string str);
void ImportClass(Class& classes);
void DeleteClass(Class& classes);
bool TestImportClass();

#endif // CLASS_H
