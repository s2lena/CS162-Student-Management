#include "AcademicSemester.h"
#include <fstream>
#include <iostream>

void CreateSemester(std::string semester, std::string academic)
{
    std::ofstream ofs;
    ofs.open("data/academic.txt", std::ios::app);
    ofs << semester << std::endl;
    ofs << academic << std::endl;
    ofs.close();
}

void LoadSemester(Node*& pH)
{
    std::ifstream ifs;
    Node* cur = nullptr;
    std::string sem, aca;

    ifs.open("data/academic.txt");
    while (ifs) {
        std::getline(ifs, sem);
        if (sem == "")
            break;
        std::getline(ifs, aca);
        if (pH == nullptr) {
            pH = new Node;
            pH->semester = sem;
            pH->academic = aca;
            pH->pNext = nullptr;
            cur = pH;
        } else {
            cur->pNext = new Node;
            cur = cur->pNext;
            cur->semester = sem;
            cur->academic = aca;
            cur->pNext = nullptr;
        }
    }
    ifs.close();
}

void ShowSemester(Node* pH)
{
    Node* cur = pH;
    while (cur != nullptr) {
        std::cout << cur->semester << std::endl;
        std::cout << cur->academic << std::endl;
        cur = cur->pNext;
    }
}

bool DeleteASemeter(Node*& pH, std::string semester, std::string academic)
{
    if (pH == nullptr)
        return false;

    Node* tmp = nullptr;

    if (pH->semester == semester && pH->academic == academic) {
        tmp = pH;
        pH = pH->pNext;
        delete tmp;
        return true;
    } 
    else {
        Node* cur = pH;
        while (cur->pNext != nullptr) {
            if (cur->pNext->academic == academic && cur->pNext->semester == semester)
                break;
            cur = cur->pNext;
        }
        if (cur->pNext == nullptr)
            return false;
        tmp = cur->pNext;
        cur->pNext = tmp->pNext;
        delete tmp;
        return true;
    }

    return false;
}

void SaveSemester(Node* pH)
{
    std::ofstream ofs;
    Node* cur = pH;
    ofs.open("data/academic.txt");
    while (cur != nullptr) {
        ofs << cur->semester << std::endl;
        ofs << cur->academic << std::endl;
        cur = cur->pNext;
    }
    ofs.close();
}

bool CheckSemester(std::string semester, std::string academic)
{
    Node* pH = nullptr;
    LoadSemester(pH);
    bool check = false;
    Node* tmp = pH; 
    while (pH != nullptr) {
        if (pH->academic == academic && pH->semester == semester)
            check = true;
        pH = pH->pNext;
        delete tmp;
        tmp = pH;
    }
    return check;
}

void DeleteSemester(Node*& pH)
{
    Node* cur = pH;
    while (pH != nullptr) {
        pH = pH->pNext;
        delete cur;
        cur = pH;
    }
}