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
    int tableSize;
    int bucketSize;
	string fileName;
    BinarySearchTree<Course>* courseTree;
    HashedDictionary<string,Course> *hashTable;
    int getFileLines(string);
    int closestPrime(int);
public:
	CourseDB(string,int);
	BinarySearchTree<Course>* getTree(){return courseTree;}
	HashedDictionary<string,Course>* getHash(){return hashTable;}
};

int CourseDB::getFileLines(string file){
    int lines = 0;
    ifstream infile(file.c_str());
    if(!infile){cout<<"Error opening input file" << endl; return -1;
    }else{
        string line;
        while(getline(infile,line)){
            lines++;
        }
    }
    infile.close();
    return lines;
}

bool IsPrime(int number){
    if (number == 2 || number == 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {
        if (number % (divisor - 1) == 0)
            return false;
        if (number % (divisor + 1) == 0)
            return false;
        divisor += 6;

    }
    return true;
}


int CourseDB::closestPrime(int a){
    while (!IsPrime(++a)){ }
    return a;
}

CourseDB::CourseDB(string fileName, int buckets)
{
    int syze = getFileLines(fileName);
    tableSize = closestPrime(syze/2);
    cout << "Object amount:" << syze << endl << "Next prime number for table/2: " << tableSize << endl;
    bucketSize = buckets;
    courseTree = new BinarySearchTree < Course > ;
    hashTable = new HashedDictionary < string, Course >(tableSize,bucketSize);

	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile){cout << "Error opening input file " << endl;return;}
	string line;
	while (getline(infile, line)){
		string courseid = "";
        string crn;
		string title;
		string instructor;
        string days;
        string start_time;
        string end_time;
		string location;

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
        BinaryNode<Course> *newNode = new BinaryNode<Course>(c);

		courseTree->insert(newNode);
		hashTable->add(newNode->getItem().getCourseid(),newNode);
	}
	infile.close();
}

#endif
