#include <iostream>
#include <string>
using namespace std;

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

int main()
{
    HostelStudent s1(1, "Fatima");
    HostelStudent s2(2, "Hafsa");
    HostelStudent s3(3, "Zara");
    HostelStudent s4(4, "Rida");

    HostelManager manager("A Block");

    manager.allocateRoom(&s1, 102);
    manager.allocateRoom(&s2, 102);
    manager.allocateRoom(&s3, 102);
    manager.allocateRoom(&s4, 201);

    manager.generateReport();

    manager.vacateRoom(102, &s1);

    cout << "\nAfter Vacating:\n";

    manager.generateReport();

    return 0;
}
