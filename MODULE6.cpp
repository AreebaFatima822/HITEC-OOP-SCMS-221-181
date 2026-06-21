#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Student
{
private:
    int studentID;
    string name;
public:
    Student(int id = 0, string n = "")
    {
        studentID = id;
        name = n;
    }

    string getName()
    {
        return name;
    }
};
class Person
{
public:
    virtual ~Person() {}
};

class Accommodation : virtual public Person
{
public:
    virtual void allocateRoom(Student* student, int roomNo) = 0;
    virtual void vacateRoom(int roomNo, Student* student) = 0;
};

class Reportable : virtual public Person
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
    Student* occupants[3];
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
        if (type == "Double")
            return 2;
        return 3;
    }

    bool addOccupant(Student* s)
    {
        if (occupantCount >= getCapacity())
            return false;

        occupants[occupantCount++] = s;
        return true;
    }

    bool removeOccupant(Student* s)
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

    Student* getOccupant(int index)
    {
        if (index >= 0 && index < occupantCount)
            return occupants[index];
        return NULL;
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
    Room* getRoom(int roomNo)
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
    Room* getRooms()
    {
        return rooms;
    }

    int getRoomCount()
    {
        return 5;
    }
};
class HostelManager : public Accommodation, public Reportable
{
private:
    HostelBlock block;

public:
    HostelManager(string blockName) : block(blockName)
    {
    }

    void allocateRoom(Student* student, int roomNo)
    {
        Room* room = block.getRoom(roomNo);

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
    void vacateRoom(int roomNo, Student* student)
    {
        Room* room = block.getRoom(roomNo);

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
    HostelBlock& getBlock()
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
    static void printHostelReport(HostelManager& manager)
    {
        Utils::printHeading("HOSTEL REPORT");
        manager.generateReport();
    }
    static void searchStudentByName(HostelManager& manager, string studentName)
    {
        Utils::printHeading("SEARCH STUDENT");

        HostelBlock& block = manager.getBlock();
        Room* rooms = block.getRooms();
        int roomCount = block.getRoomCount();

        bool found = false;

        for (int i = 0; i < roomCount; i++)
        {
            for (int j = 0; j < rooms[i].getOccupantCount(); j++)
            {
                Student* s = rooms[i].getOccupant(j);

                if (s != NULL && s->getName() == studentName)
                {
                    cout << studentName << " is in Room "
                         << rooms[i].getRoomNumber() << endl;
                    found = true;
                }
            }
        }

        if (!found)
            cout << "Student not found in hostel." << endl;
    }
    static void searchRoom(HostelManager& manager, int roomNo)
    {
        Utils::printHeading("SEARCH ROOM");

        HostelBlock& block = manager.getBlock();
        Room* room = block.getRoom(roomNo);

        if (room == NULL)
        {
            cout << "Room not found." << endl;
            return;
        }
        room->display();
    }
    static void showVacantRooms(HostelManager& manager)
    {
        Utils::printHeading("VACANT ROOMS");

        HostelBlock& block = manager.getBlock();
        Room* rooms = block.getRooms();
        int roomCount = block.getRoomCount();

        bool found = false;

        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].getOccupantCount() < rooms[i].getCapacity())
            {
                cout << "Room " << rooms[i].getRoomNumber()
                     << " has vacancy." << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No vacant rooms available." << endl;
    }
    static void saveHostelReportToFile(HostelManager& manager, string fileName)
    {
        ofstream fout(fileName.c_str());

        if (!fout)
        {
            cout << "File could not be opened." << endl;
            return;
        }

        HostelBlock& block = manager.getBlock();
        Room* rooms = block.getRooms();
        int roomCount = block.getRoomCount();

        fout << "HOSTEL REPORT" << endl;
        fout << "Block: " << block.getBlockName() << endl << endl;

        for (int i = 0; i < roomCount; i++)
        {
            fout << "Room: " << rooms[i].getRoomNumber() << endl;
            fout << "Type: " << rooms[i].getType() << endl;
            fout << "Floor: " << rooms[i].getFloor() << endl;
            fout << "Occupants: " << rooms[i].getOccupantCount()
                 << "/" << rooms[i].getCapacity() << endl;

            for (int j = 0; j < rooms[i].getOccupantCount(); j++)
            {
                Student* s = rooms[i].getOccupant(j);
                if (s != NULL)
                    fout << "   - " << s->getName() << endl;
            }

            fout << endl;
        }

        fout.close();
        cout << "Hostel report saved successfully." << endl;
    }
};
int main()
{
    Student s1(1, "Fatima");
    Student s2(2, "Hafsa");
    Student s3(3, "Zara");
    Student s4(4, "Rida");

    HostelManager manager("A Block");

    manager.allocateRoom(&s1, 102);
    manager.allocateRoom(&s2, 102);
    manager.allocateRoom(&s3, 102);  
    manager.allocateRoom(&s4, 201);

    Reports::printHostelReport(manager);

    Reports::searchStudentByName(manager, "Hafsa");

    Reports::searchRoom(manager, 201);

    Reports::showVacantRooms(manager);

    Reports::saveHostelReportToFile(manager, "HostelReport.txt");

    manager.vacateRoom(102, &s1);

    Reports::printHostelReport(manager);

    return 0;
}
