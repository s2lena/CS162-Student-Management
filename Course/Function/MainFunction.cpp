#include "Header.h"

void load_A_course(ifstream& fin, Course& x, string line) {
	
	string myStr;

	stringstream ss(line);
	getline(ss, myStr, ',');
	x.No = stoi(myStr);
	getline(ss, x.ID, ',');
	getline(ss, x.course_name, ',');
	getline(ss, x.Class, ',');
	getline(ss, x.lec_username, ',');
	getline(ss, x.lec_name, ',');
	getline(ss, x.degree, ',');
	getline(ss, myStr, ',');
	if (myStr == "Male")
		x.gen = 0;
	else x.gen = 1;
	getline(ss, myStr, ',');
	date_format(x.start, myStr);
	getline(ss, myStr, ',');
	date_format(x.end, myStr);
		
	getline(ss, x.dow, ',');
	getline(ss, myStr, ',');
	x.st.h = stoi(myStr);
	getline(ss, myStr, ',');
	x.st.min = stoi(myStr);

	getline(ss, myStr, ',');
	x.ed.h = stoi(myStr);
	getline(ss, myStr, ',');
	x.ed.min = stoi(myStr);

	getline(ss, x.room, ',');

	ss.clear();
	ss.str("");
	
}

void loadAll(ifstream& fin, Node*& head, int& size) {
	fin.ignore(255, '\n');//ignore the first line
	head = nullptr;
	size = 0;
	//int i = 0;

	string line;
	//int num=10;
	//x = new Course[num];
	Node* cur=nullptr;
	while (getline(fin, line)) {
		if (head == nullptr) {
			head = new Node;
			load_A_course(fin, head->data, line);
			cur = head;
			cur->next = nullptr;
			++size;
		}
		//++i;
		else {
			++size;
			cur->next = new Node;
			cur = cur->next;
			load_A_course(fin, cur->data, line);
			cur->next = nullptr;
		}
		/*if (size == num) {
			//reaching the limit
			Course* tmp = new Course[size + 5];
			for (int i = 0; i < size; ++i)
				tmp[i] = x[i];
			delete[] x;
			x = tmp;
			num += 5;
		}*/
	
	}
						
}

void save_A_course(ofstream& fout, Course x) {

	fout << x.No << endl;
	fout << x.ID << endl;
	fout << x.course_name << endl;
	fout << x.Class << endl;
	fout << x.lec_username << endl;
	fout << x.lec_name << endl;
	fout << x.degree << endl;
	fout << x.gen << endl;
	fout << x.start << endl;
	fout << x.end << endl;
	fout << x.dow << endl;
	fout << x.st.h << " ";
	fout << x.st.min << endl;
	fout << x.ed.h << " ";
	fout << x.ed.min << endl;
	fout << x.room << endl;
}

void saveAll(ofstream& fout, Node* head, int size) {
	fout << size << endl;
	fout << endl;
	while(head!=nullptr) {
		save_A_course(fout,head->data);
		head = head->next;
		fout << endl;
	}
}
void deleteAll(Node*& head) {
	Node* cur = head;
	while (head != nullptr) {
		head = head->next;
		delete cur;
		cur = head;
	}
}