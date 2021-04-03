#ifndef _ATTENDENCE_LIST_H_
#define _ATTENDENCE_LIST_H_

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
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
struct scoreboard {
	int ID;
	string password;
	string your_name;
	date born;
	int gen;
	string class_name;
	int activity;//1 - acitivity / 2 - non activity 
	string fifteen1, fifteen2, midterm, final;
	attendenceList List[10];
	int dropped;//1 - dropped / 2 - no dropped
};
void search_ViewAttendanceListOfCourse(ifstream& fout, scoreboard*& students);
void inputAAttendenceList(ifstream& fint, scoreboard& students);
bool check(string compare, string compare_);
void outputAllAttendenceList(scoreboard* a, int n);
void giveFout(string& a);
void exportAttendenceListToCsvFile(ifstream& fint, scoreboard*& students);//***
#endif // !_ATTENDENCE_LIST_H_
