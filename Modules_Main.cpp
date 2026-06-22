#include<iostream>
#include<string>
#include<fstream>
#include<vector>

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
class OverdueException
{
private:
    double fineAmount;
public:
    OverdueException(double fine)
    {
        fineAmount=fine;
    }

    double getFine() 
    {
        return fineAmount;
    }
};
class libraryItem
{
protected:
	int itemID;
	string title;
	string author;
	int publicationYear;

public:	
    libraryItem()
    {
        itemID=0;
        publicationYear=0;
    }
    libraryItem(int id, string t, string a, int year)
    {
        itemID=id;
        title=t;
        author=a;
        publicationYear=year;
    }
    virtual void checkout()=0;
    virtual void displayInfo()=0;
    int getItemId() 
    {
        return itemID;
    }
    string getTitle() 
    {
        return title;
    }
    string getauthor() 
    {
        return author;
    }
    int getpublicationYear() 
    {
        return publicationYear;
    }
};
class Book:public libraryItem
{
protected:
    string ISBN;
    string genre;
    int copiesAvailable;
    
public:
	Book()
    {
        copiesAvailable=0;
    }
    Book(int id, string t, string a, int year, string isbn, string g, int copies)
	    : libraryItem(id, t, a, year)
    {
        ISBN=isbn;
        genre=g;
        copiesAvailable=copies;
    }
    void checkout() override
    {
        if (copiesAvailable>0)
        {
            cout<<"Book issued successfully."<<endl;
        }
        else
        {
            cout<<"No copies are available."<<endl;
        }
    }
    void displayInfo() override
    {
        cout<<"Item ID is: "<<itemID<<endl;
        cout<<"The title of book is: "<<title<<endl;
        cout<<"The author of book is: "<<author<<endl;
        cout<<"The book was published in the year: "<<publicationYear<<endl;
        cout<<"ISBN is: "<<ISBN<<endl;
        cout<<"Genre of the book is: "<<genre<<endl;
        cout<<"The copies available are: "<<copiesAvailable<<endl;
    }
    int getCopiesAvailable() 
    {
        return copiesAvailable;
    }
    void increaseCopies()
    {
        copiesAvailable++;
    }
};
class Journal:public libraryItem
{
protected:
    string ISSN;
    int volume;
    int issueNumber;
public:
	Journal()
    {
    	volume=0;
        issueNumber=0;
    }
    Journal(int id, string t, string a, int year,string issn, int vol, int issue)
	: libraryItem(id, t, a, year)
    {
        ISSN=issn;
        volume=vol;
        issueNumber=issue;
    }
    void checkout() override
    {
        cout<<"Journal is checked out."<<endl;
    }
    void displayInfo() override
    {
        cout<<"The Item ID: "<<itemID<<endl;
        cout<<"The title is: "<<title<<endl;
        cout<<"Author is: "<<author<<endl;
        cout<<"Publication Year is: "<<publicationYear<<endl;
        cout<<"ISSN of journal is: "<<ISSN<<endl;
        cout<<"Volume: "<<volume<<endl;
        cout<<"Issue Number is: "<<issueNumber<<endl;
    }
};
struct IssuedItem
{
    int rollNo;
    int itemID;
};
class Library
{
private:
    libraryItem* catalog[100];
    int itemCount;

