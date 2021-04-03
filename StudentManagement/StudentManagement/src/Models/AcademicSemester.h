#ifndef ACADEMIC_SEMESTER_H
#define ACADEMIC_SEMESTER_H

#include <string>

struct Node {
    std::string semester;
    std::string academic;
    Node* pNext;
};

void CreateSemester(std::string semester, std::string academic);
void LoadSemester(Node*& pH);
void ShowSemester(Node* pH);
bool DeleteASemeter(Node*& pH, std::string semester, std::string academic);
void SaveSemester(Node* pH);
bool CheckSemester(std::string semester, std::string academic);
void DeleteSemester(Node*& pH);

#endif // ACADEMIC_SEMESTER_H
