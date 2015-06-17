//test driver for bst course  tree
//rohan

#include "BinarySearchTree.h"  // BST ADT
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "CourseDatabase.h"
#include "HashedDictionary.h"
#include "LinkedList.h"


//const int TABLESIZE = 40;
//const int BUCKETSIZE = 10;
const int BUCKETSIZE = 20;

using namespace std;

void showMenu(BinarySearchTree<Course> * courseTree, HashedDictionary<string,Course> *hashTable,BinarySearchTree<Course> * secCourseTree);

// display: function to pass to BST traverse functions
void display(string & anItem)
{
    cout << "Displaying item - " << anItem << endl;
}

// displayStudent: displays the student IDs
void displayCourse(Course & anItem)
{
    cout << setprecision(1) << fixed << anItem.getCourseid() << " "<<anItem.getTitle()<<endl;
}

// displayStudentWithLevel: displays the student IDs with the correct spacing and level number for print function
void displayCourseWithLevel(Course & anItem, int level)
{
    int maxwidth = 3; // width = level number + . + studentID = 7  ex: 1. 1900 = 7 chars
    for (int i = 0; i < level; i++)
    {
        for (int j = 0; j < maxwidth; j++)
            cout << " ";
    }
    
    cout << level + 1 << ".";
    cout << " " << anItem.getCourseid() << " "<<anItem.getTitle();
    cout << endl;
}

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
    cout << "\nZ - Developer Mode" << endl<<endl;
    if(developerMode){
        cout << "Binary Search Tree" << endl;
        cout << "\tB - Print Sorted List " << endl;
		cout << "\tL - Breadth Traversal " << endl;
		cout << "\tM - Preorder Traversal " << endl;
		cout << "\tN - Inorder Traversal" << endl;
		cout << "\tO - Postorder Traversal" << endl;
        cout << "\tT - Print Tree as Indented List " << endl;
        cout << "\tS - Search " << endl;
        cout << "\tF - Print to File " << endl;
        cout << "\tA - Add Course " << endl;
        cout << "\tX - Delete Course " << endl;
        cout << "Hash Table" << endl;
        cout << "\tC - Display Collisions" << endl;
        cout << "\tP - Print Hash table" << endl;
        cout << "\tD - Search" << endl;

    }
    cout << "H - Help" << endl;
    cout << "Q - Quit" << endl;
}

void HASHstatistics( HashedDictionary<string,Course> *hashTable){
    int c = hashTable->getColissions();
    int full = hashTable->getNumOfFullBuckets();
    int empty = hashTable->getNumOfEmptyBuckets();
    
    cout<<endl<<"\tStatistics:"<<endl;
    cout<<"\tNumber of items:"<<hashTable->getItemCount()<<endl;
    cout<<"\tNumber of buckets:"<<hashTable->getBucketSize()<<endl;
    cout<<"\tSize of table:"<<hashTable->getTableSize()<<endl;
    cout<<"\tTotal number of Collisions: " << hashTable->getColissions() << endl;
    cout<<"\tLoad Factor: " << hashTable->getLoadFactor() << "%" << endl;
    cout<<"\tNumber of Full Buckets:  "<<full<<endl;
    cout<<"\tNumber of Empty Buckets:  "<<empty<<endl;
    cout<<"\tAverage Number of nodes stored per bucket: "<<hashTable->getAverageNumofNodes()<<endl;
    cout<<"\tOverflow: 0" << endl;
    cout << endl;
}

void BSTprintFile(const BinarySearchTree<Course> * courseTree){
    cout << "Printing courses to courseout.txt" << endl;
    ofstream outfile;
    outfile.open("courseout.txt");
    courseTree->printToFile(outfile);
}

void BSTdeleteCourse(BinarySearchTree<Course> * courseTree, BinarySearchTree<Course> * secCourseTree, HashedDictionary <string, Course> * hashTable)
{
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
    string courseid;
    string crn;
    string title;
    string instructor;
    string days;
    string start_time;
    string end_time;
    string location;
    
    bool done = false;
    
    do {
        
        cout<<"Enter courseid :";
        cin.ignore();
        getline(cin, courseid);
        
        cout<<"Enter crn :";
        getline(cin, crn);
        
        cout<<"Enter Title :";
        getline(cin, title);
        
        
        cout<<"Enter instructor :";
        getline(cin, instructor);
        
        cout<<"Enter days :";
        getline(cin, days);
        
        cout<<"Enter Start Time :";
        getline(cin, start_time);
        
        cout<<"Enter End Time :";
        getline(cin, end_time);
        
        cout<<"Enter location :";
        getline(cin, location);
        
        
        Course c;
        c.setCourseid(courseid);
        c.setInstructor(instructor);
        c.setCrn(crn);
        c.setTitle(title);
        c.setLocation(location);
        c.setDays(days);
        c.setStartTime(start_time);
        c.setEndTime(end_time);
        c.setKey(courseid);
        cout<<"Adding Course ";
        
        Course found;
        if(courseTree->getEntry(c,found))
        {
            cout<<"Course with this id already exists, failed to add course "<<endl;
			done = true;
        }
        else
        {
            cout<<"Course Added to BSTs and Hash Table"<<endl;
            courseTree->insert(c);
            bool success = hashTable->add(courseid,c);
            c.setKey(title);
            secCourseTree->insert(c);
            done = true;
        }
    }while(!done);
    
    
}

