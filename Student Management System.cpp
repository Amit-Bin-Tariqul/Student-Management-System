// empl_io.cpp
// performs file I/O on user objects
// handles different sized objects
#include <fstream> //for file-stream functions
#include <iostream>
#include <typeinfo>  //for typeid()
#include <process.h> //for exit()
#include <fstream>
#include <cstring>
using namespace std;

const int LEN = 32;    // maximum length of last names
const int MAXEM = 100; // maximum number of users
enum user_type
{
    admin,
    faculty,
    student
};
////////////////////////////////////////////////////////////////
class user // user class
{
private:
    char name[LEN];       // user name
    unsigned long number; // user number
    static int n;         // current number of users
    static int m;
    static user *arrap[]; // array of ptrs to emps
                          // protected:
    static user *new_arrap[];
    char username[100], password[100];

public:
    user()
    {
        strcpy(username, " ");
        strcpy(password, " ");
    }
    user(char u[], char p[])
    {
        strcpy(username, u);
        strcpy(password, p);
    }
    virtual void getdata()
    {
        // cin.ignore(10, '\n');
        cout << " Enter Username[please avoid space] : ";
        cin >> username;
        cout << " Enter Password : ";
        cin >> password;
    }
    virtual void putdata()
    {
        cout << "\n Username : " << username;
        cout << "\n Password : " << password;
    }
    virtual user_type get_type(); // get type
    static void add();            // add an user
    static void display();        // display all users
    static void read();           // read from disk file
    static void new_read();
    static void write(); // write to disk file
    static void search_();
    static void edit();
};
//--------------------------------------------------------------
// static variables
int user::n;              // current number of users
user *user::arrap[MAXEM]; // array of ptrs to emps
int user::m;
user *user::new_arrap[MAXEM]; // array of ptrs to emps

////////////////////////////////////////////////////////////////
// Admin class
class Admin : public user
{
private:
    char title[LEN]; // "vice-president" etc.

public:
    void getdata()
    {
        user::getdata();

        cout << " Enter title : ";
        cin >> title;
        // cout << " Enter golf club dues : ";
        // cin >> dues;
    }
    void putdata()
    {
        user::putdata();
        cout << "\n Title : " << title;
        // cout << "\n Golf club dues : " << dues;
    }
};
////////////////////////////////////////////////////////////////
// Faculty class
class Faculty : public user
{
private:
    int pubs; // number of publications

public:
    void getdata()
    {
        user::getdata();
        cout << " Enter number of pubs : ";
        cin >> pubs;
    }
    void putdata()
    {
        user::putdata();
        cout << "\n Number of publications : " << pubs;
    }
};
////////////////////////////////////////////////////////////////
// Student class

class Course
{
private:
    char name[50], dept[50];
    double credit;
    int course_ID, semester;
    // char grade[5];
    // double attendence;

public:
    static Course *course[MAXEM];
    static int c;
    static void display_course();
    Course() {}
    // Course(char dp, int id, char n, double cr, double con, double at) : dept(dp), course_ID(id), name(n), credit(cr), semester(id / 100 % 10), attendence(at) {}

    void show_course_details()
    {
        cout << "Course dept : " << dept << '\n';
        cout << "Course ID : " << course_ID << '\n';
        cout << "Course Name : " << name << '\n';
        cout << "Course Semester : " << semester << '\n';
        cout << "Course Credit : " << credit << '\n';
    }

    void setdata()
    {

        cout << "Course ID : ";
        cin >> course_ID;
        // fflush(stdin);
        cout << "Course dept : ";
        cin >> dept;
        fflush(stdin);

        cout << "Course Name : ";
        cin >> name;
        fflush(stdin);

        cout << "Course Semester";
        fflush(stdin);

        cin >> semester;
        fflush(stdin);

        cout << "Course Credit : ";
        cin >> credit;
    }

    friend class Student;
    static void read_course();
    static void write_course();
    static void insert_course();
};
Course *Course::course[MAXEM];
int Course::c;
void Course::insert_course()
{

    char ch = 'y';
    while (1)
    {
        cout << "Enter Course information: " << endl;
        course[c] = new Course;
        course[c++]->setdata();
        // c++;
        cout << "Do you want to insert more courses?(y/n)" << endl;
        cin >> ch;
        if (ch == 'n')
            break;
    }
    write_course();
}

