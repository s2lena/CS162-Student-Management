#include"attendence_list.h"

void search_ViewAttendanceListOfCourse(ifstream& fout, scoreboard*& students)
{
    cout << "Name of your class: "; string a; cin >> a; 
    cout << "Name of your course: "; string b; cin >> b; string support = "Student";
    string compare;
    while (!fout.eof()&&a.length()>4&&b.length()>4)
    {
        fout >> compare;
        if (check(compare, a) && check(compare, b) && check(compare, support))
        {
            ifstream fint;
            fint.open(compare);
            if (fint.is_open())
            {
                int n; fint >> n;
                delete[] students; students = nullptr;
                students = new scoreboard[n];
                for (int i = 0; i < n; i++)
                {
                    inputAAttendenceList(fint, students[i]);
                }
                outputAllAttendenceList(students, n);
            }
            else
                cout << "Can not open file." << endl;
            fint.close();
            return;
        }
    }
    cout << "The information of your class or your couse had wrong." << endl;
}
void outputAllAttendenceList(scoreboard* a, int n)
{
    cout << "Student/Date|";
    for (int j = 0; j < 5; j++)// 10
    {
        cout << a[0].List[j].day.year;
        if (a[0].List[j].day.month < 10) cout << "0";
        else {}
        cout << a[0].List[j].day.month;
        if (a[0].List[j].day.day < 10)  cout << "0";
        else {}
        cout<< a[0].List[j].day.day << "|";
    }cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout  << a[i].ID<<"    |";
        for (int j = 0; j < 5; j++) {
            if (a[i].List[j].attendence == (-1))
                cout << "    0   |";
            else
                cout << "    X   |";
        }cout << endl;
    }cout << endl<<endl;
}
void inputAAttendenceList(ifstream& fint, scoreboard& a)
{
    char tmp[50];
    fint >> a.ID;
    fint.get();
    fint.getline(tmp, 50, '\n');
    a.password = tmp;
    fint.getline(tmp, 50, '\n');
    a.your_name = tmp;
    fint >> a.born.year >> a.born.month >> a.born.day;
    fint >> a.class_name;
    fint >> a.gen;
    fint >> a.activity;
    fint >> a.fifteen1 >> a.fifteen2 >> a.midterm >> a.final;
    for (int i = 0; i < 10; i++)
    {
        fint >> a.List[i].day.year >> a.List[i].day.month >> a.List[i].day.day;
        fint >> a.List[i].h_start >> a.List[i].minute_start;
        fint >> a.List[i].h_end >> a.List[i].minute_end;
        fint >> a.List[i].attendence;
    }
    fint >> a.dropped;//1-dau / 2 - rot
}
bool check(string compare, string compare_)
{
    int n = compare.length();
    int a = compare_.length();
    for (int i = 0; i < n; i++)
    {
        if (compare[i] == compare_[0])
        {
            for (int j = 0; j < a; j++)
            {
                if (compare[i] != compare_[j])
                    break;
                i++;
                if (i >= n) { return false; }
                if (j == a - 1)
                    return true;
            }
        }
    }
    return false;
}
void exportAttendenceListToCsvFile(ifstream& fint, scoreboard *& students)//***
{//fint : "NameOfFile.txt", fout ""
    cout << "Name of your class you want to export: "; string a; cin >> a;
    cout << "Name of your course you want to export: "; string b; cin >> b; string support = "Student";
    string compare; 
    while (!fint.eof()&&a.length()>4&&b.length()>4)
    {
        fint >> compare;
        if (check(compare, a) && check(compare, b) && check(compare, support))
        {
            ifstream fint;
            fint.open(compare);
            if (fint.is_open())
            {
                int n; fint >> n;
                delete[] students; students = nullptr;
                students = new scoreboard[n];
                for (int i = 0; i < n; i++)
                {
                    inputAAttendenceList(fint, students[i]);
                }
                ofstream fout;
                giveFout(compare);
                fout.open(compare);
                if (fout.is_open())
                {
                    fout << "Student/Date,";
                    for (int i = 0; i < 10; i++)
                    {
                        fout << students[0].List[i].day.year << " " << students[0].List[i].day.month 
                            << " " << students[0].List[i].day.day;
                        if (i != 9) { fout << ","; }
                    }fout << endl;
                    for (int j = 0; j < n; j++)
                    {
                        fout << students[j].ID << ",";
                        for (int i = 0; i < 10; i++)
                        {
                            if (students[j].List[i].attendence == (-1))
                                fout << "O";
                            else
                                fout << "X";
                            if (i != 9)fout << ",";
                        }fout << endl;
                    }
                    cout << "The data had been export to csv file.(" << compare << ")" << endl;
                }
                else
                    cout << "Can not create file to save csv." << endl;
            }
            else
                cout << "Can not open file." << endl;
            fint.close();
            return;
        }
    }
    cout << "The information of your class or your couse had wrong." << endl;
}
void giveFout(string& a)
{
    int n = a.length();
    string c = new char[a.length() + 16];
    for (int i = 0; i < n; i++)
        c[i] = a[i];
    string b = "-AttendenceList.csv";
    for (int i = 0; i < 19; i++)
        c[i + n - 4] = b[i];
    c[n + 15] = '\0';
    char d[100] ;
    for (int i = 0; i < n + 16; i++)
        d[i] = c[i];
    a = d;
}