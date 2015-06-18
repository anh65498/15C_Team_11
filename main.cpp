//test driver for bst course  tree
//rohan

#include "BinarySearchTree.h"  // BST ADT
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "CourseDatabase.h"
#include "HashedDictionary.h"
#include "LinkedList.h"


//const int TABLESIZE = 40;
//const int BUCKETSIZE = 10;
const int BUCKETSIZE = 20;

using namespace std;

void showMenu(BinarySearchTree<Course> * courseTree, HashedDictionary<string,Course> *hashTable,BinarySearchTree<Course> * secCourseTree);

// showTime: Prints the current date and time
void showTime()
{
    time_t rawtime;
		struct tm * timeinfo;	//use ctime to get current date and time
		char current[80] = "";
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(current, 80, "%m/%d/%Y %I:%M%p", timeinfo);	//format the date and time

		for (int i = 0; i < 80; i++)	//display date and time
			cout << current[i];
}

// display: function to pass to BST traverse functions
void display(string & anItem)
{
    cout << "Displaying item - " << anItem << endl;
}

// displayCourse: displays course ID and title
void displayCourse(Course & anItem)
{
    cout << setprecision(1) << fixed << anItem.getCourseid() << " "<<anItem.getTitle()<<endl;
}

// displayCourseWithLevel: displays course ID and title with indentation based on tree level
void displayCourseWithLevel(Course & anItem, int level)
{
    int maxwidth = 3; // width = level number + . + courseID = 7  ex: 1. 11707 = 8 chars
    for (int i = 0; i < level; i++)
    {
        for (int j = 0; j < maxwidth; j++)
            cout << " ";
    }

    cout << level + 1 << ".";
    cout << " " << anItem.getCourseid() << " "<<anItem.getTitle();
    cout << endl;
}

// displayKey:
void displayKey(string &s,Course &c)
{
    cout<<s<<" "<<c.getTitle()<<endl;
}
void displayItems(string &s,int spaces,int index,Course& c)
{


    if(index != -1)
    {
        if(s != "")
            s = s+" "+c.getTitle();
        cout<<"Index "<<index<<": "<<s<<endl;
    }
    else
    {
        string str = "Index :";
        str += index;

        int k = str.length();
        //k += c.getTitle().length();


        for(int i=0;i<spaces+k+1;i++)
        {
            cout<<" ";
        }
        cout<<s<<" "<<c.getTitle()<<endl;
    }

}


void printCourseToFile(Course & anItem, int level,ostream os)
{
    os << anItem;
}

void showOptions(bool developerMode){
    showTime();
    cout << endl << "* Course Database - Main Menu *" << endl;
    cout << "\n\tX - Search by Course ID" << endl;
    cout << "\tY - Search by Title" << endl;
    cout << "\tZ - Developer Menu";
    if(developerMode){
        cout << " (ON)" << endl << endl;
        cout << "Binary Search Tree" << endl;
        cout << "\tL - Print Sorted List " << endl;
		cout << "\tM - Breadth Traversal " << endl;
		cout << "\tN - Preorder Traversal " << endl;
		cout << "\tO - Inorder Traversal" << endl;
		cout << "\tP - Postorder Traversal" << endl;
        cout << "\tI - Print Tree as Indented List " << endl;
        cout << "\tB - BST Search " << endl;
        cout << "\tF - Print to File " << endl;
        cout << "\tA - Add Course " << endl;
        cout << "\tD - Delete Course " << endl;
        cout << "Hash Table" << endl;
        cout << "\tS - Display Statistics" << endl;
        cout << "\tT - Print Hash Table" << endl;
        cout << "\tU - Hash Table Search" << endl;
    }
    else cout << " (OFF)" << endl;
    cout << endl << "\tH - Help" << endl;
    cout << "\tQ - Quit" << endl;
}

void HASHstatistics( HashedDictionary<string,Course> *hashTable){
    int c = hashTable->getColissions();
    int full = hashTable->getNumOfFullBuckets();
    int empty = hashTable->getNumOfEmptyBuckets();

    cout<<"* Course Database - Statistics *"<<endl<<endl;
    cout<<"\tNumber of items:"<<hashTable->getItemCount()<<endl;
    cout<<"\tNumber of buckets:"<<hashTable->getBucketSize()<<endl;
    cout<<"\tSize of table:"<<hashTable->getTableSize()<<endl;
    cout<<"\tTotal number of Collisions: " << hashTable->getColissions() << endl;
    cout<<"\tLoad Factor: " << hashTable->getLoadFactor() << "%" << endl;
    cout<<"\tNumber of Full Buckets:  "<<full<<endl;
    cout<<"\tNumber of Empty Buckets:  "<<empty<<endl;
    cout<<"\tAverage Number of nodes stored per bucket: "<<hashTable->getAverageNumofNodes()<<endl;
    cout<<"\tOverflow: " << hashTable->getOverflow()<<endl;
}

