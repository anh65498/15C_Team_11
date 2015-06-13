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
    string crn;
    string title;
    string instructor;
    
    string start_time;
    string end_time;
    string days;
    string location;
    
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
        crn = "0";
        
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
    void setCrn(const string input) { crn = input; }
    void setDays(const string input) { days = input; }
    
    
    // mutators
    
    string getCourseid() const{ return courseid; }
    string getTitle() const{ return title; }
    string getInstructor() const{ return instructor; }
    string getLocation() const{ return location; }
    string getCrn() const{ return crn; }
    string getStartTime() const{ return start_time; }
    string getEndTime() const{ return end_time; }
    string getDays() const{ return days; }
    
    
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
