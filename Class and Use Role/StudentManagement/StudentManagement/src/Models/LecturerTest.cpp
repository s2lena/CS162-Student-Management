#include "Lecturer.h"

bool TestSaveAndGetLecturers() 
{
    int numOfLecturers = 3;

    Lecturer** lecturers = new Lecturer*[3] { nullptr };

    lecturers[0] = new Lecturer;
    lecturers[0]->AccountID = 1;
    lecturers[0]->FirstName = "Dinh Ba";
    lecturers[0]->LastName = "Tien";
    lecturers[0]->Sex = Sex::Male;
    lecturers[0]->Title = "Tien Si";

    lecturers[1] = new Lecturer;
    lecturers[1]->AccountID = 2;
    lecturers[1]->FirstName = "Nguyen Huu";
    lecturers[1]->LastName = "Anh";
    lecturers[1]->Sex = Sex::Male;
    lecturers[1]->Title = "Tien Si";

    lecturers[2] = new Lecturer;
    lecturers[2]->AccountID = 3;
    lecturers[2]->FirstName = "Ha Thi Anh";
    lecturers[2]->LastName = "Thu";
    lecturers[2]->Sex = Sex::Female;
    lecturers[2]->Title = "Thac Si";

    SaveLecturers(lecturers, numOfLecturers);
    
    Lecturer** lecturersGet = nullptr;
    int numOfLecturersGet = 0;

    GetLecturers(&lecturersGet, &numOfLecturersGet);

    if (numOfLecturers != numOfLecturersGet)
        return false;

    for (int i = 0; i < numOfLecturers; i++) {
        if (lecturers[i]->AccountID != lecturersGet[i]->AccountID)
            return false;
        if (lecturers[i]->FirstName.compare(lecturersGet[i]->FirstName) != 0)
            return false;
        if (lecturers[i]->LastName.compare(lecturersGet[i]->LastName) != 0)
            return false;
        if (lecturers[i]->Sex != lecturersGet[i]->Sex)
            return false;
        if (lecturers[i]->Title.compare(lecturersGet[i]->Title) != 0)
            return false;
    }

    ClearLecturers(lecturersGet, numOfLecturers);
    ClearLecturers(lecturers, numOfLecturers);

    return true;
}