    IssuedItem issuedRecords[100];
    int issuedCount;

public:
    Library()
    {
        itemCount=0;
        issuedCount=0;
    }
    void addItem(libraryItem* item)
    {
        if(itemCount<100)
        {
            catalog[itemCount]=item;
            itemCount++;
        }
    }
    void displayCatalog() 
    {
        for (int i=0;i<itemCount;i++)
        {
            catalog[i]->displayInfo();
        }
    }
    void searchByTitle(string searchTitle)
    {
        bool found=false;

        for (int i=0;i<itemCount;i++)
        {
            if (catalog[i]->getTitle()==searchTitle)
            {
                catalog[i]->displayInfo();
                found = true;
            }
        }
        if (!found)
        {
            cout<<"Item was not found."<<endl;
        }
    }
    void issueItem(int rollNo, int itemID)
    {
        for (int i=0;i<itemCount;i++)
        {
            if (catalog[i]->getItemId()==itemID)
            {
                catalog[i]->checkout();

                issuedRecords[issuedCount].rollNo=rollNo;
                issuedRecords[issuedCount].itemID=itemID;
				issuedCount++;
                return;
            }
        }
        cout<<"Item ID was not found."<<endl;
    }
    void returnItem(int rollNo,int itemID,int overdueDays)
    {
        if (overdueDays>0)
        {
            double fine=overdueDays*50;
            throw OverdueException(fine);
        }
        cout<<"Item returned successfully."<<endl;
    }
    void saveCatalog(string fileName)
    {
        ofstream fout(fileName.c_str());

        if (!fout)
        {
            cout<<"File could not be opened."<<endl;
            return;
        }
        fout<<itemCount<<endl;
        for (int i=0;i<itemCount;i++)
        {
            fout<<catalog[i]->getItemId()<<endl;
            fout<<catalog[i]->getTitle()<<endl;
        }
        fout.close();
    }
    void loadCatalog(string fileName)
    {
        ifstream fin(fileName.c_str());

        if (!fin)
        {
            cout<<"File was not found."<<endl;
            return;
        }
        int totalItems;
        fin>>totalItems;
        cout<<"Catalog is loaded successfully."<<endl;
        fin.close();
    }
    ~Library()
    {
        for (int i=0;i<itemCount;i++)
        {
            delete catalog[i];
        }
    }	
};
class FeeRecord
{
    protected:
    string StudentRef;
    float SemesterFee;
    float HostelFee;
    float LibraryFine;
    float Totalpaid;
    float Balance;
    public:
    FeeRecord(string a=" ",float b=0,float c=0,float d=0,float e=0)
    {
        StudentRef =a;
        SemesterFee =b;
        HostelFee =c;
        LibraryFine =d;
        Totalpaid =e;
        Balance =SemesterFee + HostelFee + LibraryFine;
    }
    FeeRecord(const FeeRecord &F)
    {
        StudentRef =F.StudentRef;
        SemesterFee =F.SemesterFee;
        HostelFee =F.HostelFee;
        LibraryFine =F.LibraryFine;
        Totalpaid =F.Totalpaid;
        Balance =F.Balance;
    }
     FeeRecord &operator=(const FeeRecord &F)
    {
        StudentRef =F.StudentRef;
        SemesterFee =F.SemesterFee;
        HostelFee =F.HostelFee;
        LibraryFine =F.LibraryFine;
        Totalpaid =F.Totalpaid;
        Balance =F.Balance;
    }
    void operator-=(float Payment)
    {
        Totalpaid += Payment;
        Balance += Payment;

        if(Balance < 0)
        {
            Balance = 0;
        }
    }
    void display()
    {
        cout<<" Student Ref : "<<StudentRef<<endl;
        cout<<" Semester Fee : "<<SemesterFee<<endl;
        cout<<" Hostel Fee : "<<HostelFee<<endl;
        cout<<" Library Fine : "<<LibraryFine<<endl;
        cout<<" Total Paid : "<<Totalpaid<<endl;
        cout<<" Balance : "<<Balance<<endl; 
    }
};
class Invoice
{
    private:
    int invoiceid;
    string date;
    string *item;
    int items;
    float totalamount;
    static int invoicecounter;
    public:
    Invoice(string a, int b, double c)
    {
        invoicecounter++;
        invoiceid = invoicecounter;

        date = a;
        items = b;
        totalamount = c;

        item = new string[items];

        for (int i = 0; i < items; i++)
        {
            cout << "Enter Item " << i + 1 << ": ";
            cin >> item[i];
        }
    }
      void display()
    {
        cout << "Invoice ID : " << invoiceid<<endl;
        cout << "Date : " << date<<endl;

        cout << "Items:"<<endl;

        for (int i = 0; i < items; i++)
            cout << item[i] << endl;

        cout << "Total Amount : " << totalamount << endl;
    }