void BSTprintFile(const BinarySearchTree<Course> * courseTree){
    cout << "Printing courses to courseout.txt" << endl;
    ofstream outfile;
    outfile.open("courseout.txt");
    courseTree->printToFile(outfile);
}

void BSTdeleteCourse(BinarySearchTree<Course> * courseTree, BinarySearchTree<Course> * secCourseTree, HashedDictionary <string, Course> * hashTable)
{
    cout<<"* Course Database - Delete Course *"<<endl<<endl;
    cout<<"Enter Course ID to delete :";
    string courseid;
    cin>>courseid;

    Course deleteCourse;
    deleteCourse.setCourseid(courseid);
    deleteCourse.setKey(courseid);

	Course foundcourse;
	if (!courseTree->getEntry(deleteCourse, foundcourse))
	{
		cout << "Failed to find course, cannot delete" << endl;
		return;
	}

    if(courseTree->remove(deleteCourse))
    {
        cout<<"Course "<<courseid<<" Deleted from BST"<<endl;
    }
	else
	{
		cout<<"Failed to delete Course: "<<courseid<<" from ID BST"<<endl;
	}

	deleteCourse.setTitle(foundcourse.getTitle());
	deleteCourse.setKey(foundcourse.getTitle());

	if (secCourseTree->remove(deleteCourse))
	{
		cout << "Course " << courseid << " Deleted from Title BST" << endl;
	}
	else
	{
		cout << "Failed to delete Course: " << courseid << " from Title BST" << endl;
	}

	if (hashTable->remove(courseid, deleteCourse))
	{
		cout << "Course " << courseid << " Deleted from Hash Table" << endl;
	}

	else
	{
		cout << "Failed to delete Course: " << courseid << " from Hash Table" << endl;
	}

}

void BSTAddCourse( BinarySearchTree<Course> * courseTree, BinarySearchTree<Course> * secCourseTree, HashedDictionary <string, Course> * hashTable)
{
    cout<<"* Course Database - Add Course *"<<endl<<endl;
    string courseid;
    string classkey;
    string title;
    string instructor;
    string days;
    string start_time;
    string end_time;
    string location;

    cout<<"Enter course ID(ex:00019): ";
    cin.ignore();
    getline(cin, courseid);

    cout<<"Enter class key(ex:ANTH001.02): ";
    getline(cin, classkey);

    cout<<"Enter title(ex:WOMEN IN LITERATURE): ";
    getline(cin, title);

    cout<<"Enter instructor(ex:Andrade, Claudia): ";
    getline(cin, instructor);

    cout<<"Enter days(ex:MTWRF): ";
    getline(cin, days);

    cout<<"Enter Start Time(ex:1000): ";
    getline(cin, start_time);

    cout<<"Enter End Time(ex:1225): ";
    getline(cin, end_time);

    cout<<"Enter location(ex:MLC102): ";
    getline(cin, location);
    cout << endl;


    Course c;
    c.setCourseid(courseid);
    c.setInstructor(instructor);
    c.setClassKey(classkey);
    c.setTitle(title);
    c.setLocation(location);
    c.setDays(days);
    c.setStartTime(start_time);
    c.setEndTime(end_time);
    c.setKey(courseid);
    cout<<"Adding course...\n";

    Course found;
    if(courseTree->getEntry(c,found))
    {
        cout<<"Course with this ID already exists, failed to add course."<<endl;
    }
    else
    {
        courseTree->insert(c);
        bool success = hashTable->add(courseid,c);
        if (!success){
                cout<<"Error adding new course! Please try again later."<<endl;
                return;
        }
        c.setKey(title);
        secCourseTree->insert(c);
        cout<<"Course added to BSTs and Hash Table."<<endl;
    }


}

void BSTprintSortedList(const BinarySearchTree<Course> * courseTree,const BinarySearchTree<Course> * secCourseTree)
{
    cout<<"* Course Database - Sort List *"<<endl<<endl;
    cout<<"Sort list by..." << endl;
    cout<<"\tX - Course ID"<<endl;
    cout<<"\tY - Title"<<endl;
    cout << endl << "Select an option (or 'Q' to return to menu): ";
    char input;
    cin>>input;
    while (!cin || (tolower(input)!='x' && tolower(input)!='y' && tolower(input)!='q'))
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again: ";
        cin >> input;
    }
    if(tolower(input)=='q') return;

    cout << endl;
    if(tolower(input) == 'x')
        courseTree->inOrder(displayCourse);
    else if(tolower(input) == 'y')
        secCourseTree->inOrder(displayCourse);
}

