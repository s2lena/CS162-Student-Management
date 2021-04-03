#ifndef STUDENT_H_
#define STUDENT_H_
#include<iostream>
#include<fstream>
#include <time.h>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
struct studentCourse
{
	string courseName;
	studentCourse* pNext = nullptr;
	studentCourse* pPrev = nullptr;
}; 
struct student
{
	string name;
	int ID=0;
	int hk = 0;
	string year;
	string className;
};
struct date
{
	int day, month, year;
};
struct timetime
{
	int h; int minute;
};
struct attendenceList
{
	date day;
	int h_start, minute_start, h_end, minute_end;
	int attendence; //-1 absent / 1 no absent
};
struct student_course {
	int ID;
	string password;
	string your_name;
	date born;
	int gen;
	string class_name;
	int activity;//1 - acitivity / 2 - non activity 
	string fifteen1, fifteen2, midterm, final;//midterm lab final bonus
	attendenceList List[10];
	int dropped;//1 - dropped / 2 - no dropped
};
struct your_class_and_course// management one class of lecturer
{
	int numberOfStudent = 0;
	student_course* studentInClass = nullptr;//student in that class
	string nameOfCourse;
	string classs;//main class
	your_class_and_course* pNext = nullptr;
	your_class_and_course* pPrev = nullptr;
};
struct course
{
	int hk = 0;
	string nameCourse1;
	string nameCourse2;
	string nameLecturer;
	string rank;
	int sex;//1-female 0-male
	date dateStart;
	date dateEnd;
	int firstDay;
	timetime timeStart;
	timetime timeEnd;
	string room;
};
struct studentsSchedule
{
	int numberOfCourse = 0;
	string nameClass;
	course* allOfCourse = nullptr;
};
void receivedInformationStudent(student& a);
void checkIn(ifstream& nameOfFile, student HPK);
void viewCheckInResult(ifstream& nameOfFile, student HPK);
void viewSchedules(ifstream& nameOfFile, student HPK);
void viewScoreOfACourse(ifstream& nameOfFile, student HPK);
void receivedAllCourse(ifstream& fileOfSchedule, studentsSchedule& a);
void outputAllCourse(studentsSchedule a, int hk);
void receivedAllStudentOfCourse(ifstream& fileCourse, your_class_and_course*& a);
void importAllStudentOfCourse(ofstream& fileCourse, your_class_and_course* a);
bool check(string compare, string compare_);
bool findFile(ifstream& fint, string& a, string b, string c);
void deleteAlll(your_class_and_course*& a);
bool fixCheckIn(student_course& tmp, string a);
int converStringToInteger(string a);
string giveDateAndTime();
#endif // !STUDENT_H_