    static void showCounter()
    {
        cout <<"Total Invoices = "<< invoicecounter << endl;
    }

    ~Invoice()
    {
        delete[] item;
        cout << "Invoice " << invoiceid << " Destroyed";
    }
};

int Invoice::invoicecounter = 0;

class HostelStudent
{
private:
    int studentID;
    string name;

public:
    HostelStudent(int id = 0, string n = "")
    {
        studentID = id;
        name = n;
    }

    string getName()
    {
        return name;
    }

    int getID()
    {
        return studentID;
    }
};

class HostelBase
{
public:
    virtual ~HostelBase() {}
};

class Accommodation : virtual public HostelBase
{
public:
    virtual void allocateRoom(HostelStudent *student, int roomNo) = 0;
    virtual void vacateRoom(int roomNo, HostelStudent *student) = 0;
};

class Reportable : virtual public HostelBase
{
public:
    virtual void generateReport() = 0;
};

class Room
{
private:
    int roomNumber;
    string type;
    int floor;
    HostelStudent *occupants[3];
    int occupantCount;

public:
    Room(int rn = 0, string t = "Single", int f = 0)
    {
        roomNumber = rn;
        type = t;
        floor = f;
        occupantCount = 0;

        for (int i = 0; i < 3; i++)
            occupants[i] = NULL;
    }

    int getRoomNumber()
    {
        return roomNumber;
    }

    int getCapacity()
    {
        if (type == "Single")
            return 1;
        else if (type == "Double")
            return 2;
        else
            return 3;
    }

    bool addOccupant(HostelStudent *s)
    {
        if (occupantCount >= getCapacity())
            return false;

        occupants[occupantCount] = s;
        occupantCount++;
        return true;
    }

    bool removeOccupant(HostelStudent *s)
    {
        for (int i = 0; i < occupantCount; i++)
        {
            if (occupants[i] == s)
            {
                for (int j = i; j < occupantCount - 1; j++)
                    occupants[j] = occupants[j + 1];

                occupants[occupantCount - 1] = NULL;
                occupantCount--;
                return true;
            }
        }
        return false;
    }

    void display()
    {
        cout << "Room No: " << roomNumber
             << "  Type: " << type
             << "  Floor: " << floor
             << "  Occupancy: "
             << occupantCount << "/"
             << getCapacity() << endl;

        for (int i = 0; i < occupantCount; i++)
        {
            cout << "   Student: "
                 << occupants[i]->getName()
                 << endl;
        }
    }
};

class HostelBlock
{
private:
    string blockName;
    Room rooms[5];

public:
    HostelBlock(string name = "")
    {
        blockName = name;

        rooms[0] = Room(101, "Single", 1);
        rooms[1] = Room(102, "Double", 1);
        rooms[2] = Room(201, "Triple", 2);
        rooms[3] = Room(202, "Double", 2);
        rooms[4] = Room(301, "Single", 3);
    }

    Room *getRoom(int roomNo)
    {
        for (int i = 0; i < 5; i++)
        {
            if (rooms[i].getRoomNumber() == roomNo)
                return &rooms[i];
        }

        return NULL;
    }

    void displayRooms()
    {
        cout << "\nBlock Name: " << blockName << endl;

        for (int i = 0; i < 5; i++)
            rooms[i].display();
    }
};

class HostelManager : public Accommodation, public Reportable
{
private:
    HostelBlock block;

public:
    HostelManager(string blockName)
        : block(blockName)
    {
    }

