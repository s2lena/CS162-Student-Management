#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>	
using namespace std;
struct date
{
	int day, month, year;
};
struct attendenceList
{
	date day; 
	int h_start,minute_start,h_end, minute_end; 
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
void search_ViewTheScoreboardOfCourse(ifstream & fout);
void exportScoreboardToCsvFile(ifstream& fint);
bool check(string compare, string compare_);
void inputAScoreboard(ifstream& fint,scoreboard& a);
void outputAScoreboard(scoreboard* a, int n);
void giveFout(string& a);
#endif // !SCOREBOARD_H_
