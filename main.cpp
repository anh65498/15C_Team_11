//test driver for bst course  tree
//rohan

#include "BinarySearchTree.h"  // BST ADT
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "CourseDatabase.h"

using namespace std;

void showMenu(const BinarySearchTree<Course> * courseTree);

// display: function to pass to BST traverse functions
void display(string & anItem)
{
	cout << "Displaying item - " << anItem << endl;
}

// displayStudent: displays the student IDs
void displayCourse(Course & anItem)
{
	cout << setprecision(1) << fixed << anItem.getCourseid() << " ";
}

// displayStudentWithLevel: displays the student IDs with the correct spacing and level number for print function
void displayCourseWithLevel(Course & anItem, int level)
{
	int maxwidth = 7; // width = level number + . + studentID = 7  ex: 1. 1900 = 7 chars
	for (int i = 0; i < level; i++)
	{
		for (int j = 0; j < maxwidth; j++)
			cout << " ";
	}

	cout << level + 1 << ".";
	cout << " " << anItem.getCourseid() << " ";
	cout << endl;
}

int main()
{
	BinarySearchTree<Course> * courseTree = 0;
	courseTree = new BinarySearchTree < Course > ;
	
	CourseDB db;
	db.buildDatabase("courses1.txt", courseTree);
	showMenu(courseTree);

	return 0;
}

// showMenu: Prints the selection of choices for the user
void showMenu(const BinarySearchTree<Course> * courseTree)
{
	bool done = false;
	char option;
	string courseid;
	cout << "Welcome to the Student Database:" << endl;
	cout << "B - Tree Breadth-First Traversal " << endl;
	cout << "D - Depth First Traversal " << endl;
	cout << "I - Iterative Depth-First Traversal " << endl;
	cout << "T - Print Tree as Indented List " << endl;
	cout << "S - Search By a Unique key " << endl;
	cout << "R - Print in Range " << endl;
	cout << "H - Help" << endl;
	cout << "Q - Quit" << endl;

	do
	{
		cout << "\nSelect an option: ";
		cin >> option;

		switch (toupper(option))
		{

		case 'B':
			cout << endl;
			cout << "Breadth-First: ";
			courseTree->levelOrder(displayCourse);
			cout << endl;
			break;

		case 'T':
			cout << endl;
			courseTree->print(displayCourseWithLevel);
			cout << endl;
			break;

		case 'D':
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
			break;

		case 'I':
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

			break;

		case 'Q':
			done = true;
			break;

		case 'H':
			cout << endl;
			cout << "B - Tree Breadth-First Traversal" << endl;
			cout << "D - Depth-First Traversal" << endl;
			cout << "I - Iterative Depth-First Traversals" << endl;
			cout << "T - Print Tree as Indented List" << endl;
			cout << "S - Search By a Unique key" << endl;
			cout << "R - Print in Range " << endl;
			cout << "H - Help" << endl;
			cout << "Q - Quit" << endl;
			break;
		case 'S':
		{
			bool done = false;
			do {
				cout << endl << "Enter Student ID: ";
				cin >> courseid;

				Course search(courseid);
				Course found;

				bool success = courseTree->getEntry(search, found);
				if (success)
				{
					cout << endl << "Course ID found: "  << "ID: " << found.getCourseid() << endl << "Title: " << found.getTitle() << endl;
					done = true;
				}

				else
					cout << endl << "Invalid ID, try again " << endl;

			} while (!done);

			break;
		}

		case 'R':
		{/*
			int minRange;
			int maxRange;



			bool done = false;
			do {
				Course minS, maxS;
				minS = studentTree.findSmallest();
				maxS = studentTree.findLargest();

				int min = minS.getCourseId();
				int max = maxS.getId();
				cout << endl << "Search Range - Please enter between " << min << " " << max << ":" << endl << endl;
				cout << "Min: ";
				cin >> minRange;
				cout << endl;
				cout << "Max: ";
				cin >> maxRange;
				cout << endl;
				if (minRange >= min && maxRange <= max && maxRange >= min)
				{
					done = true;
				}
				else
				{
					cout << endl << "Invalid range, try again" << endl;
					cin.clear();
				}

			} while (!done);


			Course minStudent(minRange, "Dummy", 0);
			Course maxStudent(maxRange, "Dummy", 0);

			studentTree.findNodesInRange(minStudent, maxStudent, displayCourse);
			cout << endl;
			break;
			*/

		}
		default:

			cout << "Invalid input, try again" << endl;
			cin.clear();
			break;

		}

	} while (!done);
}
