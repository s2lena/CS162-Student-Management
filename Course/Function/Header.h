#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
struct date {
	int day, month, year;
};
struct time {
	int h, min;
};
struct Course {
	int No;
	//char* ID,*course_name,*Class,*lec_username,*lec_name,*degree, *room;
	string ID;
	string course_name;
	string Class;
	string lec_username;
	string lec_name;
	string degree;
	int gen;
	char* start, * end;//date of starting and ending
	string dow;
	time st, ed;//time of starting and ending
	string room;

};
struct Node {
	Course data;
	Node* next;
};

void load_A_course(ifstream& fin, Course& x, string line);
void save_A_course(ofstream& fout, Course x);
void loadAll(ifstream& fin, Node*& head, int& size);
void saveAll(ofstream& fout, Node* head, int size);
void deleteAll(Node* &head);
void date_format(char*& x, string myStr);




#endif
