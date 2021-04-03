#include"scoreboard.h"

int main()
{
	ifstream fint;
	cout << "24. Search and view the scoreboard of a course.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
	{
		search_ViewTheScoreboardOfCourse(fint);
	}
	else
		cout << "Can'n not open file." << endl;
	fint.close();

	cout << "25. Export a scoreboard to a csv file.\n";
	fint.open("NameOfFile.txt");
	if (fint.is_open())
	{
		exportScoreboardToCsvFile(fint);
	}
	else
		cout << "Can'n not open file." << endl;
	fint.close();
	return 0;
}