void Course::read_course()
{
    c = 0;
    long long int size; // size of user object
                        // user_type etype;    // type of user
    ifstream inf;       // open ifstream in binary
    inf.open("COURSE.DAT", ios::binary);
    if (!inf)
    {
        cout << "\nCan't open file\n";
        return;
    }

    while (true)
    {
        // read type of next user

        if (inf.eof()) // quit loop on eof
        {
            cout << "EOF\n";
            break;
        }
        // if (!inf) // error reading type
        // {
        //     cout << "\nCan't read type from file\n";
        //     return;
        // }
        size = sizeof(Course);
        inf.read((char *)course[c], size);
        if (!inf) // error but not eof
        {
            cout << "\nCan't read data from file\n";
            return;
        }
        c++; // count user
    }        // end while
    cout << "Reading " << c << " courses\n";
}

void Course::display_course()
{
    Course::read_course();
    int size = c;
    int i = 0;
    while (size--)
    {

        course[i]->show_course_details();
        i++;
    }
}
void Course::write_course()
{
    long long int size;
    cout << "Writing " << c << " courses.\n";
    ofstream ouf; // open ofstream in binary
    ouf.open("COURSE.DAT", ios::trunc | ios::binary);
    if (!ouf)
    {
        cout << "\nCan't open file\n";
        return;
    }
    for (int j = 0; j < c; j++) // for every user object
    {
        // get its type
        // write type to file

        size = sizeof(Course);

        cout << size << endl;
        ouf.write((char *)(course[j]), size);
        if (!ouf)
        {
            cout << "\nCan't write to file\n";
            return;
        }
    }
}

class reg_course
{
private:
    int id, sem, course_id;
    double credit, attendence, gpa;

public:
    static reg_course rc[MAXEM];
    static int rgc;
    static void read_reg_course();
    static void write_reg_course();

    reg_course() {}
    void set_reg_course()
    {
        cout << "Student ID :" << endl;
        cin >> id;
        cout << "Semester :" << endl;
        cin >> sem;
        cout << "Course ID :" << endl;
        cin >> course_id;
        cout << "Credit :" << endl;
        cin >> credit;
        cout << "Attendence :" << endl;
        cin >> attendence;
        cout << "GPA : " << endl;
        cin >> gpa;
    }
};
int reg_course::rgc=0;
reg_course reg_course::rc[MAXEM];
void reg_course::read_reg_course()
{
    long long int size; // size of user object
    ifstream inf;       // open ifstream in binary
    size=sizeof(reg_course);
    inf.open("REG.DAT", ios::binary);
    if (!inf)
    {
        cout << "\nCan't open file\n";
        return;
    }
   // rcg = 0; // no users in memory yet
    while (true)
    {
        // read type of next user
        
        if (inf.eof()) // quit loop on eof
            break;
        
        inf.read((char *)rc[rgc], size);
        if (!inf) // error but not eof
        {
            cout << "\nCan't read data from file\n";
            return;
        }
        rgc++; // count user
    }        // end while
    cout << "Reading " << rgc << " users\n";
}
void reg_course::write_reg_course()
{
    long long int size;
    cout << "Writing " << rgc << " regcourses.\n";
    ofstream ouf;    // open ofstream in binary
    user_type etype; // type of each user object
    ouf.open("REG.DAT", ios::trunc | ios::binary);
    if (!ouf)
    {
        cout << "\nCan't open file\n";
        return;
    }
    for (int j = 0; j < rgc; j++) // for every user object
    {
       
        cout << size << endl;
        ouf.write((char *)(rc[j]), size);
        if (!ouf)
        {
            cout << "\nCan't write to file\n";
            return;
        }
    }
}

