#ifndef CourseData_h
#define CourseData_h


class CourseData
{
public:

    Course *coursePtr;
    CourseData(Course *ptr)
    {
        coursePtr = ptr;
    }

    CourseData()
    {
        coursePtr = 0;
    }

    Course* getCoursePtr() const{return coursePtr;};
    void setCoursePtr(Course *p){coursePtr = p;}

    // overloads > operator
    bool operator >(const CourseData & d)
    {

        if (this->coursePtr->getCourseid() > d.coursePtr->getCourseid())
            return true;
        else
            return false;
    }

    // overloads < operator
    bool operator <(const CourseData & d)
    {
        if (this->coursePtr->getCourseid() < d.coursePtr->getCourseid())
            return true;
        else
            return false;
    }

    // overloads == operator
    bool operator ==(const CourseData& d)
    {
        if (this->coursePtr->getCourseid() == d.coursePtr->getCourseid())
            return true;
        else
            return false;
    }

    // overloads >= operator
    bool operator >=(const CourseData & d)
    {
        if (this->coursePtr->getCourseid() >= d.coursePtr->getCourseid())
            return true;
        else
            return false;
    }

    // overloads <= operator
    bool operator <=(const CourseData & d)
    {
        if (this->coursePtr->getCourseid() <= d.coursePtr->getCourseid())
            return true;
        else
            return false;
    }

    // overloads << operator
    friend ostream & operator<<(ostream &o, const CourseData& cd)
    {
        Course *c = cd.getCoursePtr();
        o << c->getCourseid() << " " << c->getClassKey() << "; " << c->getTitle() << "; " << c->getInstructor() << "; " << c->getDays() << " " << c->getStartTime() << "-" << c->getEndTime() << "; " << c->getLocation()<< endl;
        return o;
    }


};

#endif
