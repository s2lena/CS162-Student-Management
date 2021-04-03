#ifndef _LECTURER_H_
#define _LECTURER_H_
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct day
{
	int year, month, date;
};
struct timetime
{
	int hours, minutes;
};
struct lecturer_schedule
{
	int hk = 0;
	string course_name2;
	string course_name1;
	string student_class;
	day day_start, day_end;
	int date;//monday, tuesday...
	timetime time_start;
	timetime time_end;
	string room;
};
struct date
{
	int day, month, year;
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
	int numberOfStudent=0;
	student_course* studentInClass = nullptr;//student in that class
	string nameOfCourse;
	string classs;//main class
	string year;
	string hk;
	your_class_and_course* pNext = nullptr;
	your_class_and_course* pPrev = nullptr;
};
struct management_lecturer_schedule
{
	int n = 0;// current semester
	int hk1 = 0, hk2 = 0, hk3=0;
	string your_name;
	your_class_and_course* yourClassAndCourse = nullptr;
	int numberYourClassAndCourse=0;
	lecturer_schedule* tmp = nullptr;
};
struct scoreboard
{
	int No=-1;
	int ID=-1;
	string student_name;
	string midterm, final, lab, bonus;
	scoreboard* pNext = nullptr;
	scoreboard* pPrev = nullptr;
};
struct importScoreboard
{
	int n=0;// number of student on that csv
	scoreboard* student = nullptr;
};
void receivedListOfCourseInCurrentSemester(ifstream & fint,management_lecturer_schedule& tmp);
void viewListOfCourseInCurrentSemester(management_lecturer_schedule a);
void viewListOfStudentsOfCourse(ifstream & fint, management_lecturer_schedule& tmp);
void giveListOfCourse(ifstream& fint,management_lecturer_schedule a, int numberOfCourse);
bool checkIfTheCourseAndClassBelongToYou(management_lecturer_schedule a, string course_name, string class_name);
void receivedAllStudentOfCourse(ifstream& fint, your_class_and_course*& a);
void outputListOfCourseInCurrentSemester(lecturer_schedule a);
void outputListOfStudentOfCourse(your_class_and_course* a);
void viewAttendenceListOfCourse(ifstream & fint, management_lecturer_schedule a);
void outputListOfAttendenceOfCourse(your_class_and_course* a);
void editAnAttendance(ifstream& fint, management_lecturer_schedule& tmp);
void importScoreboardOfCourse(ifstream& nameoffile, ifstream& fileCSV, management_lecturer_schedule tmp);
void receivedTheScoreboardFromCSV(ifstream& filecsv, importScoreboard& a);
void importAllStudentOfCourse(ofstream& fout, your_class_and_course* a);
void viewScoreboard(ifstream& nameoffile, management_lecturer_schedule tmp);
void seeScoreboard(your_class_and_course* a);
void editGradeOfStudents(ifstream& nameoffile, management_lecturer_schedule tmp);
bool findFile(ifstream& fint, string& a,string b, string c);
bool check(string compare, string compare_);
void shortName(string& a);
void deleteAll(management_lecturer_schedule a);
void deleteAlll(your_class_and_course*& a);
void deleteAllll(importScoreboard& a);
#endif // !_LECTURER_H_
