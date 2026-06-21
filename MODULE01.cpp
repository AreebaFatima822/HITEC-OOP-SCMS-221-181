#include<iostream>
using namespace std;

class person
{
    protected:
    string name;
    int CNIC;
    int age;
    string contact;
    public:
    virtual void displayinfo() = 0;
    person(string a,int b,int c,string d)
    {
        name = a;
        CNIC = b;
        age = c;
        contact = d;
    }
    void input()
    {
        cout<<"Enter Name of Person: "<<endl;
        cin>>name;
        cout<<"Enter CNIC : "<<endl;
        cin>>CNIC;
        cout<<"Enter Age : "<<endl;
        cin>>age;
        cout<<"Enter Contact Number : "<<endl;
        cin>>contact;
    }
    void display()
{
    cout<<"Name : "<<name<<endl;
    cout<<"CNIC : "<<CNIC<<endl;
    cout<<"Age : "<<age<<endl;
    cout<<"Contact : "<<contact<<endl;
};
class student : public person
{
    private:
    string rollno;
    int semester;
    float gpa;
    int encourses[5];
    public:
    student(string a,int b,int c,string d,string e,int f,float g,int h) : person(a,b,c,d)
    {
        rollno = e;
        semester = f;
        gpa = g;
        for(int i=0;i<5;i++)
        {
            encourses[i]=0;
        }
        encourses [0] =h;
    }
    void studentinput()
    {
        person::input();
        cout<<"Enter Roll Number of Student : "<<endl;
        cin>>rollno;
        cout<<"Enter Semester : "<<endl;
        cin>>semester;
        cout<<"Enter GPA : "<<endl;
        cin>>gpa;
        cout<<"Enter enrollment courses : "<<endl;
        for(int i=0;i<5;i++)
        {
            cin>>encourses[i];
        }
    }
    void displaystudentinfo()
    {
        person::display();
        cout<<"Roll Number : "<<rollno<<endl;
        cout<<"Semester : "<<semester<<endl;
        cout<<"GPA : "<<gpa<<endl;
        cout<<"Enrollment Courses"<<endl;
        for(int i=0;i<5;i++)
        {
            cout<<encourses[i]<<endl;;
        }
    }
    void calculategrade()
    {
        if(gpa >= 3.5)
        {
            cout<<"A Grade."<<endl;
        }
        else if(gpa >= 3 && gpa <3.5)
        {
            cout<<"B Grade."<<endl;
        }
        else if (gpa >= 2.5 && gpa <3)
        {
            cout<<"C Grade."<<endl;
        }
        else if (gpa >= 2 && gpa <2.5)
        {
            cout<<"D Grade."<<endl;
        } 
        else
        {
            cout<<"F Grade."<<endl;
        }       
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
    faculity(string a,int b,int c,string d,int e,string f,string g,int h) : person(a,b,c,d)
    {
        empid=e;
        department=f;
        designation=g;
        asscourses=h;
    }
    void faculityinput()
    {
        person::input();
        cout<<"Enter Employee ID : "<<endl;
        cin>>empid;
        cout<<"Enter Department : "<<endl;
        cin>>department;
        cout<<"Enter Designation : "<<endl;
        cin>>designation;
        cout<<"Enter Number of Assigned Courses : "<<endl;
        cin>>asscourses;
        person::input();
    }
    void displayfaculityinfo()
    {
        person::display();
        cout<<"Employee ID : "<<empid<<endl;
        cout<<"Department : "<<department<<endl;
        cout<<"Designation : "<<designation<<endl;
        cout<<"Assigned Courses : "<<asscourses<<endl;
    }
};
class staff : public person
{
    private:
    int staffid;
    string role;
    float salary;
    public:
    staff(string a,int b,int c,string d,int e,string f,float g) : person(a,b,c,d)
    {
        staffid = e;
        role = f;
        salary = g;
    }
    void staffinput()
    {
        person::input();
        cout<<"Enter Staff ID : "<<endl;
        cin>>staffid;
        cout<<"Enter Role : "<<endl;
        cin>>role;
        cout<<"Enter Salary : "<<endl;
        cin>>salary;
        person::input();
    }
    void displaystaffinfo()
    {
        person::display();
        cout<<"Staff ID : "<<staffid<<endl;
        cout<<"Role : "<<role<<endl;
        cout<<"Salary : "<<salary<<endl;
    }
};
int main()
{
    person *P1 = new student("Rida",36104,19,"0317745","061",2,3.8,4);
    person *P2 = new faculity("Hajra",45267,15,"0313245",157,"computer science","Lecturer",2);
    person *P3 = new staff("Fatima",56791,23,"0315234",121,"Assistant",40000);

    P1->studentinput();
    P1->displaystudentinfo();
    cout<<endl;

    P2->faculityinput();
    P2->displayfaculityinfo();
    cout<<endl;

    P3->staffinput();
    P3->displaystaffinfo();

    return 0;

}
