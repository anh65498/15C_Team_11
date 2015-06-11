//temporary test file for reading courses into BST

#ifndef _CourseDatabase_h
#define _CourseDatabase_h

#include <iostream>
#include "Course.h"
#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

class CourseDB
{
private:
	string fileName;

public:
	CourseDB() {}
	bool buildDatabase(string fileName, BinarySearchTree<Course>  * courseTree);


};

bool CourseDB::buildDatabase(string fileName, BinarySearchTree<Course>  * courseTree)
{

	ifstream infile;
	infile.open(fileName);
	if (!infile)
	{
		cout << "Error opening input file " << endl;
		return false;

	}
	string line;
	while (infile)
	{
		string courseid = "";
		string title;
		string instructor;
		string location;
		string time;
		int units;
		string quarter;

		getline(infile, line);

		//00043;introduc*tion to visual arts;Roehl, Paul;MW 08:30 AM­12:20PM;4;Summer
		int index = line.find(';');
		int start = 0;
		courseid = line.substr(0, index);
		start = index + 1;
		index = line.find(';', index + 1);

		title = line.substr(start, index - start);
		start = index + 1;


		index = line.find(';', index + 1);
		instructor = line.substr(start, index - start);
		start = index + 1;

		index = line.find(';', index + 1);
		location = line.substr(start, index - start);

		start = index + 1;

		index = line.find(';', index + 1);
		time = line.substr(start, index - start);

		start = index + 1;

		index = line.find(';', index + 1);
		string units_str = line.substr(start, index - start);

		units = atoi(units_str.c_str());

		start = index + 1;

		string qurter = line.substr(start, line.length() - start);

		Course c;
		c.setCourseid(courseid);
		c.setInstructor(instructor);
		c.setTime(time);
		c.setTitle(title);
		c.setLocation(location);
		c.setQuarter(quarter);
		c.setUnits(units);

		courseTree->insert(c);
		c.print();
	}
	infile.close();

	return true;
}

#endif
