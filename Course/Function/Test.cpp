#include "Header.h"

int main() {
	ifstream fin;
	ofstream fout;

	/*cout << "From a semester, import schedule" << endl;
	cout << "Enter an academic year: ";
	string year;
	getline(cin, year);
	cout << "Enter a semester: ";
	string ses;
	getline(cin, ses);
	cout << "Enter a class: ";
	string Class;
	getline(cin, Class);*/

	Node* sche;
	int size = 0;
	fin.open("C:/Users/VINH PHU/Desktop/19APCS1-Schedule.csv");
	if (fin.is_open()) {
		//load_A_course(fin, sche);
		loadAll(fin, sche, size);
		fin.close();

		fout.open("C:/Users/VINH PHU/Desktop/Test(2019-2020-HK2-Schedule-19APCS1).txt");
		if (fout.is_open()) {
			//save_A_course(fout, sche);
			saveAll(fout, sche, size);
			fout.close();
		}
		else cout << "Cannot save the file";
	}
	else cout << "Cann't open the file" << endl;

	deleteAll(sche);

	return 0;
}