//////////////
class Student : public user
{
    int ID, age, sem;
    char dob[50], name[50], address[500];
    double cgpa;
    Course *course[];

public:
    Student()
    {
        ID = 0;
        age = 0;
        sem = 0;
        dob[0] = ' ';
        name[0] = ' ';
        address[0] = ' ';
    }
    Student(char u[], char p[], int iden, char n[], int sm, char db[], char addr[]) : user(u, p), ID(iden), sem(sm)
    {
        strcpy(dob, db);
        strcpy(address, addr);
        strcpy(name, n);
    }
    // string getUsername()
    // {
    //     return username;
    // }
    // string getPassword()
    // {
    //     return password;
    // }
    void show_current_semester_details()
    {
        cout << "\t\t\tCurrent Semester Details of " << name << "\n";

        cout << "\t\t\tCurrent Semester : " << sem;
        switch (sem)
        {
        case 1:
            cout << "st\n\n";
            break;
        case 2:
            cout << "nd\n\n";
            break;
        case 3:
            cout << "rd\n\n";
            break;
        default:
            cout << "th\n\n";
            break;
        }

        // for (int i = 0; i < course_info[sem].size(); i++)
        // {
        //     // course_info[sem][i]->show_course_details();
        // }
    }
    void putdata()
    {
        user::putdata();
        cout << "\nStudent's  Name : ";
        cout << name << '\n';
        // cout << "Student's  Age  : ";
        // cout << age << '\n';
        cout << "Student's  ID   : ";
        cout << ID << '\n';
        cout << "Student's Current Semester : ";
        cout << sem << '\n';
        // cout << "Student's  Cgpa : ";
        // cout << cgpa << '\n';
        cout << "Student's  Address : ";
        cout << address << '\n';
        cout << "Student's  Dob : ";
        cout << dob << '\n';
    }
    void getdata()
    {
        user::getdata();
        fflush(stdin);
        cout << "Student's  Name : ";
        gets(name);
        fflush(stdin);
        cout << "Student's  ID   : ";
        cin >> ID;
        fflush(stdin);
        cout << "Student's Current Semester : ";
        cin >> sem;
        fflush(stdin);
        cout << "Student's  Address : ";
        gets(address);
        fflush(stdin);
        cout << "Student's  Dob : ";
        gets(dob);
        fflush(stdin);
    }
    void add_taken_courses(int total)
    {
        for (int i = 0; i < total; i++)
        {
            // if (course[i])
        }
    }
};

////////////////////////////////////////////////////////////////
// add user to list in memory
void user::add()
{
    char ch;
    cout << "'a' to add a Admin"
            "\n'f' to add a Faculty"
            "\n's' to add a Student"
            "\nEnter selection : ";
    cin >> ch;
    switch (ch)
    {
    // create specified user type
    case 'a':
        arrap[n] = new Admin;
        break;
    case 'f':
        arrap[n] = new Faculty;
        break;
    case 's':
        arrap[n] = new Student;
        break;
    default:
        cout << "\nUnknown user type\n";
        return;
    }
    arrap[n++]->getdata(); // get user data from user
}
//--------------------------------------------------------------
// search users
void user::search_()

