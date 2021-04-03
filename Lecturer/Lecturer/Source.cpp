#include"lecturer.h"

int main()
{
	ifstream fint; management_lecturer_schedule a;
	fint.open("NameOfFile.txt");
	if (!fint.is_open()) {
		cout << "Can not open file\"NameOfFile.txt\".()\n"; fint.close();
	}
	else
	{
		receivedListOfCourseInCurrentSemester(fint, a);//dinh ba tie//findFile
		while (a.numberYourClassAndCourse == 0)
		{
			cout << "\nPlese input again:\n"; cin.get();
			receivedListOfCourseInCurrentSemester(fint, a);
		}int choose = -1; system("cls"); fint.close();
	menu:
		if (choose != (-1))
		{
			cout << "0. Back." << endl;
			cout << "1. Return." << endl;
			cout << "Your choose: "; cin >> choose;
			if (choose == 1)
				return 0;
			else
				system("cls");
		}
		cout << "1. View list of courses in the current semester.\n";
		cout << "2. View list of students of a course.\n";
		cout << "3. View attendance list of a course.\n";
		cout << "4. Edit an attendance.\n";
		cout << "5. import scoreboard of a course(midterm, final, lab, bonus) from a csv file.\n";
		cout << "6. Edit grade of a student.\n";
		cout << "7. View a scoreboard\n";
		cout << "Which one you want to do: "; cin >> choose; system("cls");
		switch (choose)
		{
		case 1:
			cout << "1. View list of courses in the current semester.\n\n";
			fint.open("NameOfFile.txt");
			if (!fint.is_open())
				cout << "Can not open this file." << endl;
			else
			{
				viewListOfCourseInCurrentSemester(a);
			}fint.close();
			goto menu;
		case 2:
			cout << "2. View list of students of a course.\n\n";
			fint.open("NameOfFile.txt");
			if (!fint.is_open())
				cout << "Can not open file\"NameOfFile.txt\"." << endl << endl;
			else
			{
				viewListOfStudentsOfCourse(fint, a);
			}fint.close();
			goto menu;
		case 3:
			cout << "3. View attendance list of a course.\n\n";
			fint.open("NameOfFile.txt");
			if (fint.is_open())
			{
				if (a.numberYourClassAndCourse == 0)
				{
					receivedListOfCourseInCurrentSemester(fint, a);
					fint.close();
					if (a.numberYourClassAndCourse == 0)
					{
						cout << "Return"; return 0;
					}
					fint.open("NameOfFile.txt");
					if (fint.is_open())
						viewAttendenceListOfCourse(fint, a);//we need a to check if that course is belong to 
						//lecture or not
				}
				else
					viewAttendenceListOfCourse(fint, a);
			}fint.close();
			goto menu;
		case 4:
			cout << "4. Edit an attendance.\n\n";
			fint.open("NameOfFile.txt");
			if (fint.is_open())
			{
				if (a.numberYourClassAndCourse == 0)
				{
					receivedListOfCourseInCurrentSemester(fint, a);
					fint.close();
					fint.open("NameOfFile.txt");
					if (fint.is_open())
						editAnAttendance(fint, a);
				}
				else
					editAnAttendance(fint, a);
			}fint.close();
			goto menu;
		case 5:
			cout << "5. import scoreboard of a course(midterm, final, lab, bonus) from a csv file.\n\n";
			fint.open("NameOfFile.txt");//still problem
			if (fint.is_open())
			{
				cout << "Name of file to import(19APCS1-CS162-Scoreboard.csv): ";
				string nameofcsvfile; cin >> nameofcsvfile; cin.get();
				ifstream nameOfCSVFile(nameofcsvfile);
				if (nameOfCSVFile.is_open())
				{
					if (a.numberYourClassAndCourse == 0)
					{
						receivedListOfCourseInCurrentSemester(fint, a);
						if (a.numberYourClassAndCourse == 0)
						{
							cout << "Return"; return 0;
						}
						fint.close();
						fint.open("NameOfFile.txt");
						if (fint.is_open())
							importScoreboardOfCourse(fint, nameOfCSVFile, a);
					}

					else
						importScoreboardOfCourse(fint, nameOfCSVFile, a);
				}
				else
					cout << "Can not open file csv.\n\n";
			}
			else
				cout << "Can not open file \"NameOfFile.txt\".\n\n";
			fint.close();
			goto menu;
		case 6:
			cout << "6. Edit grade of a student.\n\n";
			fint.open("NameOfFile.txt");//still problem
			if (fint.is_open())
			{
				if (a.numberYourClassAndCourse == 0)
				{
					receivedListOfCourseInCurrentSemester(fint, a);
					if (a.numberYourClassAndCourse == 0)
					{
						cout << "Return"; return 0;
					}
					fint.close();
					fint.open("NameOfFile.txt");
					if (fint.is_open())
						editGradeOfStudents(fint, a);
				}
				else
					editGradeOfStudents(fint, a);
			}
			else
				cout << "Can not open file \"NameOfFile.txt\".\n\n";
			fint.close();
			goto menu;
		case 7:
			cout << "7. View a scoreboard\n\n";
			fint.open("NameOfFile.txt");
			if (!fint.is_open())
				cout << "Can not open file \"NameOfFile.txt\".()\n\n";
			else
			{
				if (a.numberYourClassAndCourse == 0)
				{
					receivedListOfCourseInCurrentSemester(fint, a);
					if (a.numberYourClassAndCourse == 0)
					{
						cout << "Return"; return 0;
					}
					fint.close();
					fint.open("NameOfFile.txt");
					if (fint.is_open())
						viewScoreboard(fint, a);
				}
				else
					viewScoreboard(fint, a);
			} fint.close();
			goto menu;
		case 0:
			cout << "See you again!!!" << endl << endl;
		default:
			cout << "You is stupid!!!hi.()\n\n";
			break;
		}
		deleteAll(a);
		return 0;
	}
}