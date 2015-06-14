//temporary test file for reading courses into BST

#ifndef _CourseDatabase_h
#define _CourseDatabase_h

#include <iostream>
#include "Course.h"
#include "BinarySearchTree.h"
#include "HashedDictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

class CourseDB
{
private:
	string fileName;

public:
	CourseDB() {}
	bool buildDatabase(string fileName, BinarySearchTree<Course>  * courseTree, HashedDictionary<string,Course> * hashTable);
};

bool CourseDB::buildDatabase(string fileName, BinarySearchTree<Course>  * courseTree, HashedDictionary<string,Course> * hashTable)
{
	ifstream infile;
	infile.open(fileName);
	if (!infile)
	{
		cout << "Error opening input file " << endl;
		return false;

	}
	string line;
	while (!infile.eof())
	{
		string courseid = "";
        string crn;
		string title;
		string instructor;
        string days;
        string start_time;
        string end_time;
		string location;


		getline(infile, line);

		//10286;ACCT001A03;FINAN ACCOUNTNG I;Breen, Mary A.;MTWR;1000;1215;G6
        //courseid,crn,title,instructor,days,start_time,end_time,location

		int index = line.find(';');
		int start = 0;
		courseid = line.substr(0, index);
		start = index + 1;

        index = line.find(';', index + 1);
        crn = line.substr(start, index - start);
        start = index + 1;

		index = line.find(';', index + 1);
		title = line.substr(start, index - start);
		start = index + 1;


		index = line.find(';', index + 1);
		instructor = line.substr(start, index - start);
		start = index + 1;

		index = line.find(';', index + 1);
		days = line.substr(start, index - start);

		start = index + 1;

		index = line.find(';', index + 1);
		start_time = line.substr(start, index - start);
		start = index + 1;

        index = line.find(';', index + 1);
        end_time = line.substr(start, index - start);
        start = index + 1;

        index = line.find(';', index + 1);
        location = line.substr(start, index - start);
        start = index + 1;

		Course c;
		c.setCourseid(courseid);
		c.setInstructor(instructor);
        c.setCrn(crn);
		c.setTitle(title);
		c.setLocation(location);
		c.setDays(days);
		c.setStartTime(start_time);
        c.setEndTime(end_time);

		courseTree->insert(c);

        if(!hashTable->add(c.getCourseid(),c))
        {
            //TODO:rejected
        }


		//c.print();
	}
	infile.close();

	return true;
}

#endif