void BSTprintSortedList(const BinarySearchTree<Course> * courseTree,const BinarySearchTree<Course> * secCourseTree)
{
    cout<<"Sorted by "<<endl;
    cout<<"\tC - Courseid"<<endl;
    cout<<"\tT - Title"<<endl;
    char input;
    cin>>input;
    
    if(tolower(input) == 'c')
        courseTree->inOrder(displayCourse);
    if(tolower(input) == 't')
        secCourseTree->inOrder(displayCourse);
    cout << endl;
    
}

void BSTsearch(const BinarySearchTree<Course> * courseTree,const BinarySearchTree<Course> * secCourseTree){
    
    char searchoption;
    string courseid;
    cout<<"Search"<<endl;
    cout<<"P - Courseid (BST)"<<endl;
    cout<<"S - Title (BST)"<<endl;
    //cout<<"H - HashTable "<<endl;
    cin>>searchoption;
    
    switch(toupper(searchoption))
    {
        case 'P':
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
                        done = true;
                    }
                    
                    else
                        cout << endl << "Invalid ID, try again " << endl;
                    
                    
                }
                
            } while (!done);
            
            break;
        }
        case 'S':
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
                    Course search;
                    search.setTitle(title);
                    search.setKey(title);
                    Course found;
                    
                    
                    LinkedList<Course> *searchList = secCourseTree->getEntries(search);
                    
                    
                    if(searchList->getCount() > 1)
                    {
                        cout<<"Multiple Courses Found "<<endl;
                    }
                    else if(searchList->getCount() == 1)
                    {
                        cout<<"Course Found "<<endl;
                    }
                    else
                        cout<<"Course Not Found "<<endl;
                    
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
	cout << "Breadth" << endl;
	courseTree->levelOrder(displayCourse);
}

void BSTpreOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "Preorder" << endl;
	courseTree->preOrder(displayCourse);
}

void BSTinOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "Inorder" << endl;
	courseTree->inOrder(displayCourse);
}

void BSTpostOrder(const BinarySearchTree<Course> * courseTree)
{
	cout << "Postorder" << endl;
	courseTree->postOrder(displayCourse);
}

void HashPrint(const HashedDictionary<string, Course> *hashTable)
{
    char input;
    cout<<"F - Full Table"<<endl;
    cout<<"I - Items"<<endl;
    cin>>input;
    
    input = tolower(input);
    if(input == 'f')
    {
        hashTable->printHashTable(displayItems);
    }
    else if (input == 'i')
    {
        hashTable->displayHashTableList(displayKey);
    }

}

void HashSearch(const HashedDictionary<string, Course> *hashTable)
{
    string courseid;
    bool done = false;
    do {
        cout << endl << "Enter Course ID (or 'Q' to return to menu): ";
        cin >> courseid;
        
        if (courseid == "Q" || courseid == "q")
            done = true;
        else {
            
            Course search(courseid);
            search.setKey(courseid);
            Course *found;
            
            //bool success = hashTable->getEntry(search, found);
            found = hashTable->getItem(courseid);
            if (found != 0)
            {
                cout << endl << "Course ID found: "  << "ID: " << found->getCourseid() << endl << "Title: " << found->getTitle() << endl;
                done = true;
            }
            
            else
                cout << endl << "Invalid ID, try again " << endl;
            
            
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
        switch (toupper(option)){
            case 'C':HASHstatistics(db.getHash());break;
                //case 'B':BSTbreadthFirst(db.getTree());break;
            case 'B' :BSTprintSortedList(db.getTree(),db.getSecTree());break;
			case 'L': BSTbreadth(db.getTree()); break;
			case 'M': BSTpreOrder(db.getTree()); break;
			case 'N': BSTinOrder(db.getTree()); break;
			case 'O': BSTpostOrder(db.getTree()); break;
            case 'T':BSTindentedPrint(db.getTree());break;
            case 'F':BSTprintFile(db.getTree());break;
            case 'Q':done = true;BSTprintFile(db.getTree());break;
            case 'X':BSTdeleteCourse(db.getTree(), db.getSecTree(), db.getHash());break;
            case 'A':BSTAddCourse(db.getTree(),db.getSecTree(), db.getHash());break;
            case 'H':showOptions(developerMode!='d');break;
            case 'S':BSTsearch(db.getTree(),db.getSecTree());break;
            case 'Z':cout << "Developer mode(1 or 0):"; cin >> developerMode; showOptions(developerMode);break;
            //case 'P': db.getHash()->displayHashTableList(displayKey);
            case 'P': HashPrint(db.getHash());
                break;
            case 'D': HashSearch(db.getHash());
                break;
            default:cout << "Invalid input, try again" << endl;cin.clear();break;
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
