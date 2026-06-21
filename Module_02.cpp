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

class CourseStudent
{
private:
int studentID;
string name;

public:
CourseStudent(int id, string n)
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

class CourseFaculty
{
private:
int facultyID;
string name;

public:
CourseFaculty(int id, string n)
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
CourseFaculty* instructor;
int maxCapacity;
int enrolledCount;

vector<CourseStudent*> enrolledStudents;
vector<CourseStudent*> waitingList;


public:
Course(string code, string name, int credits,
CourseFaculty* inst, int capacity)
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

void enrollStudent(CourseStudent* s)
{
    if (enrolledCount >= maxCapacity)
        throw CapacityExceededException();

    enrolledStudents.push_back(s);
    enrolledCount++;
}

void addToWaitingList(CourseStudent* s)
{
    waitingList.push_back(s);
}

bool operator==(Course& other)
{
    return courseCode == other.courseCode;
}

vector<CourseStudent*> operator+(Course& other)
{
    vector<CourseStudent*> merged;

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
CourseStudent* student;
Course* course;
string enrollmentDate;
string grade;

public:
Enrollment(CourseStudent* s, Course* c,
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
CourseFaculty f1(101, "Dr Ahmed");


CourseStudent s1(1, "Hafsa");
CourseStudent s2(2, "Rida");
CourseStudent s3(3, "Sana");
CourseStudent s4(4, "Fatima");

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

vector<CourseStudent*> mergedList = c1 + c2;

cout << "\nMerged Waiting List:\n";

for(int i = 0; i < mergedList.size(); i++)
{
    cout << mergedList[i]->getName() << endl;
}

cout << "\nCourse Information\n";
cout << c1;

Enrollment e1(&s1, &c1, "01-Sep-2025", "A");
e1.display();

return 0;


}