{

    char name[100];
    cin >> name;
    int flag = 0;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(arrap[i]->username, name))
        {
            cout << "Found!!!" << endl;
            flag = 1;
            break;
        }
    }
    if (flag != 1)
        cout << "Not found!" << endl;
}
// display all users
void user::display()
{
    for (int j = 0; j < n; j++)
    {
        cout << (j + 1);              // display number
        switch (arrap[j]->get_type()) // display type
        {
        case admin:
            cout << ".Type : Admin";
            break;
        case faculty:
            cout << ".Type : Faculty";
            break;
        case student:
            cout << ".Type : Student";
            break;
        default:
            cout << ".Unknown type";
        }
        arrap[j]->putdata(); // display user data
        cout << endl;
    }
}
//--------------------------------------------------------------
// return the type of this object
user_type user::get_type()
{
    if (typeid(*this) == typeid(Admin))
        return admin;
    else if (typeid(*this) == typeid(Faculty))
        return faculty;
    else if (typeid(*this) == typeid(Student))
        return student;
    else
    {
        cerr << "\nBad user type";
        exit(1);
    }
    return admin;
}
//--------------------------------------------------------------
// write all current memory objects to file
void user::write()
{
    long long int size;
    cout << "Writing " << n << " users.\n";
    ofstream ouf;    // open ofstream in binary
    user_type etype; // type of each user object
    ouf.open("EMPLOY.DAT", ios::trunc | ios::binary);
    if (!ouf)
    {
        cout << "\nCan't open file\n";
        return;
    }
    for (int j = 0; j < n; j++) // for every user object
    {
        // get its type
        etype = arrap[j]->get_type();
        // write type to file
        ouf.write((char *)&etype, sizeof(etype));
        switch (etype) // find its size
        {
        case admin:
            size = sizeof(Admin);
            break;
        case faculty:
            size = sizeof(Faculty);
            break;
        case student:
            size = sizeof(Student);
            break;
        } // write user object to file
        cout << size << endl;
        ouf.write((char *)(arrap[j]), size);
        if (!ouf)
        {
            cout << "\nCan't write to file\n";
            return;
        }
    }
}
void user::edit()
{
    cout << "Enter username to edit : " << endl;
    char u[100];
    cin >> u;
    for (int i = 0; i < n; i++)
    {
        if (!strcmp(arrap[i]->username, u))
        {

            char pass[100];
            cout << "Enter the password : ";
            cin >> pass;
            int j;
            j = strcmp(arrap[i]->password, pass);
            if (j == 0)
            {
                cout << "Enter New Password :" << endl;
                cin >> pass;
                strcpy(arrap[i]->password, pass);
                return;
            }
            else
            {
                cout << "Wrong password" << endl;
                break;
            }
        }
    }
}
//--------------------------------------------------------------
// read data for all users from file into memory
void user::read()
{
    long long int size; // size of user object
    user_type etype;    // type of user
    ifstream inf;       // open ifstream in binary
    inf.open("EMPLOY.DAT", ios::binary);
    if (!inf)
    {
        cout << "\nCan't open file\n";
        return;
    }
    n = 0; // no users in memory yet
    while (true)
    {
        // read type of next user
        inf.read((char *)&etype, sizeof(etype));
        if (inf.eof()) // quit loop on eof
            break;
        if (!inf) // error reading type
        {
            cout << "\nCan't read type from file\n";
            return;
        }
        switch (etype)
        {
        // make new user
        case admin: // of correct type
            arrap[n] = new Admin;
            size = sizeof(Admin);
            break;
        case faculty:
            arrap[n] = new Faculty;
            size = sizeof(Faculty);
            break;
        case student:
            arrap[n] = new Student;
            size = sizeof(Student);
            break;
        default:
            cout << "\nUnknown type in file\n";
            return;
        } // read data from file into it
        inf.read((char *)arrap[n], size);
        if (!inf) // error but not eof
        {
            cout << "\nCan't read data from file\n";
            return;
        }
        n++; // count user
    }        // end while
    cout << "Reading " << n << " users\n";
}
////////////////////////////////////////////////////////////////

void user::new_read()
{
    long long int size; // size of user object
    user_type etype;    // type of user
    ifstream inf;       // open ifstream in binary
    inf.open("EMPLOY.DAT", ios::binary);
    if (!inf)
    {
        cout << "\nCan't open file\n";
        return;
    }
    m = 0; // no users in memory yet
    while (true)
    {
        // read type of next user
        inf.read((char *)&etype, sizeof(etype));
        if (inf.eof()) // quit loop on eof
            break;
        if (!inf) // error reading type
        {
            cout << "\nCan't read type from file\n";
            return;
        }
        switch (etype)
        {
        // make new user
        case admin: // of correct type
            new_arrap[m] = new Admin;
            size = sizeof(Admin);
            break;
        case faculty:
            new_arrap[m] = new Faculty;
            size = sizeof(Faculty);
            break;
        case student:
            new_arrap[m] = new Student;
            size = sizeof(Student);
            break;
        default:
            cout << "\nUnknown type in file\n";
            return;
        } // read data from file into it
        inf.read((char *)new_arrap[m], size);
        if (!inf) // error but not eof
        {
            cout << "\nCan't read data from file\n";
            return;
        }
        m++; // count user
    }        // end while
    for (int i = n; i < m + n; i++)
    {
        arrap[i] = new_arrap[i - n];
    }
    n = n + m;
    // cout << "Reading " << m << " users\n";
}
int main()
{
    char ch;
    // Course::insert_course();
    //  Course::display_course();
    // Course::read_course();
    while (true)
    {
        cout << "a -- add data for an user"
                "\n d -- display data for all users"
                "\n w -- write all user data to file"
                "\n r -- read all user data from file"
                "\n s -- to search specific data"
                "\n e -- to edit specific data"
                "\n x -- exit"
                "\nEnter selection: ";

        cin >> ch;
        switch (ch)
        {
        case 'a': // add an user to list
            user::add();
            break;
        case 'd': // display all users
            user::display();
            break;
        case 'w': // write users to file
            user::write();
            break;
        case 'r': // read all users from file
            user::new_read();
            user::read();
            break;
        case 's':
            user::search_();
            break;
        case 'e':
            user::edit();
            break;
        case 'x':
            exit(0); // exit program
        default:
            cout << "\nUnknown command";
        } // end switch
    }     // end while
    return 0;
} // end main()