    void allocateRoom(HostelStudent *student, int roomNo)
    {
        Room *room = block.getRoom(roomNo);

        if (room == NULL)
        {
            cout << "Room not found!" << endl;
            return;
        }

        if (room->addOccupant(student))
        {
            cout << student->getName()
                 << " allocated to Room "
                 << roomNo << endl;
        }
        else
        {
            cout << "Room is full!" << endl;
        }
    }

    void vacateRoom(int roomNo, HostelStudent *student)
    {
        Room *room = block.getRoom(roomNo);

        if (room == NULL)
        {
            cout << "Room not found!" << endl;
            return;
        }

        if (room->removeOccupant(student))
        {
            cout << student->getName()
                 << " vacated Room "
                 << roomNo << endl;
        }
        else
        {
            cout << "Student not found in room!" << endl;
        }
    }

    void generateReport()
    {
        cout << "\n===== HOSTEL REPORT =====\n";
        block.displayRooms();
    }
};
class ReportStudent
{
private:
int studentID;
string name;

public:
ReportStudent(int id = 0, string n = "")
{
studentID = id;
name = n;
}


string getName()
{
    return name;
}


};

class ReportPerson
{
public:
virtual ~ReportPerson() {}
};

class ReportAccommodation : virtual public ReportPerson
{
public:
virtual void allocateRoom(ReportStudent* student, int roomNo) = 0;
virtual void vacateRoom(int roomNo, ReportStudent* student) = 0;
};

class ReportReportable : virtual public ReportPerson
{
public:
virtual void generateReport() = 0;
};

class ReportRoom
{
private:
int roomNumber;
string type;
int floor;
ReportStudent* occupants[3];
int occupantCount;

public:
ReportRoom(int rn = 0, string t = "Single", int f = 0)
{
roomNumber = rn;
type = t;
floor = f;
occupantCount = 0;


    for (int i = 0; i < 3; i++)
        occupants[i] = NULL;
}

int getRoomNumber()
{
    return roomNumber;
}

int getCapacity()
{
    if (type == "Single")
        return 1;
    if (type == "Double")
        return 2;
    return 3;
}

bool addOccupant(ReportStudent* s)
{
    if (occupantCount >= getCapacity())
        return false;

    occupants[occupantCount++] = s;
    return true;
}

bool removeOccupant(ReportStudent* s)
{
    for (int i = 0; i < occupantCount; i++)
    {
        if (occupants[i] == s)
        {
            for (int j = i; j < occupantCount - 1; j++)
                occupants[j] = occupants[j + 1];

            occupants[occupantCount - 1] = NULL;
            occupantCount--;
            return true;
        }
    }
    return false;
}

void display()
{
    cout << "Room: " << roomNumber
         << " Type: " << type
         << " Floor: " << floor
         << " Occupants: " << occupantCount << "/"
         << getCapacity() << endl;

    for (int i = 0; i < occupantCount; i++)
        cout << "   - " << occupants[i]->getName() << endl;
}

string getType()
{
    return type;
}

int getFloor()
{
    return floor;
}

int getOccupantCount()
{
    return occupantCount;
}

ReportStudent* getOccupant(int index)
{
    if (index >= 0 && index < occupantCount)
        return occupants[index];

    return NULL;
}


};

class ReportHostelBlock
{
private:
string blockName;
ReportRoom rooms[5];

public:
ReportHostelBlock(string name = "")
{
blockName = name;


    rooms[0] = ReportRoom(101, "Single", 1);
    rooms[1] = ReportRoom(102, "Double", 1);
    rooms[2] = ReportRoom(201, "Triple", 2);
    rooms[3] = ReportRoom(202, "Double", 2);
    rooms[4] = ReportRoom(301, "Single", 3);
}

ReportRoom* getRoom(int roomNo)
{
    for (int i = 0; i < 5; i++)
    {
        if (rooms[i].getRoomNumber() == roomNo)
            return &rooms[i];
    }

    return NULL;
}

void displayRooms()
{
    cout << "\nBlock: " << blockName << endl;

    for (int i = 0; i < 5; i++)
        rooms[i].display();
}

string getBlockName()
{
    return blockName;
}

ReportRoom* getRooms()
{
    return rooms;
}

int getRoomCount()
{
    return 5;
}


};

