#include"student.h"
int main(void)
{
	ifstream fint;//WHEN STORE TIME
	student a;
	receivedInformationStudent(a);

	cout << "1. Check - in.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
		checkIn(fint, a);
	else
		cout << "Can not open file \"NameOfFile.txt\" to work.()\n\n";
	fint.close();

	cout << "2. View check - in result.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
		viewCheckInResult(fint, a);
	else
		cout << "Can not open file \"NameOfFile.txt\" to work.()\n\n";
	fint.close();

	cout << "3. View schedules.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
		viewSchedules(fint, a);
	else
		cout << "Can not open file \"NameOfFile.txt\" to work.()\n\n";
	fint.close();

	cout << "4. View his / her scores of a course.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
		viewScoreOfACourse(fint, a);
	else
		cout << "Can not open file \"NameOfFile.txt\" to work.()\n\n";
	fint.close();
}
