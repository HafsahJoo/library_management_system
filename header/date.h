#ifndef _DATE_H_
#define _DATE_H_

/*
   date.h
   Author: M00952394
   Created: 04/01/2024
   Updated: 14/01/2024
*/

/*
 * The Date class stores date.
 * It includes methods to set and get the day, month, and year of the date.
 */
class Date
{

private:
    int day;
    int month;
    int year;

public:
    /*
        Default constructor
    */
    Date();

    /*
        Constructor for Date class that sets day, month, and year.
        @param day representing the day
        @param month representing the month
        @param year representing the year
    */
    Date(int day, int month, int year);

    /*
        Setter for day
        @param day representing the day
    */
    void setDay(int day);

    /*
        Setter for month
        @param month representing the month
    */
    void setMonth(int month);

    /*
        Setter for year
        @param year representing the year
    */
    void setYear(int year);

    /*
        Getter for day
        @return day representing the day
    */
    int getDay();

    /*
        Getter for month
        @return month representing the month
    */
    int getMonth();
    
    /*
        Getter for year
        @return year representing the year
    */
    int getYear();
};

#endif