class ReportHostelManager :
public ReportAccommodation,
public ReportReportable
{
private:
ReportHostelBlock block;

public:
ReportHostelManager(string blockName)
: block(blockName)
{
}


void allocateRoom(ReportStudent* student, int roomNo)
{
    ReportRoom* room = block.getRoom(roomNo);

    if (room == NULL)
    {
        cout << "Room not found.\n";
        return;
    }

    if (room->addOccupant(student))
        cout << student->getName()
             << " allocated to Room "
             << roomNo << endl;
    else
        cout << "Room is full.\n";
}

void vacateRoom(int roomNo, ReportStudent* student)
{
    ReportRoom* room = block.getRoom(roomNo);

    if (room == NULL)
    {
        cout << "Room not found.\n";
        return;
    }

    if (room->removeOccupant(student))
        cout << student->getName()
             << " vacated Room "
             << roomNo << endl;
    else
        cout << "Student not found in room.\n";
}

void generateReport()
{
    cout << "\nHostel Occupancy Report\n";
    block.displayRooms();
}

ReportHostelBlock& getBlock()
{
    return block;
}


};

class Utils
{
public:
static void printLine()
{
cout << "----------------------------------------" << endl;
}


static void printHeading(string heading)
{
    cout << endl;
    printLine();
    cout << heading << endl;
    printLine();
}


};

