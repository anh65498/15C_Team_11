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
    int tableSize;
    int bucketSize;
	int threshold;

    BinarySearchTree<Course>* courseTree;
    HashedDictionary<string,Course> *hashTable;
    BinarySearchTree<Course>* secCourseTree;
    int getFileLines(string);
    int closestPrime(int);


public:
	CourseDB() {}
	bool buildDatabase(string fileName, BinarySearchTree<Course>  * courseTree, HashedDictionary<string,Course> * hashTable,int key);
    CourseDB(string,int);
    BinarySearchTree<Course>* getTree(){return courseTree;}
    BinarySearchTree<Course>* getSecTree(){return secCourseTree;}
    HashedDictionary<string,Course>* getHash(){return hashTable;}
    void rehashHashTable(const HashedDictionary<string,Course> *oldHashTable,int newSize ,int newBucketSize);

};

// determine how many objects are in a file based on number of lines
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

// check if an integer is a prime number
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

// finds the closest prime number greater than a given integer
int CourseDB::closestPrime(int a){
    while (!IsPrime(++a)){ }
    return a;
}

CourseDB::CourseDB(string fileName, int buckets)
{
    int syze = getFileLines(fileName);
    //tableSize = closestPrime(syze/2);
	tableSize = closestPrime(syze / 4);
    //cout << "Object amount:" << syze << endl << "Next prime number for table/2: " << tableSize << endl;
    bucketSize = buckets;
	threshold = 80;
    courseTree = new BinarySearchTree < Course > ;
    secCourseTree = new BinarySearchTree < Course > ;
    hashTable = new HashedDictionary < string, Course >(tableSize,bucketSize);

    ifstream infile;
    infile.open(fileName.c_str());
    if (!infile){cout << "Error opening input file " << endl;return;}
    string line;
    while (getline(infile, line)){
        string courseid = "";
        string classkey;
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
        classkey = line.substr(start, index - start);
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

		//working code:

       /* Course c;
        c.setCourseid(courseid);
        c.setInstructor(instructor);
        c.setCrn(crn);
        c.setTitle(title);
        c.setLocation(location);
        c.setDays(days);
        c.setStartTime(start_time);
        c.setEndTime(end_time);
        c.setKey(courseid);
        //BinaryNode<Course> *newNode = new BinaryNode<Course>(c);

        courseTree->insert(c);
        //hashTable->add(newNode->getItem().getCourseid(),newNode);
        hashTable->add(courseid,c);
        c.setKey(title);
        secCourseTree->insert(c);*/

		//alternate with pointers:
		Course *c = new Course();
		c->setCourseid(courseid);
		c->setInstructor(instructor);
		c->setClassKey(classkey);
		c->setTitle(title);
		c->setLocation(location);
		c->setDays(days);
		c->setStartTime(start_time);
		c->setEndTime(end_time);
		c->setKey(courseid);
		//BinaryNode<Course> *newNode = new BinaryNode<Course>(c);

		courseTree->insert(*c);
		//hashTable->add(newNode->getItem().getCourseid(),newNode);
		hashTable->add(courseid, *c);
		c->setKey(title);
		secCourseTree->insert(*c);

        int loadfactor = hashTable->getLoadFactor();
        if (loadfactor > 80)
        {
            tableSize = closestPrime(tableSize * 1.3);
            rehashHashTable(hashTable, tableSize, buckets);
            hashTable->updateTableSize(tableSize);
            loadfactor = hashTable->getLoadFactor();
            cout << "Rehashing to " << tableSize << " size... \n";
        }

    }
    cout<<"Ready!"<<endl;
    infile.close();
}

// rehashes the hash table passed in as a paramater with the new size and updates the pointer of the current hash table to this new hash table after rehash
void CourseDB::rehashHashTable(const HashedDictionary<string,Course> *oldHashTable,int newSize,int newBucketSize )
{
    HashedDictionary<string,Course> *newHashTable = hashTable->reHash(hashTable, newSize,newBucketSize);
    if(newHashTable != 0)
    {
        // delete the old hashTable
        delete oldHashTable;
        hashTable = newHashTable;
    }
}



#endif
