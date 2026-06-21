#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class CapacityExceededException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Course capacity exceeded! Cannot enroll more students.";
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

    int getStudentID() const
    {
        return studentID;
    }

    string getName() const
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

    string getName() const
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
    Course(string code, string name, int credits, Faculty* inst, int capacity)
    {
        courseCode = code;
        courseName = name;
        creditHours = credits;
        instructor = inst;
        maxCapacity = capacity;
        enrolledCount = 0;
    }

    string getCourseCode() const
    {
        return courseCode;
    }

    string getCourseName() const
    {
        return courseName;
    }

    int getCreditHours() const
    {
        return creditHours;
    }

    int getMaxCapacity() const
    {
        return maxCapacity;
    }

    int getEnrolledCount() const
    {
        return enrolledCount;
    }

    vector<Student*>& getWaitingList()
    {
        return waitingList;
    }

    void enrollStudent(Student* student)
    {
        if (enrolledCount >= maxCapacity)
            throw CapacityExceededException();

        enrolledStudents.push_back(student);
        enrolledCount++;
    }

    void addToWaitingList(Student* student)
    {
        waitingList.push_back(student);
    }

    bool operator==(const Course& other)
    {
        return courseCode == other.courseCode;
    }

    vector<Student*> operator+(Course& other)
    {
        vector<Student*> mergedList;

        for (auto s : waitingList)
            mergedList.push_back(s);

        for (auto s : other.waitingList)
            mergedList.push_back(s);

        return mergedList;
    }

    friend ostream& operator<<(ostream& out, const Course& c);
};

ostream& operator<<(ostream& out, const Course& c)
{
    out << "Course Code: " << c.courseCode << endl;
    out << "Course Name: " << c.courseName << endl;
    out << "Credit Hours: " << c.creditHours << endl;
    out << "Instructor: " << c.instructor->getName() << endl;
    out << "Capacity: " << c.enrolledCount << "/" << c.maxCapacity << endl;

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
    Enrollment(Student* s, Course* c, string date, string g = "")
    {
        student = s;
        course = c;
        enrollmentDate = date;
        grade = g;
    }

    void display()
    {
        cout << "Student: " << student->getName() << endl;
        cout << "Course: " << course->getCourseName() << endl;
        cout << "Enrollment Date: " << enrollmentDate << endl;
        cout << "Grade: " << grade << endl;
    }
};

int main()
{
    Faculty f1(101, "Dr. Ahmed");

    Student s1(1, "Hafsa");
    Student s2(2, "Hadia");
    Student s3(3, "Omama");
    Student s4(4, "Rida");

    Course c1("CS101", "Programming Fundamentals", 3, &f1, 2);
    Course c2("CS101", "Programming Fundamentals", 3, &f1, 3);

    if (c1 == c2)
        cout << "Courses are equal." << endl;

    try
    {
        c1.enrollStudent(&s1);
        c1.enrollStudent(&s2);
        c1.enrollStudent(&s3);
    }
    catch (CapacityExceededException& e)
    {
        cout << e.what() << endl;
    }

    c1.addToWaitingList(&s3);
    c2.addToWaitingList(&s4);

    vector<Student*> mergedList = c1 + c2;

    cout << "\nMerged Waiting List:\n";
    for (auto s : mergedList)
        cout << s->getName() << endl;

    cout << "\n" << c1 << endl;

    Enrollment e1(&s1, &c1, "2025-09-01", "A");
    e1.display();

    return 0;
}