#include "Lecturer.h"
#include <fstream>
#include <iostream>

bool GetLecturers(Lecturer*** outLecturers, int* outNumOfLecturers)
{
    using namespace std;

    ifstream ifs;

    ifs.open("data/lecturer.txt");

    int numOfLecturers = 0;
    ifs >> numOfLecturers;

    Lecturer** lecturers = new Lecturer* [numOfLecturers] { nullptr };

    int sex = 0;

    for (int i = 0; i < numOfLecturers; i++) {
        lecturers[i] = new Lecturer();
        ifs >> lecturers[i]->AccountID;
        ifs.ignore();
        getline(ifs, lecturers[i]->FirstName);
        getline(ifs, lecturers[i]->LastName);
        ifs >> sex;
        lecturers[i]->Sex = (Sex)sex;
        ifs.ignore();
        getline(ifs, lecturers[i]->Title);
    }

    ifs.close();
    if (outNumOfLecturers != nullptr) {
        *outNumOfLecturers = numOfLecturers;
    }

    if (outLecturers != nullptr) {
        *outLecturers = lecturers;
    }

    return true;
}

bool SaveLecturers(Lecturer** lecturers, int numOfLecturers)
{
    using namespace std;

    ofstream ofs;
    ofs.open("data/lecturer.txt");

    ofs << numOfLecturers << endl;

    for (int i = 0; i < numOfLecturers; i++) {
        ofs << lecturers[i]->AccountID << endl;
        ofs << lecturers[i]->FirstName << endl;
        ofs << lecturers[i]->LastName << endl;
        ofs << (int)lecturers[i]->Sex << endl;
        ofs << lecturers[i]->Title;
        if (i + 1 != numOfLecturers)
            ofs << endl;
    }

    ofs.close();
    return true;
}

void ClearLecturers(Lecturer** lecturers, int numOfLectuerers)
{
    for (int i = 0; i < numOfLectuerers; i++) {
        if (lecturers[i] != nullptr) {
            delete lecturers[i];
            lecturers[i] = nullptr;
        }
    }
    delete[] lecturers;
}

Lecturer* GetLecturer(int lecturerID)
{
    Lecturer** lecturers = nullptr;
    int numOfLecturers = 0;

    bool status = GetLecturers(&lecturers, &numOfLecturers);

    Lecturer* lecturer = nullptr;

    for (int i = 0; i < numOfLecturers; i++) {
        if (lecturers[i]->AccountID == lecturerID) {
            lecturer = lecturers[i];
            lecturers[i] = nullptr;
            break;
        }
    }

    ClearLecturers(lecturers, numOfLecturers);

    return lecturer;
}