#ifndef SecCourseData_h
#define SecCourseData_h

// CourseData class with overloaded operators using the
// seconary key - Title of the Course class

class SecCourseData: public CourseData
{

public:

    SecCourseData(Course *ptr)
    {
        coursePtr = ptr;
    }

    SecCourseData()
    {

    }


    // overloads > operator
    bool operator >(const SecCourseData & d)
    {
        if (this->coursePtr->getTitle() > d.coursePtr->getTitle())
            return true;
        else
            return false;
    }

    // overloads < operator
    bool operator <(const SecCourseData & d)
    {
        if (this->coursePtr->getTitle() < d.coursePtr->getTitle())
            return true;
        else
            return false;
    }

    // overloads == operator
    bool operator ==(const SecCourseData& d)
    {
        if (this->coursePtr->getTitle() == d.coursePtr->getTitle())
            return true;
        else
            return false;
    }

    // overloads >= operator
    bool operator >=(const SecCourseData & d)
    {

        if (this->coursePtr->getTitle() >= d.coursePtr->getTitle())
            return true;
        else
            return false;
    }

    // overloads <= operator
    bool operator <=(const SecCourseData & d)
    {
        if (this->coursePtr->getTitle() <= d.coursePtr->getTitle())
            return true;
        else
            return false;
    }

};


#endif
