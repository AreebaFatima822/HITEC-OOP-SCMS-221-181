#include <iostream>
using namespace std;

class person
{
protected:
    string name;
    int CNIC;
    int age;
    string contact;

public:
    person(string a, int b, int c, string d)
    {
        name = a;
        CNIC = b;
        age = c;
        contact = d;
    }

    virtual void displayinfo() = 0;

    virtual void input()
    {
        cout << "Enter Name : ";
        cin >> name;

        cout << "Enter CNIC : ";
        cin >> CNIC;

        cout << "Enter Age : ";
        cin >> age;

        cout << "Enter Contact : ";
        cin >> contact;
    }

    void display()
    {
        cout << "Name : " << name << endl;
        cout << "CNIC : " << CNIC << endl;
        cout << "Age : " << age << endl;
        cout << "Contact : " << contact << endl;
    }

};

class student : public person
{
private:
    string rollno;
    int semester;
    float gpa;
    int encourses[5];

public:
    student(string a, int b, int c, string d,
            string e, int f, float g, int h)
        : person(a, b, c, d)
    {
        rollno = e;
        semester = f;
        gpa = g;

        for(int i=0;i<5;i++)
{
    encourses[i]=0;
}
encourses[0]=h;
    }

    void input()
    {
        person::input();

        cout << "Enter Roll Number : ";
        cin >> rollno;

        cout << "Enter Semester : ";
        cin >> semester;

        cout << "Enter GPA : ";
        cin >> gpa;

        cout << "Enter 5 Enrolled Courses : ";
        for (int i = 0; i < 5; i++)
            cin >> encourses[i];
    }

    void displayinfo()
    {
        person::display();

        cout << "Roll Number : " << rollno << endl;
        cout << "Semester : " << semester << endl;
        cout << "GPA : " << gpa << endl;

        cout << "Enrolled Courses : ";
        for (int i = 0; i < 5; i++)
            cout << encourses[i] << " ";

        cout << endl;

        calculategrade();
    }

    void calculategrade()
    {
        if (gpa >= 3.5)
            cout << "Grade : A" << endl;
        else if (gpa >= 3.0)
            cout << "Grade : B" << endl;
        else if (gpa >= 2.5)
            cout << "Grade : C" << endl;
        else if (gpa >= 2.0)
            cout << "Grade : D" << endl;
        else
            cout << "Grade : F" << endl;
    }
};

class faculity : public person
{
private:
    int empid;
    string department;
    string designation;
    int asscourses;

public:
    faculity(string a, long long b, int c, string d,
             int e, string f, string g, int h)
        : person(a, b, c, d)
    {
        empid = e;
        department = f;
        designation = g;
        asscourses = h;
    }

    void input()
    {
        person::input();

        cout << "Enter Employee ID : ";
        cin >> empid;

        cout << "Enter Department : ";
        cin >> department;

        cout << "Enter Designation : ";
        cin >> designation;

        cout << "Enter Assigned Courses : ";
        cin >> asscourses;
    }

    void displayinfo()
    {
        person::display();

        cout << "Employee ID : " << empid << endl;
        cout << "Department : " << department << endl;
        cout << "Designation : " << designation << endl;
        cout << "Assigned Courses : " << asscourses << endl;
    }
};

class staff : public person
{
private:
    int staffid;
    string role;
    float salary;

public:
    staff(string a, long long b, int c, string d,
          int e, string f, float g)
        : person(a, b, c, d)
    {
        staffid = e;
        role = f;
        salary = g;
    }

    void input()
    {
        person::input();

        cout << "Enter Staff ID : ";
        cin >> staffid;

        cout << "Enter Role : ";
        cin >> role;

        cout << "Enter Salary : ";
        cin >> salary;
    }

    void displayinfo()
    {
        person::display();

        cout << "Staff ID : " << staffid << endl;
        cout << "Role : " << role << endl;
        cout << "Salary : " << salary << endl;
    }
};

int main()
{
    person *P1 = new student("Rida", 36104, 19, "0317745", "061", 2, 3.8, 4);
    person *P2 = new faculity("Hajra", 45267, 35, "0313245", 157, "CS", "Lecturer", 2);
    person *P3 = new staff("Fatima", 56791, 23, "0315234", 121, "Assistant", 40000);

    
    P1->displayinfo();
    cout << endl;
   
    P2->displayinfo();
    cout<<endl;

    P3->displayinfo();


    return 0;
}