void BSTsearch(const BinarySearchTree<Course> * courseTree,const BinarySearchTree<Course> * secCourseTree){
    char searchoption;
    string courseid;
    cout<<"* Course Database - BST Search *"<<endl<<endl;
    cout<<"Search by..." << endl;
    cout<<"\tX - Course ID (BST)"<<endl;
    cout<<"\tY - Title (BST)"<<endl;
    //cout<<"H - HashTable "<<endl;
    cout << endl << "Select an option (or 'Q' to return to menu): ";
    cin.ignore();

    cin>>searchoption;
    while (!cin || (toupper(searchoption)!='X' && toupper(searchoption)!='Y' && toupper(searchoption)!='Q'))
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again: ";
        cin >> searchoption;
    }

    switch(toupper(searchoption))
    {
        case 'X':
        {
            bool done = false;
            do {
                cout << endl << "Enter Course ID (or 'Q' to return to menu): ";
                cin >> courseid;

                if (courseid == "Q" || courseid == "q")
                    done = true;
                else {
                    Course search(courseid);
                    search.setKey(courseid);
                    Course found;

                    bool success = courseTree->getEntry(search, found);
                    if (success)
                    {
                        cout << endl << "Course ID found: "  << "ID: " << found.getCourseid() << endl << "Title: " << found.getTitle() << endl;
                    }

                    else
                        cout << endl << "Invalid ID, try again." << endl;
                }

            } while (!done);

            break;
        }
        case 'Y':
        {
            string title;
            bool done = false;
            cin.clear();
            cin.ignore();
            do {
                cout << endl << "Enter Course Title (or 'Q' to return to menu): ";

                getline(cin,title);

                if (title == "Q" || title == "q")
                {
                    done = true;
                }

                else
                {
                    cout<<endl;
                    Course search;
                    search.setTitle(title);
                    search.setKey(title);
                    Course found;


                    LinkedList<Course> *searchList = secCourseTree->getEntries(search);


                    if(searchList->getCount() > 1)
                    {
                        cout<<"Multiple Courses Found"<<endl;
                    }
                    else if(searchList->getCount() == 1)
                    {
                        cout<<"Course Found"<<endl;
                    }
                    else
                        cout<<"Course Not Found"<<endl;

                    ListNode<Course> *nodePtr = searchList->getHead()->next;

                    for(int i=0;i<searchList->getCount();i++)
                    {
                        Course c = nodePtr->value;
                        cout<<c;
                        nodePtr = nodePtr->next;
                    }
                }
            } while (!done);

            break;
        }
    }
}

void BSTindentedPrint(const BinarySearchTree<Course> * courseTree){
    cout << endl;
    courseTree->print(displayCourseWithLevel);
    cout << endl;
}

void BSTbreadth(const BinarySearchTree<Course> * courseTree)
{
	cout << "- Breadth -" << endl;
	courseTree->levelOrder(displayCourse);
}

void BSTpreOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "- Preorder -" << endl;
	courseTree->preOrder(displayCourse);
}

void BSTinOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "- Inorder -" << endl;
	courseTree->inOrder(displayCourse);
}

void BSTpostOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "- Postorder -" << endl;
	courseTree->postOrder(displayCourse);
}

void HashPrint(const HashedDictionary<string, Course> *hashTable)
{
    char input;
    cout<<"* Course Database - Hash Table Print *"<<endl<<endl;
    cout<<"Print table by..."<<endl;
    cout<<"\tF - Full Table"<<endl;
    cout<<"\tI - Items"<<endl;

    cout << endl << "Select an option (or 'Q' to return to menu): ";
    cin>>input;

    while (!cin || (tolower(input)!='f' && tolower(input)!='i' && tolower(input)!='q'))
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again: ";
        cin >> input;
    }
    if (tolower(input) == 'q') return;

    cout << endl;
    if(tolower(input) == 'f')
    {
        hashTable->printHashTable(displayItems);
    }
    else if (tolower(input) == 'i')
    {
        hashTable->displayHashTableList(displayKey);
    }


}

