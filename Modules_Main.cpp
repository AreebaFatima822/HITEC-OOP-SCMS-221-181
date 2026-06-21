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
