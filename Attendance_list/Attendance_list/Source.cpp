#include"attendence_list.h"

int main()
{
	string d = "2019-2020-HK2-19APCS1-CM101-Student.txt";
	giveFout(d);
	scoreboard* students= nullptr;
	cout << "26. Search and view attendance list of a course.\n\n";
	ifstream fint;
	fint.open("NameOfFile.txt");
	if (!fint.is_open())
		cout << "Can not open file." << endl;
	else
	{
	    search_ViewAttendanceListOfCourse(fint, students);
	}
	cout << "\n27. Export a attendence list to csv file.\n\n";
	fint.close();
	fint.open("NameOfFile.txt");
	if (!fint.is_open())
		cout << "Can not open file." << endl;
	else
	{
		exportAttendenceListToCsvFile(fint, students);
	}
	delete[] students;
	fint.close();
}