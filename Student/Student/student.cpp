#include"student.h"

void receivedInformationStudent(student& a)
{
    cout << "Your full name: ";
    char aa[50]; cin.getline(aa, 50, '\n');
    a.name = aa;
    cout << "Your ID: ";
    cin >> a.ID;
    cout << "Your class: "; 
    cin >> a.className;
    cout << "Year(2019-2020): ";
    cin.get();
    cin.getline(aa, 50, '\n');
    a.year = aa;
    cout << "Semester now: ";
    cin >> a.hk;
}
void checkIn(ifstream& nameOfFile, student HPK)
{
    cout << "Your course: "; string yourCourse; cin >> yourCourse;
    string a = "Student";
    if (findFile(nameOfFile, a, HPK.className, yourCourse))
    {
        cout << "Yeah. I had see file of your course.()I will check In for you.()\n";
        ifstream fileOfCourse;
        fileOfCourse.open(a);
        if (fileOfCourse.is_open())
        {
            your_class_and_course* tmp;
            tmp = new your_class_and_course;
            receivedAllStudentOfCourse(fileOfCourse, tmp);
            for (int i = 0; i < tmp->numberOfStudent; i++)
            {
                if (tmp->studentInClass[i].ID == HPK.ID)
                {
                    if (fixCheckIn(tmp->studentInClass[i], giveDateAndTime()))
                    {
                        ofstream fout;
                        fout.open(a);
                        if (fout.is_open()) {
                            importAllStudentOfCourse(fout, tmp);
                            cout << "Your check in had been store.()\n\n";
                        }
                        else
                            cout << "Can not open file of course to store again.()\n\n";
                        fout.close();
                    }
                    else
                        cout << "We can't check in for you.()Because you had out of time or wrong day.()\n\n";
                    break;
                }
                if (i == tmp->numberOfStudent - 1)
                    cout << "Your ID or course you put is wrong.()\n\n";
            }
            deleteAlll(tmp);
        }
        else
            cout << "Can not open that file to check In.()\n\n";
        fileOfCourse.close();
    }
    else
        cout << "I can't see your file.()\n\n";
}
void viewCheckInResult(ifstream& nameOfFile, student HPK)
{
    cout << "Your course: "; string yourCourse; cin >> yourCourse;
    string a = "Student";
    if (findFile(nameOfFile, a, HPK.className, yourCourse))
    {
        cout << "Yeah. I had see file of your course.()I will show for you.()\n";
        ifstream fileOfCourse;
        fileOfCourse.open(a);
        if (fileOfCourse.is_open())
        {
            your_class_and_course* tmp;
            tmp = new your_class_and_course;
            receivedAllStudentOfCourse(fileOfCourse, tmp);
            for (int i = 0; i < tmp->numberOfStudent; i++)
            {
                if (tmp->studentInClass[i].ID == HPK.ID)
                {
                    for (int j = 0; j < 5; j++)//10
                    {
                        cout << tmp->studentInClass[i].List[j].day.year << "-";
                        if (tmp->studentInClass[i].List[j].day.month < 10)
                            cout << "0";
                        cout << tmp->studentInClass[i].List[j].day.month << "-";
                        if (tmp->studentInClass[i].List[j].day.day < 10)
                            cout << "0";
                        cout << tmp->studentInClass[i].List[j].day.day << " ";
                    }cout << endl;
                    for (int j = 0; j < 5; j++)
                    {
                        cout << "     ";
                        if (tmp->studentInClass[i].List[j].attendence == (-1))
                            cout << "X";
                        else
                            cout << "0";
                        cout << "     ";
                    }cout << endl << endl;
                    break;
                }
                if(i==tmp->numberOfStudent-1)
                    cout << "Your ID or course you put is wrong.()\n\n";
            }
            deleteAlll(tmp);
        }
        else
            cout << "Can not open that file to show.()\n\n";
        fileOfCourse.close();
    }
    else
        cout << "I can't see your file.()\n\n";
}
void viewSchedules(ifstream& nameOfFile, student HPK)
{
    string a = "Schedule";
    if (findFile(nameOfFile, a, HPK.className, HPK.year))
    {
        cout << "Yeah. I had see file of your course.()I will show for you.()\n";
        ifstream fint;
        fint.open(a);
        if (fint.is_open())
        {
            studentsSchedule tmp;
            receivedAllCourse(fint, tmp);
            outputAllCourse(tmp, HPK.hk);
            delete[] tmp.allOfCourse;
        }
        else
            cout << "Can not open that file to show.()\n\n";
        fint.close();
    }
    else
        cout << "I can't see your file.()\n\n";
}
void viewScoreOfACourse(ifstream& nameOfFile, student HPK)
{
    string a = "Student";
    cout << "Name of course: "; string nameCourse;
    cin >> nameCourse;
    if (findFile(nameOfFile, a, nameCourse, HPK.className))
    {
        cout << "Yeah. I had see file of your course.()I will show for you.()\n";
        ifstream fint;
        fint.open(a);
        if (fint.is_open())
        {
            your_class_and_course* tmp;
            tmp = new your_class_and_course;
            receivedAllStudentOfCourse(fint, tmp);
            for (int i = 0; i < tmp->numberOfStudent; i++)
            {
                if (tmp->studentInClass[i].ID == HPK.ID)
                {
                    cout << "Your score: Midterm Final Lab Bonus\n";
                    cout << left << setw(12) << " ";
                    cout << left << setw(8) << tmp->studentInClass[i].fifteen1;
                    cout << left << setw(6) << tmp->studentInClass[i].fifteen2;
                    cout << left << setw(4) << tmp->studentInClass[i].midterm;
                    cout << tmp->studentInClass[i].final << endl << endl; break;
                }
                if(i == tmp->numberOfStudent-1)
                    cout << "Your ID or course you put is wrong.()\n\n";
            }
            deleteAlll(tmp);
        }
        else
            cout << "Can not open that file to show.()\n\n";
        fint.close();
    }
    else
        cout << "I can't see your file.()\n\n";
}
void receivedAllCourse(ifstream& fileOfSchedule, studentsSchedule& a)
{
    char aaa[50];
    fileOfSchedule >> a.numberOfCourse;
    fileOfSchedule >> a.nameClass;
    a.allOfCourse = new course[a.numberOfCourse];
    for (int i = 0; i < a.numberOfCourse; i++)
    {
        fileOfSchedule >> a.allOfCourse[i].hk;
        fileOfSchedule >> a.allOfCourse[i].nameCourse1;
        fileOfSchedule.get();
        fileOfSchedule.getline(aaa, 50, '\n');
        a.allOfCourse[i].nameCourse2 = aaa;
        fileOfSchedule.getline(aaa, 50,'\n');
        a.allOfCourse[i].nameLecturer = aaa;
        fileOfSchedule.getline(aaa, 50, '\n');
        a.allOfCourse[i].rank = aaa;
        fileOfSchedule >> a.allOfCourse[i].sex;
        fileOfSchedule >> a.allOfCourse[i].dateStart.year
            >> a.allOfCourse[i].dateStart.month
            >> a.allOfCourse[i].dateStart.day;
        fileOfSchedule >> a.allOfCourse[i].dateEnd.year
            >> a.allOfCourse[i].dateEnd.month
            >> a.allOfCourse[i].dateEnd.day;
        fileOfSchedule >> a.allOfCourse[i].firstDay
            >> a.allOfCourse[i].timeStart.h >> a.allOfCourse[i].timeStart.minute;
        fileOfSchedule >> a.allOfCourse[i].timeEnd.h
            >> a.allOfCourse[i].timeEnd.minute;
        fileOfSchedule.get();
        fileOfSchedule.getline(aaa, 50, '\n');
        a.allOfCourse[i].room = aaa;
    }
}
void outputAllCourse(studentsSchedule a, int hk)
{
    cout << endl;
    cout << a.nameClass << "   " << "HK" << hk << endl;
    for (int i = 0; i < a.numberOfCourse; i++)
    {
        if (a.allOfCourse[i].hk == hk)
        {
            cout << "Name of course: " << a.allOfCourse[i].nameCourse2 << endl;
            cout << "Lecturer: ";
            if (a.allOfCourse[i].sex == 0)
                cout << "Sir ";
            else
                cout << "Miss ";
            cout << a.allOfCourse[i].nameLecturer << endl;
            cout << "Firstday: ";
            switch (a.allOfCourse[i].firstDay)
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
                cout << "Thusday";
                break;
            case 6:
                cout << "Friday"; break;
            case 7:
                cout << "Staturday"; break;
            case 8:
                cout << "Sunday"; break;
            default:
                cout << "Can't read";
                break;
            }cout << endl;
            cout << "Rank: ";
            if (a.allOfCourse[i].rank == "TS")
                cout << "Doctor";
            else if (a.allOfCourse[i].rank == "GS")
                cout << "Professor";
            else
                cout << "Teacher";
            cout << endl;
            cout << "Date start: "; cout << a.allOfCourse[i].dateStart.year << "-";
            if (a.allOfCourse[i].dateStart.month < 10)
                cout << "0";
            cout << a.allOfCourse[i].dateStart.month << "-";
            if (a.allOfCourse[i].dateStart.month < 10)
                cout << "0";
            cout << a.allOfCourse[i].dateStart.day << endl;
            cout << "Date end: "; cout << a.allOfCourse[i].dateEnd.year << "-";
            if (a.allOfCourse[i].dateEnd.month < 10)
                cout << "0";
            cout << a.allOfCourse[i].dateEnd.month << "-";
            if (a.allOfCourse[i].dateEnd.day < 10)
                cout << "0";
            cout << a.allOfCourse[i].dateEnd.day << endl;
            cout << "Time start: ";
            cout << a.allOfCourse[i].timeStart.h << "h";
            if (a.allOfCourse[i].timeStart.minute < 10)
                cout << "0";
            cout << a.allOfCourse[i].timeStart.minute << endl;
            cout << "Time end: ";
            cout << a.allOfCourse[i].timeEnd.h << "h";
            if (a.allOfCourse[i].timeEnd.minute < 10)
                cout << "0";
            cout << a.allOfCourse[i].timeEnd.minute << endl;
            cout << "Room: " << a.allOfCourse[i].room << endl << endl;
        }
    }
}
void receivedAllStudentOfCourse(ifstream& fileCourse, your_class_and_course*& a)
{
    if (a == nullptr)
        a = new your_class_and_course;
    char tmp[50];
    fileCourse >> a->numberOfStudent;
    a->studentInClass = new student_course[a->numberOfStudent];
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        fileCourse >> a->studentInClass[i].ID;
        fileCourse.get();
        fileCourse.getline(tmp, 50, '\n');
        a->studentInClass[i].password = tmp;
        fileCourse.getline(tmp, 50, '\n');
        a->studentInClass[i].your_name = tmp;
        fileCourse >> a->studentInClass[i].born.year >> a->studentInClass[i].born.month
            >> a->studentInClass[i].born.day;
        fileCourse >> a->studentInClass[i].class_name;
        fileCourse >> a->studentInClass[i].gen;
        fileCourse >> a->studentInClass[i].activity;
        fileCourse >> a->studentInClass[i].fifteen1 >> a->studentInClass[i].fifteen2
            >> a->studentInClass[i].midterm >> a->studentInClass[i].final;
        for (int j = 0; j < 10; j++)
        {
            fileCourse >> a->studentInClass[i].List[j].day.year//dong mau xanh what mean? 
                >> a->studentInClass[i].List[j].day.month >> a->studentInClass[i].List[j].day.day;
            fileCourse >> a->studentInClass[i].List[j].h_start >> a->studentInClass[i].List[j].minute_start;
            fileCourse >> a->studentInClass[i].List[j].h_end >> a->studentInClass[i].List[j].minute_end;
            fileCourse >> a->studentInClass[i].List[j].attendence;
        }
        fileCourse >> a->studentInClass[i].dropped;//1-dau / 2 - rot
    }
}
void importAllStudentOfCourse(ofstream& fileCourse, your_class_and_course* a)
{
    fileCourse << a->numberOfStudent << endl;
    for (int i = 0; i < a->numberOfStudent; i++)
    {
        fileCourse << a->studentInClass[i].ID << endl;
        fileCourse << a->studentInClass[i].password << endl;
        fileCourse << a->studentInClass[i].your_name << endl;
        fileCourse << a->studentInClass[i].born.year << " ";
        if (a->studentInClass[i].born.month < 10)
            fileCourse << "0";
        fileCourse << a->studentInClass[i].born.month;
        fileCourse << " ";
        if (a->studentInClass[i].born.day < 10)
            fileCourse << "0";
        fileCourse << a->studentInClass[i].born.day << endl;
        fileCourse << a->studentInClass[i].class_name << endl;
        fileCourse << a->studentInClass[i].gen << endl;
        fileCourse << a->studentInClass[i].activity << endl;
        fileCourse << a->studentInClass[i].fifteen1 << endl << a->studentInClass[i].fifteen2
            << endl << a->studentInClass[i].midterm << endl << a->studentInClass[i].final << endl;
        for (int j = 0; j < 10; j++)
        {
            fileCourse << a->studentInClass[i].List[j].day.year;
            fileCourse << " ";
            if (a->studentInClass[i].List[j].day.month < 10)
                fileCourse << "0";
            fileCourse << a->studentInClass[i].List[j].day.month << " ";
            if (a->studentInClass[i].List[j].day.day < 10)
                fileCourse << "0";
            fileCourse << a->studentInClass[i].List[j].day.day << " ";
            fileCourse << a->studentInClass[i].List[j].h_start << " ";
            if (a->studentInClass[i].List[j].minute_start < 10) cout << "0";
            cout<< a->studentInClass[i].List[j].minute_start << " ";
            fileCourse << a->studentInClass[i].List[j].h_end << " ";
            if (a->studentInClass[i].List[j].minute_end < 10) cout << "0";
            cout<< a->studentInClass[i].List[j].minute_end << " ";
            fileCourse << a->studentInClass[i].List[j].attendence << endl;
        }
        fileCourse << a->studentInClass[i].dropped << endl;//1-dau / 2 - rot
    }
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
void deleteAlll(your_class_and_course*& a)
{
    delete[] a->studentInClass;
    delete a;
}
bool fixCheckIn(student_course& tmp, string a)
{
    timetime timeNow;
    date  dayNow;
    char c[20];
    c[0] = a[11];
    c[1] = a[12];
    c[2] = '\0';
    string d;
    d = c;
    timeNow.h = converStringToInteger(d);
    c[0] = a[14];
    c[1] = a[15];
    d = c;
    timeNow.minute = converStringToInteger(d);
    c[0] = a[8]; c[1] = a[9];
    d = c;
    dayNow.day = converStringToInteger(d);
    c[0] = a[20];
    c[1] = a[21];
    c[2] = a[22];
    c[3] = a[23];
    c[4] = '\0';
    d = c;
    dayNow.year = converStringToInteger(d);
    c[0] = a[4];
    c[1] = a[5];
    c[2] = a[6];
    c[3] = '\0';
    d = c;
    if (d == "Jan")
        dayNow.month = 1;
    else if (d == "Feb")
        dayNow.month = 2;
    else if (d == "Mar")
        dayNow.month = 3;
    else if (d == "Apr")
        dayNow.month = 4;
    else if (d == "May")
        dayNow.month = 5;
    else if (d == "Jun")
        dayNow.month = 6;
    else if (d == "Jul")
        dayNow.month = 7;
    else if (d == "Aug")
        dayNow.month = 8;
    else if (d == "Sep")
        dayNow.month = 9;
    else if (d == "Oct")
        dayNow.month = 10;
    else if (d == "Nov")
        dayNow.month = 11;
    else if (d == "Dec")
        dayNow.month = 12;
    else dayNow.month = 0;
    for (int i = 0; i < 10; i++)
    {
        if (tmp.List[i].day.day == dayNow.day && tmp.List[i].day.month == dayNow.month && tmp.List[i].day.year == dayNow.year)
        {
            if (timeNow.h<tmp.List[i].h_end && timeNow.h>tmp.List[i].h_start)
            {
                tmp.List[i].attendence = 0;
                return true;
            }
            if (timeNow.h == tmp.List[i].h_end)
            {
                if (timeNow.minute <= tmp.List[i].minute_end)
                {
                    tmp.List[i].attendence = 0;
                    return true;
                }
            }
            if (timeNow.h == tmp.List[i].h_start)
            {
                if (timeNow.minute >= tmp.List[i].minute_start)
                {
                    tmp.List[i].attendence = 0;
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}
int converStringToInteger(string a)
{
    int n;
    stringstream  result(a);
    result >> n;
    return n;
}
string giveDateAndTime()
{
    time_t result = time(NULL);
    char str[26];
    ctime_s(str, sizeof str, &result);
    string a = str;
    return a;
}