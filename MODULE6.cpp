#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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
ReportStudent s1(1, "Fatima");
ReportStudent s2(2, "Hafsa");
ReportStudent s3(3, "Zara");
ReportStudent s4(4, "Rida");


ReportHostelManager manager("A Block");

manager.allocateRoom(&s1, 102);
manager.allocateRoom(&s2, 102);
manager.allocateRoom(&s3, 102);
manager.allocateRoom(&s4, 201);

Reports::printHostelReport(manager);

Reports::searchStudentByName(manager, "Hafsa");

Reports::searchRoom(manager, 201);

Reports::showVacantRooms(manager);

Reports::saveHostelReportToFile(
    manager,
    "HostelReport.txt");

manager.vacateRoom(102, &s1);

Reports::printHostelReport(manager);

return 0;


}