void USERsearch(const BinarySearchTree<Course> * courseTree,const BinarySearchTree<Course> * secCourseTree,char key)
{
    char searchoption = key;
    string courseid;
    switch(toupper(searchoption))
    {
        case 'X':
        {
            cout<<"* Course Database - ID Search *"<<endl;
            bool done = false;
            do {
                cout << endl << "Enter Course ID (or 'Q' to return to menu): ";
                cin >> courseid;
                if (courseid == "Q" || courseid == "q")
                    done = true;
                else {
                    Course search(courseid);
                    search.setKey(courseid);
                    Course found;
                    bool success = courseTree->getEntry(search, found);
                    if (success)
                    {
                        cout << endl << "Course ID found: "  << "ID: " << found.getCourseid() << endl << "Title: " << found.getTitle() << endl;
                    }
                    else
                        cout << endl << "Invalid ID, try again." << endl;
                }

            } while (!done);

            break;
        }
        case 'Y':
        {
            cout<<"* Course Database - Title Search *"<<endl;
            string title;
            bool done = false;
            cin.clear();
            cin.ignore();
            do {
                cout << endl << "Enter Course Title (or 'Q' to return to menu): ";
                getline(cin,title);
                if (title == "Q" || title == "q")
                {
                    done = true;
                }
                else
                {
                    cout << endl;
                    Course search;
                    search.setTitle(title);
                    search.setKey(title);
                    Course found;
                    LinkedList<Course> *searchList = secCourseTree->getEntries(search);
                    if(searchList->getCount() > 1)
                    {
                        cout<<"Multiple Courses Found"<<endl;
                    }
                    else if(searchList->getCount() == 1)
                    {
                        cout<<"Course Found"<<endl;
                    }
                    else
                        cout<<"Course Not Found"<<endl;
                    ListNode<Course> *nodePtr = searchList->getHead()->next;
                    for(int i=0;i<searchList->getCount();i++)
                    {
                        Course c = nodePtr->value;
                        cout<<c;
                        nodePtr = nodePtr->next;
                    }
                }
            } while (!done);
            break;
        }
    }
}

void HashSearch(const HashedDictionary<string, Course> *hashTable)
{
    cout<<"* Course Database - Hash Search *"<<endl;
    string courseid;
    bool done = false;
    do {
        cout << endl<<"Enter Course ID (or 'Q' to return to menu): ";
        cin >> courseid;

        if (courseid == "Q" || courseid == "q")
            done = true;
        else {
            cout << endl;
            Course search(courseid);
            search.setKey(courseid);
            Course *found;

            //bool success = hashTable->getEntry(search, found);
            found = hashTable->getItem(courseid);
            if (found != 0)
            {
                cout << "Course ID found: "  << "ID: " << found->getCourseid() << endl << "Title: " << found->getTitle() << endl;
            }

            else
                cout << "Invalid ID, try again." << endl;
        }

    } while (!done);
}

// showMenu: Prints the selection of choices for the user
void showMenu(CourseDB db)
{
    bool done = false;
    bool developerMode = false;
    char option;
    string courseid;
    cout << "\nWelcome to the Summer 2015 De Anza Course Database" << endl<<endl;

    showOptions(developerMode);
    do{
        cout << "\nSelect an option: ";
        cin >> option;
        while (!cin)
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Enter 'H' to see the menu again.";
            cout << "\nSelect an option: ";
            cin >> option;
        }
        cout<<endl;
        switch (toupper(option)){
            case 'X':USERsearch(db.getTree(),db.getSecTree(),option);break;
            case 'Y':USERsearch(db.getTree(),db.getSecTree(),option);break;
            case 'Z':developerMode = !developerMode; showOptions(developerMode);break;

            case 'L':BSTprintSortedList(db.getTree(),db.getSecTree());break;
			case 'M':BSTbreadth(db.getTree()); break;
			case 'N':BSTpreOrder(db.getTree()); break;
			case 'O':BSTinOrder(db.getTree()); break;
			case 'P':BSTpostOrder(db.getTree()); break;
            case 'I':BSTindentedPrint(db.getTree());break;
            case 'B':BSTsearch(db.getTree(),db.getSecTree());break;
            case 'F':BSTprintFile(db.getTree());break;
            case 'A':BSTAddCourse(db.getTree(),db.getSecTree(), db.getHash());break;
            case 'D':BSTdeleteCourse(db.getTree(), db.getSecTree(), db.getHash());break;

            //case 'P': db.getHash()->displayHashTableList(displayKey);
            case 'S':HASHstatistics(db.getHash());break;
                //case 'B':BSTbreadthFirst(db.getTree());break;
            case 'T':HashPrint(db.getHash());break;
            case 'U':HashSearch(db.getHash());break;

            case 'H':showOptions(developerMode);break;
            case 'Q':done = true;BSTprintFile(db.getTree());break;

            default:cout << "Invalid input. Enter 'H' to see the menu again." << endl;cin.clear();break;
        }

    } while (!done);
}
int main()
{
    CourseDB db("courses.txt",BUCKETSIZE);
    // sample usage of rehashing

   // db.rehashHashTable(db.getHash(),301, 1000);
    showMenu(db);

    return 0;
}
