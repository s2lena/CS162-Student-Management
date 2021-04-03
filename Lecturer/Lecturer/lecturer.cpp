#include"lecturer.h"

void receivedListOfCourseInCurrentSemester(ifstream& fint, management_lecturer_schedule& tmp)
{
    cout << "Your name: "; string b; char efff[50]; cin.getline(efff, 50, '\n'); b = efff;
    cout << "Year(2018-2019): "; string a; cin >> a;
    string c = "Schedule-Lecturer";
    shortName(b);
    if (!findFile(fint, a, b, c))
        cout << "The information you input is wrong.\n";
    else
    {
        ifstream fint_;
        fint_.open(a);
        if (!fint_.is_open())
            cout << "Can not open this file." << endl;
        else
        {
            fint_ >> tmp.hk1 >> tmp.hk2 >> tmp.hk3;
            tmp.numberYourClassAndCourse = tmp.hk1 + tmp.hk2 + tmp.hk3;
            char eff[50]; fint_.get(); fint_.getline(eff, 50, '\n');
            tmp.your_name = eff;
            cout << "The current semester(1-2-3): "; int alo; cin >> alo;
            if(alo<4&&alo>-1) tmp.n = alo;
            tmp.tmp = new lecturer_schedule[tmp.hk1 + tmp.hk2 + tmp.hk3];
            giveListOfCourse(fint_, tmp, tmp.hk1 + tmp.hk2 + tmp.hk3);
        }
        fint_.close();
    }
}
void viewListOfCourseInCurrentSemester(management_lecturer_schedule a)
{
    bool improve = false;
    for (int i = 0; i < a.numberYourClassAndCourse; i++)
    {
        if (a.n == a.tmp[i].hk)
        {
            cout << endl;
            outputListOfCourseInCurrentSemester(a.tmp[i]);
            improve = true;
        }
    }
    if (!improve)
        cout << "In that semester you don't have any course." << endl << endl;
}
void viewListOfStudentsOfCourse(ifstream& fint, management_lecturer_schedule& tmp)
{
    cout << "Please input name of class you want to see: ";
    string class_name;
    cin >> class_name;
    cout << "Please input name of course you want to see: ";
    string course_name;
    cin >> course_name;
    string student = "Student";
    if (checkIfTheCourseAndClassBelongToYou(tmp, course_name, class_name))
    {
        cout << "Yeah. This class and course belong to you. I will print it for you." << endl;
        if (!findFile(fint, student, class_name, course_name))
            cout << "We can't see file of that class.\n\n";
        else
        {
            ifstream fint1;
            fint1.open(student);
            if (!fint.is_open())
                cout << "We had see that file. But we can't not open that file.()\n\n";
            else
            {
                your_class_and_course* viewCourse = new your_class_and_course;
                receivedAllStudentOfCourse(fint1, viewCourse);
                outputListOfStudentOfCourse(viewCourse);
                deleteAlll(viewCourse);
            }
            fint1.close();
        }
    }
    else
        cout << "That course and class don't belong to you." << endl;

}
bool checkIfTheCourseAndClassBelongToYou(management_lecturer_schedule a, string course_name, string class_name)
{
    for (int i = 0; i < a.numberYourClassAndCourse; i++)
    {
        if (a.tmp[i].course_name1 == course_name && a.tmp[i].student_class == class_name)
        {
            return true;
        }
    }
    return false;
}
void shortName(string& a)
{
    int n = a.length();
    for (int i = 0; i < n; i++)
        a[i] = tolower(a[i]);
    for (int i = 0; i < n - 1; i++)// space space ....
    {
        if (a[i] == ' ')
            if (a[i + 1] == ' ' || i == 0)
            {
                --n;
                for (int j = i; j < n; j++)
                    a[j] = a[j + 1];
                a[n] = '\0';
                i--;
            }
    }
    if (a[n - 1] == ' ') { a[n - 1] = '\0'; --n; }
    int support = 0; bool check = false;
    for (int i = n - 1; i >= 0; i--)//find size of short name
    {
        if (a[i] == ' ')
        {
            for (int j = i - 1; j >= 0; j--)
                if (a[j] == ' ')
                {
                    support++; check = true;
                    break;
                }
                else if (j == 0) { support++; i = 0; }
        }
        else if (check == false)
            support++;
    }
    char* tmp = new char[support + 1];
    if (check == true) support = 1;
    tmp[0] = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] == ' ')
        {
            for (int j = i + 1; j < n; j++)
            {
                if (a[j] == ' ') {
                    tmp[support] = a[i + 1]; support++; break;
                }
                if (j == n - 1)
                {
                    for (int h = i + 1; h < n; h++)
                    {
                        tmp[support] = a[h];
                        support++;
                    }
                    tmp[support] = '\0'; a = tmp; return;
                }
            }
        }
    }
    return;
}
void outputListOfCourseInCurrentSemester(lecturer_schedule a)
{
        cout << "Course: "; cout << a.course_name1 << endl;
        cout << "The full name of course: "; cout << a.course_name2 << endl;
        cout << "Class student: "; cout << a.student_class << endl;
        cout << "Date start: ";
        cout << a.day_start.year << " "
            << a.day_start.month << " " << a.day_start.date << endl;
        cout << "Date end: ";
        cout << a.day_end.year << " "
            << a.day_end.month << " " << a.day_end.date << endl;
        cout << "Date: ";
        switch (a.date)
        {
        case 2:
            cout << "Monday";
            break;
        case 3:
            cout << "Tuesday";
            break;
        case 4:
            cout << "Wednesday";
            break;
        case 5:
            cout << "Thursday";
            break;
        case 6:
            cout << "Friday";
            break;
        case 7:
            cout << "Saturday";
            break;
        case 8:
            cout << "Sunday";
            break;
        default:
            break;
        } cout << endl;
        cout << "Time start: "; cout << a.time_start.hours << "h" << a.time_end.minutes << endl;
        cout << "Time end: "; cout << a.time_end.hours << "h" << a.time_end.minutes << endl;
        cout << "Room: "; cout << a.room << endl << endl;
}
void giveListOfCourse(ifstream& fint, management_lecturer_schedule a, int numberOfCourse)
{
    char b[50]; string support;
    for (int i = 0; i < numberOfCourse; i++)
    {
        fint >> support;
        if (support == "hk1")
            a.tmp[i].hk = 1;
        else if (support == "hk2")
            a.tmp[i].hk = 2;
        else if (support == "hk3")
            a.tmp[i].hk = 3;
        else
            a.tmp[i].hk = 0;
        fint >> a.tmp[i].course_name1;
        fint.get();
        fint.getline(b, 50, '\n');
        a.tmp[i].course_name2 = b;
        fint >> a.tmp[i].student_class;
        fint >> a.tmp[i].day_start.year >> a.tmp[i].day_start.month >> a.tmp[i].day_start.date;
        fint >> a.tmp[i].day_end.year >> a.tmp[i].day_end.month >> a.tmp[i].day_end.date;
        fint >> a.tmp[i].date;
        fint >> a.tmp[i].time_start.hours >> a.tmp[i].time_start.minutes;
        fint >> a.tmp[i].time_end.hours >> a.tmp[i].time_end.minutes;
        fint >> a.tmp[i].room;
    }
}
void outputListOfStudentOfCourse(your_class_and_course* a)
{
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        cout << a->studentInClass[i].your_name << endl;
    }cout << endl;
}
void receivedAllStudentOfCourse(ifstream& fint, your_class_and_course*& a)
{
    if (a == nullptr)
        a = new your_class_and_course;
    char tmp[50];
    fint >> a->numberOfStudent;
    a->studentInClass = new student_course[a->numberOfStudent];
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        fint >> a->studentInClass[i].ID;
        fint.get();
        fint.getline(tmp, 50, '\n');
        a->studentInClass[i].password = tmp;
        fint.getline(tmp, 50, '\n');
        a->studentInClass[i].your_name = tmp;
        fint >> a->studentInClass[i].born.year >> a->studentInClass[i].born.month 
            >> a->studentInClass[i].born.day;
        fint >> a->studentInClass[i].class_name;
        fint >> a->studentInClass[i].gen;
        fint >> a->studentInClass[i].activity;
        fint >> a->studentInClass[i].fifteen1 >> a->studentInClass[i].fifteen2 
            >> a->studentInClass[i].midterm >> a->studentInClass[i].final;
        for (int j = 0; j < 10; j++)
        {
            fint >> a->studentInClass[i].List[j].day.year//dong mau xanh what mean? 
                >> a->studentInClass[i].List[j].day.month >> a->studentInClass[i].List[j].day.day;
            fint >> a->studentInClass[i].List[j].h_start >> a->studentInClass[i].List[j].minute_start;
            fint >> a->studentInClass[i].List[j].h_end >> a->studentInClass[i].List[j].minute_end;
            fint >> a->studentInClass[i].List[j].attendence;
        }
        fint >> a->studentInClass[i].dropped;//1-dau / 2 - rot
    }
}
void editAnAttendance(ifstream& fint, management_lecturer_schedule& tmp)
{
    cout << "Please input name of class you want to edit an attendence: "; string c; cin >> c;
    cout << "Please input name of course you want to edit an attendence: "; string b; cin >> b;
    string a = "Student";
    if (checkIfTheCourseAndClassBelongToYou(tmp, b, c))
    {
        cout << "Yeah that class and course belong to you." << endl;
        if (!findFile(fint, a, b, c))
        {
            cout << "Can not find file of course to see." << endl;
            return;
        }
        ifstream fint_;
        fint_.open(a);
        if (fint_.is_open())
        {
            your_class_and_course* d = new your_class_and_course;
            receivedAllStudentOfCourse(fint_, d);
            cout << "Please input the ID of student you want to edit an attendence: ";
            int ID; cin >> ID;
            for (int i = 0; i < d->numberOfStudent; i++)
            {
                if (d->studentInClass[i].ID == ID)
                {
                    for (int j = 0; j < 5; j++)//shoult 10
                    {
                        cout << d->studentInClass[i].List[j].day.year << "-";
                        if (d->studentInClass[i].List[j].day.month< 10)
                            cout << "0";
                        cout << d->studentInClass[i].List[j].day.month << "-";
                        if (d->studentInClass[i].List[j].day.day < 10)
                            cout << "0";
                        cout << d->studentInClass[i].List[j].day.day << " ";
                    }cout << endl;
                    for (int j = 0; j < 5; j++)//shoult 10
                    {
                        cout << "     ";
                        if (d->studentInClass[i].List[j].attendence == (-1))
                            cout << "X";
                        else
                            cout << "0";
                        cout << "    |";
                    }
                    cout << "\nWhich one you want to edit(2020 04 30): ";
                    int year, month, day; cin >> year >> month >> day;
                    for (int j = 0; j < 5; j++)//shoult 10
                    {
                        if (d->studentInClass[i].List[j].day.year == year
                            && d->studentInClass[i].List[j].day.month == month
                            && d->studentInClass[i].List[j].day.day == day)
                        {
                            if (d->studentInClass[i].List[j].attendence == 0)
                                d->studentInClass[i].List[j].attendence = -1;
                            else
                                d->studentInClass[i].List[j].attendence = 0;
                            fint_.close();
                            ofstream fout;
                            fout.open(a);
                            if (fout.is_open())
                            {
                                importAllStudentOfCourse(fout,d);
                                cout << "I had edit an attendence of that student.\n\n";
                            }
                            else
                                cout << "Can not open file of this course to import." << endl << endl;
                                break;
                        }if (j == 4)
                            cout << "Your date you just input is wrong." << endl << endl;
                    }
                    break;
                }
                if (i == d->numberOfStudent)
                    cout << "Your ID you just input is wrong.\n\n";
            }
            delete[] d->studentInClass;
            delete d;
        }
        else
            cout << "Can not open file of that course." << endl << endl;
        fint_.close();
    }
    else
        cout << "No that class not belong to you." << endl << endl;
}
void importAllStudentOfCourse(ofstream& fout, your_class_and_course* a)
{
    fout<< a->numberOfStudent<<endl;
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        fout << a->studentInClass[i].ID<<endl;
        fout << a->studentInClass[i].password << endl;
        fout<<a->studentInClass[i].your_name<<endl;
        fout << a->studentInClass[i].born.year << " ";
        if (a->studentInClass[i].born.month < 10)
            fout << "0";
        fout << a->studentInClass[i].born.month;
        fout << " ";
        if (a->studentInClass[i].born.day < 10)
            fout << "0";
        fout<< a->studentInClass[i].born.day<<endl;
        fout<< a->studentInClass[i].class_name<<endl;
        fout<< a->studentInClass[i].gen<<endl;
        fout<< a->studentInClass[i].activity<<endl;
        fout<< a->studentInClass[i].fifteen1 <<endl<< a->studentInClass[i].fifteen2
            <<endl<< a->studentInClass[i].midterm <<endl<< a->studentInClass[i].final<<endl;
        for (int j = 0; j < 10; j++)
        {
            fout << a->studentInClass[i].List[j].day.year;
            fout << " ";
            if (a->studentInClass[i].List[j].day.month < 10)
                fout << "0";
            fout << a->studentInClass[i].List[j].day.month << " ";
            if (a->studentInClass[i].List[j].day.day < 10)
                fout << "0";
            fout<< a->studentInClass[i].List[j].day.day << " ";
            fout<< a->studentInClass[i].List[j].h_start <<" "<< a->studentInClass[i].List[j].minute_start<< " ";
            fout<< a->studentInClass[i].List[j].h_end <<" "<< a->studentInClass[i].List[j].minute_end<<" ";
            fout<< a->studentInClass[i].List[j].attendence<<endl;
        }
        fout<< a->studentInClass[i].dropped<<endl;//1-dau / 2 - rot
    }
}
void importScoreboardOfCourse(ifstream& nameoffile, ifstream& fileCSV, management_lecturer_schedule tmp)
{
    cout << "Please input the name of class you want to import scoreboard of course: "; string a; cin >> a;
    cout << "Please input the name of course you want to import scoreboard of course: "; string b; cin >> b;
    string c = "Student";
    if (checkIfTheCourseAndClassBelongToYou(tmp, b, a))
    {
        cout << "Yeah that class and course belong to you." << endl;
        if (findFile(nameoffile, c, b, a))
        {
            ifstream fint3;
            fint3.open(c);
            if (!fint3.is_open())
                cout << "Can not open file course of that class.()\n\n";
            else
            {
                your_class_and_course* ImportScoreboard = nullptr; 
                receivedAllStudentOfCourse(fint3,ImportScoreboard);
                importScoreboard Scoreboard;
                receivedTheScoreboardFromCSV(fileCSV, Scoreboard);
                int count = 0; scoreboard* pTail = Scoreboard.student;
                for (scoreboard* cur = pTail; cur!=nullptr;cur= cur->pPrev)
                {
                    for (int j = 0; j<ImportScoreboard->numberOfStudent;j++)
                    {
                        if (cur->ID == ImportScoreboard->studentInClass[j].ID)
                        {
                            ImportScoreboard->studentInClass[j].fifteen1 = cur->midterm;
                            ImportScoreboard->studentInClass[j].fifteen2 = cur->final;
                            ImportScoreboard->studentInClass[j].midterm = cur->lab;
                            ImportScoreboard->studentInClass[j].final = cur->bonus;
                            count++;
                            break;
                        }
                    }
                } 
                fint3.close();
                ofstream fout;
                fout.open(c);
                if (fout.is_open())
                {
                    importAllStudentOfCourse(fout, ImportScoreboard);
                    cout << "Number of student in that scoreboard: " << Scoreboard.n << endl;
                    cout << "Successfully: " << count << endl;
                    cout << "Fail: " << Scoreboard.n - count << endl << endl;
                }
                else
                    cout << "Can not open again that file to fix.\n\n";
                deleteAlll(ImportScoreboard);
                deleteAllll(Scoreboard);
                fout.close();
                return;
            }
            fint3.close();
        }
        else
            cout << "Can not find file course of that class.()\n\n";
    }
    else
        cout << "That course and class not belong to you." << endl << endl;
}
void receivedTheScoreboardFromCSV(ifstream& filecsv, importScoreboard& a)
{
    char aa[50]; int support=-1; int tmp=-1;
    filecsv.getline(aa, 50, '\n');
    filecsv >> support;
    while (support!=0&&support!=tmp&&!filecsv.eof())
    {
        tmp = support;
        a.n++;
        if (a.student == nullptr)
            a.student = new scoreboard;
        else
        {
            a.student->pNext = new scoreboard;
            a.student->pNext->pPrev = a.student;
            a.student = a.student->pNext;
        }
        a.student->No = support;
        filecsv.get();
        filecsv >> a.student->ID;
        filecsv.get();
        filecsv.getline(aa, 30, ',');
        a.student->student_name = aa;
        filecsv.getline(aa, 5, ','); 
        a.student->midterm = aa;
        filecsv.getline(aa, 5, ',');
        a.student->final = aa; 
        filecsv.getline(aa, 5, ',');
        a.student->lab = aa; 
        filecsv.getline(aa, 5, '\n');
        a.student->bonus = aa;
        filecsv >> support;
    }
}
void viewScoreboard(ifstream& nameoffile, management_lecturer_schedule tmp)
{
    cout << "Please input the class name you want to see scoreboard: "; string a; cin >> a;
    cout << "Please input the course name you want to see scoreboard "; string b; cin >> b;
    string c = "Student";
    if (checkIfTheCourseAndClassBelongToYou(tmp, b, a))
    {
        cout << "Yeah that class and course belong to you." << endl;
        if (findFile(nameoffile, c, b, a))
        {
            ifstream fint3;
            fint3.open(c);
            if (!fint3.is_open())
                cout << "Can not open file course of that class.()\n\n";
            else
            {
                your_class_and_course* EditScoreboard = nullptr;
                receivedAllStudentOfCourse(fint3, EditScoreboard);
                seeScoreboard(EditScoreboard);
                deleteAlll(EditScoreboard);
            }
            fint3.close();
        }
        else
            cout << "Can not find file course of that class.()\n\n";
    }
    else
        cout << "That course and class not belong to you." << endl << endl;
}
void seeScoreboard(your_class_and_course* a)
{
    cout << setw(25); cout << " "; cout << "Miterm  Lab  Final  Bonus\n";
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        cout << left << setw(25) << a->studentInClass[i].your_name;
        cout << left << setw(8) << a->studentInClass[i].fifteen1;
        cout << left << setw(5) << a->studentInClass[i].fifteen2;
        cout << left << setw(7) << a->studentInClass[i].midterm;
        cout << a->studentInClass[i].final << endl;
    }
}
void editGradeOfStudents(ifstream& nameoffile, management_lecturer_schedule tmp)
{
    cout << "Please input the class name of student you want to edit: "; string a; cin >> a;
    cout << "Please input the course name of student you want to edit "; string b; cin >> b;
    string c = "Student";
    if (checkIfTheCourseAndClassBelongToYou(tmp, b, a))
    {
        cout << "Yeah that class and course belong to you." << endl;
        if (findFile(nameoffile, c, b, a))
        {
            ifstream fint3;
            fint3.open(c);
            if (!fint3.is_open())
                cout << "Can not open file course of that class.()\n\n";
            else
            {
                your_class_and_course* EditScoreboard = nullptr;
                receivedAllStudentOfCourse(fint3, EditScoreboard);
                cout << "ID of student you want to edit: "; int ID;//maybe use name
                cin >> ID;
                for (int i = 0; i < EditScoreboard->numberOfStudent; i++)
                {
                    if (EditScoreboard->studentInClass[i].ID == ID)
                    {
                        cout << "Name: " << EditScoreboard->studentInClass[i].your_name << endl;
                        cout << "Miterm  Lab  Final  Bonus\n";
                        cout << left << setw(8) << EditScoreboard->studentInClass[i].fifteen1;
                        cout << left << setw(5) << EditScoreboard->studentInClass[i].fifteen2;
                        cout << left << setw(7) << EditScoreboard->studentInClass[i].midterm;
                        cout << EditScoreboard->studentInClass[i].final << endl;
                        cout << "Input (Miterm Lab Final Bonus):"; 
                        cin >> EditScoreboard->studentInClass[i].fifteen1;
                        cin >> EditScoreboard->studentInClass[i].fifteen2;
                        cin >> EditScoreboard->studentInClass[i].midterm;
                        cin >> EditScoreboard->studentInClass[i].final;
                        fint3.close();
                        ofstream fout;
                        fout.open(c);
                        if (!fout.is_open())
                            cout << "Can not open file of class to edit.()\n\n";
                        else
                        {
                            importAllStudentOfCourse(fout, EditScoreboard);
                            cout << "The grade of student had been edit.()\n\n";
                        }fout.close();
                        break;
                    }
                    if (i == EditScoreboard->numberOfStudent - 1)
                        cout << "Can not find the student with that ID in class.\n\n";
                }
                deleteAlll(EditScoreboard);
            }
            fint3.close();
        }
        else
            cout << "Can not find file course of that class.()\n\n";
    }
    else
        cout << "That course and class not belong to you." << endl << endl;
}
bool findFile(ifstream& fint, string& a, string b, string c)
{
    string compare;
    /*if (a.length() < 5 || b.length() < 5 || c.length() < 5)
        return false;*/
    while (!fint.eof())
    {
        fint >> compare;
        if (compare.length() == 0)
            return false;
        if (check(compare, a) && check(compare, b) && check(compare, c))
        {
            a = compare; return true;
        }
    }
    return false;
}
bool check(string compare, string compare_)
{
    if (compare_.length() == 0 || compare.length() == 0)return true;
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
void viewAttendenceListOfCourse(ifstream& fint, management_lecturer_schedule a)
{
    cout << "Please input name of class you want to see: "; string c; cin >> c;
    cout << "Please input name of course you want to see: "; string b; cin >> b;
    string tmp = "Student";
    if (checkIfTheCourseAndClassBelongToYou(a, b, c))
    {
        if (!findFile(fint, tmp, b, c))
        {
            cout << "Can not find file of course to see." << endl;
            return;
        }
        ifstream fint_;
        fint_.open(tmp);
        if (fint_.is_open())
        {
            your_class_and_course* d = new your_class_and_course;
            receivedAllStudentOfCourse(fint_, d);
            outputListOfAttendenceOfCourse(d);
            delete[] d->studentInClass;
            delete d;
        }
    }
}
void outputListOfAttendenceOfCourse(your_class_and_course* a)
{
    cout << endl; cout << "X-Absent, 0-Present\n";
    if (a->numberOfStudent == 0) { cout << "Number of student in that course is zero.\n\n";return; }
    cout << left << setw(22) << "Name/Date";
    for (int i = 0; i < 5; i++)//10
    {
        cout << a->studentInClass[0].List[i].day.year << "-";
        if (a->studentInClass[0].List[i].day.month < 10) cout << "0";
        cout << a->studentInClass[0].List[i].day.month;
        cout << "-";
        if (a->studentInClass[0].List[i].day.day < 10)
            cout << "0";
        cout << a->studentInClass[0].List[i].day.day;
        if (i != 4)cout << " ";
        else cout << "|";
    }
    cout << endl; for (int i = 0; i < a->numberOfStudent; i++)
    {
        cout << left << setw(22) << a->studentInClass[i].your_name;
        for (int j = 0; j < 5; j++)//10
        {
            cout  << "      ";
            if (a->studentInClass[i].List[j].attendence == (-1))
                cout << "X";
            else cout << "0";
            cout << "   |";
        } cout << endl;
    } cout << endl;
}
void deleteAll(management_lecturer_schedule a)
{
    delete[] a.tmp; 
    your_class_and_course* cur = nullptr;
    while (a.yourClassAndCourse != nullptr)
    {
        cur = a.yourClassAndCourse->pNext;
        delete[] a.yourClassAndCourse->studentInClass;
        delete a.yourClassAndCourse;
        a.yourClassAndCourse = cur;
    }
}
void deleteAlll(your_class_and_course*& a)
{
    delete[] a->studentInClass; delete a;
}
void deleteAllll(importScoreboard& a)
{
    scoreboard* cur = a.student;
    while (cur != nullptr)
    {
        cur = cur->pNext;
        delete a.student;
        a.student = cur;
    }
}