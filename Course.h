/**~*~*
Course template (TEMPORARY FOR TESTING BST PART)
*~**/
#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
using namespace std;

class Course
{
private:
	string courseid;
	string title;
	string instructor;
	string location;
	string time;
	int units;
	string quarter;

public:
	// constructors
	Course()
	{
		courseid = "0";
		title = "0";
		instructor = "0";
		location = "0";
		time = "0";
		units = 0;
	}

	Course(string idinput) : courseid(idinput){};

	void print()
	{
		cout << courseid << " " << title << " " << instructor << " " << location << endl;
	}

	// accessors

	void setCourseid(const string input) { courseid = input; }
	void setTitle(const string input) { title = input; }
	void setInstructor(const string input) { instructor = input; }
	void setLocation(const string input) { location = input; }
	void setTime(const string input) { time = input; }
	void setUnits(const int input) { units = input; }
	void setQuarter(const string input) { quarter = input; }


	// mutators

	string getCourseid() const{ return courseid; }
	string getTitle() const{ return title; }
	string getInstructor() const{ return instructor; }
	string getLocation() const{ return location; }
	int getUnits() const{ return units; }
	string getTime() const{ return time; }
	string getQuarter() const{ return quarter; }


	// overloads > operator
	bool operator >(const Course & d)
	{
		if (courseid > d.courseid)
			return true;
		else
			return false;
	}

	// overloads < operator
	bool operator <(const Course & d)
	{
		if (courseid < d.courseid)
			return true;
		else
			return false;
	}

	// overloads == operator
	bool operator ==(const Course& d)
	{
		if (courseid == d.courseid)
			return true;
		else
			return false;
	}

	// overloads >= operator
	bool operator >=(const Course & d)
	{
		if (courseid >= d.courseid)
			return true;
		else
			return false;
	}

	// overloads <= operator
	bool operator <=(const Course & d)
	{
		if (courseid <= d.courseid)
			return true;
		else
			return false;
	}


};

#endif
