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
    string classkey;
    string title;
    string instructor;

    string start_time;
    string end_time;
    string days;
    string location;

    string key;

    //int units;
    //string quarter;

public:
    // constructors
    Course()
    {
        courseid = "0";
        title = "0";
        instructor = "0";
        location = "0";
        classkey = "0";

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
    void setStartTime(const string input) { start_time = input; }
    void setEndTime(const string input) { end_time = input; }
    void setClassKey(const string input) { classkey = input; }
    void setDays(const string input) { days = input; }
    void setKey(const string input) { key = input; }


    // mutators

    string getCourseid() const{ return courseid; }
    string getTitle() const{ return title; }
    string getInstructor() const{ return instructor; }
    string getLocation() const{ return location; }
    string getClassKey() const{ return classkey; }
    string getStartTime() const{ return start_time; }
    string getEndTime() const{ return end_time; }
    string getDays() const{ return days; }
    string getKey() const {return key;}


    // overloads > operator
    bool operator >(const Course & d)
    {
        if (key > d.key)
            return true;
        else
            return false;
    }

    // overloads < operator
    bool operator <(const Course & d)
    {
        if (key < d.key)
            return true;
        else
            return false;
    }

    // overloads == operator
    bool operator ==(const Course& d)
    {
        if (key == d.key)
            return true;
        else
            return false;
    }

    // overloads >= operator
    bool operator >=(const Course & d)
    {
        if (key >= d.key)
            return true;
        else
            return false;
    }

    // overloads <= operator
    bool operator <=(const Course & d)
    {
        if (key <= d.key)
            return true;
        else
            return false;
    }

    friend ostream & operator<<(ostream &o, const Course& c)
    {
        o << c.courseid << ";" << c.classkey << ";" << c.title << ";" << c.instructor << ";" << c.days << ";" << c.start_time << ";" << c.end_time << ";" << c.location<< endl;
        return o;
    }


};

#endif
