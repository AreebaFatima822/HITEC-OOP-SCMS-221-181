#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CapacityExceededException
{
public:
    const char* what()
    {
        return "Course capacity exceeded!";
    }
};

class Student
{
private:
    int studentID;
    string name;

public:
    Student(int id, string n)
    {
        studentID = id;
        name = n;
    }

    int getStudentID()
    {
        return studentID;
    }

    string getName()
    {
        return name;
    }
};

class Faculty
{
private:
    int facultyID;
    string name;

public:
    Faculty(int id, string n)
    {
        facultyID = id;
        name = n;
    }

    string getName()
    {
        return name;
    }
};

class Course
{
private:
    string courseCode;
    string courseName;
    int creditHours;
    Faculty* instructor;
    int maxCapacity;
    int enrolledCount;

    vector<Student*> enrolledStudents;
    vector<Student*> waitingList;

public:
    Course(string code, string name, int credits,
           Faculty* inst, int capacity)
    {
        courseCode = code;
        courseName = name;
        creditHours = credits;
        instructor = inst;
        maxCapacity = capacity;
        enrolledCount = 0;
    }

    string getCourseCode()
    {
        return courseCode;
    }

    string getCourseName()
    {
        return courseName;
    }

    void enrollStudent(Student* s)
    {
        if (enrolledCount >= maxCapacity)
            throw CapacityExceededException();

        enrolledStudents.push_back(s);
        enrolledCount++;
    }

    void addToWaitingList(Student* s)
    {
        waitingList.push_back(s);
    }

    bool operator==(Course& other)
    {
        return courseCode == other.courseCode;
    }

    vector<Student*> operator+(Course& other)
    {
        vector<Student*> merged;

        int i;

        for(i = 0; i < waitingList.size(); i++)
            merged.push_back(waitingList[i]);

        for(i = 0; i < other.waitingList.size(); i++)
            merged.push_back(other.waitingList[i]);

        return merged;
    }

    friend ostream& operator<<(ostream& out, Course& c);
};

ostream& operator<<(ostream& out, Course& c)
{
    out << "Course Code: " << c.courseCode << endl;
    out << "Course Name: " << c.courseName << endl;
    out << "Credit Hours: " << c.creditHours << endl;
    out << "Instructor: " << c.instructor->getName() << endl;
    out << "Capacity: "
        << c.enrolledCount << "/"
        << c.maxCapacity << endl;

    return out;
}

class Enrollment
{
private:
    Student* student;
    Course* course;
    string enrollmentDate;
    string grade;

public:
    Enrollment(Student* s, Course* c,
               string date, string g)
    {
        student = s;
        course = c;
        enrollmentDate = date;
        grade = g;
    }

    void display()
    {
        cout << "\nEnrollment Details\n";
        cout << "Student: " << student->getName() << endl;
        cout << "Course: " << course->getCourseName() << endl;
        cout << "Date: " << enrollmentDate << endl;
        cout << "Grade: " << grade << endl;
    }
};

int main()
{
    Faculty f1(101, "Dr Ahmed");

    Student s1(1, "Hafsa");
    Student s2(2, "Rida");
    Student s3(3, "Sana");
    Student s4(4, "Fatima");

    Course c1("CS101", "Programming", 3, &f1, 2);
    Course c2("CS101", "Programming", 3, &f1, 3);

    if(c1 == c2)
        cout << "Courses are equal.\n";

    try
    {
        c1.enrollStudent(&s1);
        c1.enrollStudent(&s2);
        c1.enrollStudent(&s3);
    }
    catch(CapacityExceededException e)
    {
        cout << e.what() << endl;
    }

    c1.addToWaitingList(&s3);
    c2.addToWaitingList(&s4);

    vector<Student*> mergedList = c1 + c2;

    cout << "\nMerged Waiting List:\n";

    int i;
    for(i = 0; i < mergedList.size(); i++)
    {
        cout << mergedList[i]->getName() << endl;
    }

    cout << "\nCourse Information\n";
    cout << c1;

    Enrollment e1(&s1, &c1, "01-Sep-2025", "A");
    e1.display();

    return 0;
}