class Reports
{
public:
static void printHostelReport(ReportHostelManager& manager)
{
Utils::printHeading("HOSTEL REPORT");
manager.generateReport();
}


static void searchStudentByName(
    ReportHostelManager& manager,
    string studentName)
{
    Utils::printHeading("SEARCH STUDENT");

    ReportHostelBlock& block = manager.getBlock();
    ReportRoom* rooms = block.getRooms();

    bool found = false;

    for (int i = 0; i < block.getRoomCount(); i++)
    {
        for (int j = 0; j < rooms[i].getOccupantCount(); j++)
        {
            ReportStudent* s = rooms[i].getOccupant(j);

            if (s != NULL && s->getName() == studentName)
            {
                cout << studentName
                     << " is in Room "
                     << rooms[i].getRoomNumber()
                     << endl;

                found = true;
            }
        }
    }

    if (!found)
        cout << "Student not found in hostel." << endl;
}

static void searchRoom(
    ReportHostelManager& manager,
    int roomNo)
{
    Utils::printHeading("SEARCH ROOM");

    ReportRoom* room =
        manager.getBlock().getRoom(roomNo);

    if (room == NULL)
    {
        cout << "Room not found." << endl;
        return;
    }

    room->display();
}

static void showVacantRooms(
    ReportHostelManager& manager)
{
    Utils::printHeading("VACANT ROOMS");

    ReportHostelBlock& block = manager.getBlock();
    ReportRoom* rooms = block.getRooms();

    bool found = false;

    for (int i = 0; i < block.getRoomCount(); i++)
    {
        if (rooms[i].getOccupantCount()
            < rooms[i].getCapacity())
        {
            cout << "Room "
                 << rooms[i].getRoomNumber()
                 << " has vacancy."
                 << endl;

            found = true;
        }
    }

    if (!found)
        cout << "No vacant rooms available." << endl;
}

static void saveHostelReportToFile(
    ReportHostelManager& manager,
    string fileName)
{
    ofstream fout(fileName.c_str());

    if (!fout)
    {
        cout << "File could not be opened."
             << endl;
        return;
    }

    ReportHostelBlock& block = manager.getBlock();
    ReportRoom* rooms = block.getRooms();

    fout << "HOSTEL REPORT" << endl;
    fout << "Block: "
         << block.getBlockName()
         << endl << endl;

    for (int i = 0; i < block.getRoomCount(); i++)
    {
        fout << "Room: "
             << rooms[i].getRoomNumber()
             << endl;

        fout << "Type: "
             << rooms[i].getType()
             << endl;

        fout << "Floor: "
             << rooms[i].getFloor()
             << endl;

        fout << "Occupants: "
             << rooms[i].getOccupantCount()
             << "/"
             << rooms[i].getCapacity()
             << endl;

        for (int j = 0;
             j < rooms[i].getOccupantCount();
             j++)
        {
            ReportStudent* s =
                rooms[i].getOccupant(j);

            if (s != NULL)
                fout << "   - "
                     << s->getName()
                     << endl;
        }

        fout << endl;
    }

    fout.close();

    cout << "Hostel report saved successfully."
         << endl;
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
    cout << endl;
    P3->displayinfo();

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

    for(int i = 0; i < mergedList.size(); i++)
        cout << mergedList[i]->getName() << endl;

    cout << c1;

    Enrollment e1(&s1, &c1, "01-Sep-2025", "A");
    e1.display();

    Library library;

    library.addItem(new Book(101,"Object Oriented Programming","Bjarne Stroustrup",2018,"9780136152504","Programming",5));
    library.addItem(new Book(102,"Data Structures","Mark Weiss",2020,"9781292024475","Computer Science",3));
    library.addItem(new Journal(201,"Artificial Intelligence Review","John Smith",2024,"ISSN-56789",10,2));

    library.displayCatalog();
    library.searchByTitle("Data Structures");
    library.issueItem(22, 101);
    library.saveCatalog("library.txt");
    library.loadCatalog("library.txt");

    try
    {
        library.returnItem(22, 101, 4);
    }
    catch(OverdueException e)
    {
        cout << "Overdue item returned.\n";
        cout << "Fine Amount: Rs. " << e.getFine() << endl;
    }

    FeeRecord F1("25-CS-061",90000,30000,500);
    FeeRecord F2("25-CS-390",70000,30000,200);

    FeeRecord F3(F1);

    F1 -= 2000;
    F2 -= 4000;

    FeeRecord F4;
    F4 = F2;

    F1.display();
    F2.display();
    F3.display();
    F4.display();

    Invoice I1("1-June-2024",3,6400);
    I1.display();

    Invoice I2("10-Oct-2022",2,7800);
    I2.display();

    Invoice::showCounter();

    HostelStudent hs1(1, "Fatima");
    HostelStudent hs2(2, "Hafsa");
    HostelStudent hs3(3, "Zara");
    HostelStudent hs4(4, "Rida");

    HostelManager manager("A Block");

    manager.allocateRoom(&hs1, 102);
    manager.allocateRoom(&hs2, 102);
    manager.allocateRoom(&hs3, 102);
    manager.allocateRoom(&hs4, 201);

    manager.generateReport();

    manager.vacateRoom(102, &hs1);

    manager.generateReport();

    ReportStudent rs1(1, "Fatima");
    ReportStudent rs2(2, "Hafsa");
    ReportStudent rs3(3, "Zara");
    ReportStudent rs4(4, "Rida");

    ReportHostelManager reportManager("A Block");

    reportManager.allocateRoom(&rs1, 102);
    reportManager.allocateRoom(&rs2, 102);
    reportManager.allocateRoom(&rs3, 102);
    reportManager.allocateRoom(&rs4, 201);

    Reports::printHostelReport(reportManager);
    Reports::searchStudentByName(reportManager, "Hafsa");
    Reports::searchRoom(reportManager, 201);
    Reports::showVacantRooms(reportManager);
    Reports::saveHostelReportToFile(reportManager, "HostelReport.txt");

    reportManager.vacateRoom(102, &rs1);

    Reports::printHostelReport(reportManager);

    delete P1;
    delete P2;
    delete P3;

return 0;
}
