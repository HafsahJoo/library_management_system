/*
 * date.cpp
 * Author: M00952394
 * Created: 04/01/2024
 * Updated: 12/01/2024
 */

#include "date.h"
#include <iostream>

Date::Date(){}
Date::Date(int day, int month, int year)
{
    setDay(day);
    setMonth(month);
    setYear(year);
}

void Date::setDay(int day)
{
    this->day = day;
}

void Date::setMonth(int month)
{
    this->month = month;
}

void Date::setYear(int year)
{
    this->year = year;
}


int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}
