#include<iostream>
#include<fstream>
#include<string>
using namespace std;

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
    virtual void displayInfo() const =0;
    int getItemId() const 
    {
        return itemID;
    }
    string getTitle() const
    {
        return title;
    }
    string getauthor() const
    {
        return author;
    }
    int getpublicationYear() const
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
    void displayInfo() const override
    {
        cout<<"Item ID is: "<<itemID<<endl;
        cout<<"The title of book is: "<<title<<endl;
        cout<<"The author of book is: "<<author<<endl;
        cout<<"The book was published in the year: "<<publicationYear<<endl;
        cout<<"ISBN is: "<<ISBN<<endl;
        cout<<"Genre of the book is: "<<genre<<endl;
        cout<<"The copies available are: "<<copiesAvailable<<endl;
    }
    int getCopiesAvailable() const
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
    void displayInfo() const override
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
    void displayCatalog() const
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
int main()
{
    Library library;
    
    library.addItem(new Book(101,"Object Oriented Programming","Bjarne Stroustrup",2018,"9780136152504","Programming",5));
    library.addItem(new Book(102,"Data Structures","Mark Weiss",2020,"9781292024475","Computer Science",3)); 
    library.addItem(new Journal(201,"Artificial Intelligence Review","John Smith",2024,"ISSN-56789",10,2));

    cout<<"LIBRARY CATALOG"<<endl;
    library.displayCatalog();
    
    cout<<endl;

    cout<<"SEARCH BY TITLE"<<endl;
    library.searchByTitle("Data Structures");
    
    cout<<endl; 

    cout<<"ISSUE ITEM"<<endl;
    library.issueItem(22, 101); 
    
    cout<<endl; 

    cout<<"SAVE CATALOG"<<endl;
    library.saveCatalog("library.txt");
    
    cout<<endl; 

    cout<<"LOAD CATALOG"<<endl;
    library.loadCatalog("library.txt");
    
    cout<<endl; 

    cout<<"RETURN ITEM"<<endl;

    try
    {
        library.returnItem(22, 101, 4);
    }
   catch (OverdueException e)
    {
    cout<<"Overdue item returned.\n";

    double fine=e.getFine();
    cout<<"Fine Amount: Rs. "<<fine<<endl;
    }
    return 0;
}







