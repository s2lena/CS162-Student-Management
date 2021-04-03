#include"scoreboard.h"

void search_ViewTheScoreboardOfCourse(ifstream& fout)
{
    cout << "Name of your class: "; string a; cin >> a;
    cout << "Name of your course: "; string b; cin >> b; string support = "Student";
    string compare;
    while (!fout.eof()&&a.length()>4&&b.length()>4)
    {
        fout >> compare;
        if (check(compare, a) && check(compare, b)&&check(compare,support))
        {
            ifstream fint;
            fint.open(compare);
            if (fint.is_open())
            {
                int n; fint >> n;
                scoreboard* point = new scoreboard[n];
                for (int i = 0; i < n; i++)
                {
                    inputAScoreboard(fint, point[i]);
                }
                outputAScoreboard(point, n);
                delete[] point;
            }
            else
                cout << "Can not open file.()\n\n" << endl;
            fint.close();
            return;
        }
    }
    cout << "The information of your class or your couse had wrong.()\n\n" << endl;
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
void inputAScoreboard(ifstream& fint, scoreboard& a)
{
    char tmp[50];
    fint >> a.ID;
    fint.get();
    fint.getline(tmp,50,'\n');
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
void outputAScoreboard(scoreboard* a, int n)
{
    cout << "No StudentsID Class   Midterm Final Lab Bonus" << endl;///////name
    for (int i = 0; i < n; i++)
    {
        cout << left << setw(3) << i + 1;
        cout << left << setw(11) << a[i].ID;
        cout << left << setw(8) << a[i].class_name;
        cout << left << setw(8) << a[i].fifteen1;
        cout << left << setw(6) << a[i].fifteen2;
        cout << left << setw(4) << a[i].midterm; 
        cout << a[i].final << endl;
    }cout << "\n";
}
void exportScoreboardToCsvFile(ifstream& fint)//***
{//fint : "NameOfFile.txt", fout ""
    cout << "Name of your class you want to export: "; string a; cin >> a;
    cout << "Name of your course you want to export: "; string b; cin >> b; string support = "Student";
    string compare;
    while (!fint.eof()&& a.length()>4 && b.length()>4)
    {
        fint >> compare;
        if (check(compare, a) && check(compare, b) && check(compare, support))
        {
            ifstream fint;
            fint.open(compare);
            if (fint.is_open())
            {
                int n; fint >> n;
                scoreboard* point = new scoreboard[n];
                for (int i = 0; i < n; i++)
                {
                    inputAScoreboard(fint, point[i]);
                }
                ofstream fout;
                giveFout(compare);
                fout.open(compare);
                if (fout.is_open())
                {
                    fout << "No ,Students ID,Full name,Class,Bonus,Midterm,Final,Total\n";
                    for (int i = 0; i < n; i++)
                    {
                        fout << i + 1 << "," << point[i].ID << "," << point[i].your_name
                            << "," << point[i].class_name << "," << point[i].fifteen1<<","
                            << point[i].fifteen2 << "," << point[i].midterm << "," << point[i].final << endl;
                    }
                    cout << "The data had been export to csv file.("<<compare<<")" << endl;
                }
                else
                    cout << "Can not create file to save csv." << endl;
                delete[] point;
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
    char* c = new char[n+1];
    for (int i = 0; i < n; i++)
        c[i] = a[i];
    c[n - 3] = 'c';
    c[n - 2] = 's';
    c[n - 1] = 'v';
    c[n] = '\0';
    a = c;
}