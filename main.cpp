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

const int BUCKETSIZE = 1000;

using namespace std;

// display: function to pass to BST traverse functions
void display(string & anItem){
    cout << "Displaying item - " << anItem << endl;
}
void displayKey(string &s)
{
    cout<<s<<endl;
}
// displayStudent: displays the student IDs
void displayCourse(Course & anItem){
    cout << setprecision(1) << fixed << anItem.getCourseid() << " ";
}

// displayStudentWithLevel: displays the student IDs with the correct spacing and level number for print function
void displayCourseWithLevel(Course & anItem, int level){
    int maxwidth = 7; // width = level number + . + studentID = 7  ex: 1. 1900 = 7 chars
    for (int i = 0; i < level; i++){
        for (int j = 0; j < maxwidth; j++)
            cout << " ";
    }
    cout << level + 1 << ".";
    cout << " " << anItem.getCourseid() << " ";
    cout << endl;
}

void printCourseToFile(Course & anItem, int level,ostream os){
    os << anItem;
}

void showOptions(bool developerMode){
    cout << "\tZ - Developer Mode" << endl;
    if(developerMode){
        cout << "Binary Search Tree" << endl;
        cout << "\tB - Tree Breadth-First Traversal " << endl;
        cout << "\tD - Depth First Traversal " << endl;
        cout << "\tI - Iterative Depth-First Traversal " << endl;
        cout << "\tT - Print Tree as Indented List " << endl;
        cout << "\tS - Search " << endl;
        cout << "\tF - Print to File " << endl;
        cout << "\tA - Add Course " << endl;
        cout << "\tX - Delete Course " << endl;
        cout << "Hash Table" << endl;
        cout << "\tC - Display Collisions" << endl;
        cout << "\tP - print Hash table" << endl;
    }
    cout << "H - Help" << endl;
    cout << "Q - Quit" << endl;
}
void BSTprintFile(const BinarySearchTree<Course> * courseTree){
    cout << "Printing courses to courseout.txt" << endl;
    ofstream outfile;
    outfile.open("courseout.txt");
    courseTree->printToFile(outfile);
}
void BSTiterativeDepthFirst(const BinarySearchTree<Course> * courseTree){
    cout << endl << "Iterative Depth-First: ";
    cout << endl << endl << "Inorder: " << endl;
    courseTree->inOrder(displayCourse);
    cout << endl;
    cout << endl << "Preorder: " << endl;
    courseTree->preOrder(displayCourse);
    cout << endl;
    cout << endl << "Postorder: " << endl;
    courseTree->postOrder(displayCourse);
    cout << endl << endl;
}
void BSTbreadthFirst(const BinarySearchTree<Course> * courseTree){
    cout << endl;
    cout << "Breadth-First: ";
    courseTree->levelOrder(displayCourse);
    cout << endl;
}
void BSTdepthFirst(const BinarySearchTree<Course> * courseTree){
    cout << endl << "Depth-First: ";
    cout << endl << endl << "Inorder: " << endl;
    courseTree->inOrder(displayCourse);
    cout << endl;
    cout << endl << "Preorder: " << endl;
    courseTree->preOrder(displayCourse);
    cout << endl;
    cout << endl << "Postorder: " << endl;
    courseTree->postOrder(displayCourse);
    cout << endl << endl;
}

void BSTindentedPrint(const BinarySearchTree<Course> * courseTree){
    cout << endl;
    courseTree->print(displayCourseWithLevel);
    cout << endl;
}
void BSTdeleteCourse(const BinarySearchTree<Course> * courseTree){
    cout<<"Enter Course ID to delete :";
    string courseid;
    cin>>courseid;
    /*
    Course deleteCourse;
    deleteCourse.setCourseid(courseid);
    deleteCourse.setKey(courseid);
    courseTree->remove(deleteCourse);
    */
}
void BSTsearch(const BinarySearchTree<Course> * courseTree){

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
// showMenu: Prints the selection of choices for the user
void showMenu(CourseDB db)
{
    bool done = false;
    bool developerMode = false;
    char option;
    string courseid;
    cout << "Welcome to the Course Database" << endl;

    showOptions(developerMode);
    do{
        cout << "\nSelect an option: ";
        cin >> option;
        switch (toupper(option)){
            case 'C':HASHstatistics(db.getHash());break;
            case 'B':BSTbreadthFirst(db.getTree());break;
            case 'T':BSTindentedPrint(db.getTree());break;
            case 'D':BSTdepthFirst(db.getTree());break;
            case 'I':BSTiterativeDepthFirst(db.getTree());break;
            case 'F':BSTprintFile(db.getTree());break;
            case 'Q':done = true;break;
            case 'X':BSTdeleteCourse(db.getTree());break;
            case 'A':break;
            case 'H':showOptions(developerMode!='d');break;
            case 'S':BSTsearch(db.getTree());break;
            case 'Z':cout << "Developer mode(1 or 0):"; cin >> developerMode; showOptions(developerMode);break;
            case 'P': db.getHash()->displayHashTableList(displayKey);break;
            default:cout << "Invalid input, try again" << endl;cin.clear();break;
        }

    } while (!done);
}

int main()
{
    CourseDB db("courses.txt",BUCKETSIZE);
    showMenu(db);

    return 0;
}
