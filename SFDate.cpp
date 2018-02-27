//
//  SFDate.cpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFDate.hpp"
#include "SFInterval.hpp"
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

// split a string by slashes
std::vector<std::string> split(std::string aStr, char delimiter){
    std::istringstream theStream(aStr);
    std::vector<std::string> words;
    while (!theStream.eof()) {
        std::string theWord;
        getline(theStream, theWord, delimiter);
        if(theWord.length()) {
            words.push_back(theWord);
        }
    }
    return words;
}

using SoftwareFoundations::SFDate;
using SoftwareFoundations::SFInterval;

// default to today
SFDate::SFDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

// must parse the given string of the form MM/DD/YYYY
SFDate::SFDate(const char *aDateTimeString){
    std::string theStr(aDateTimeString);
    if(theStr[0] >= '0' && theStr[0] <= '9'){
        std::vector<std::string> words = split(theStr, '/');
        month = atoi(words[0].c_str()); // convert string to int
        day = atoi(words[1].c_str());
        year = atoi(words[2].c_str());
    }
    else{
        std::vector<std::string> words = split(theStr, ' ');
        if(words[0] == "Jan")
            month = 1;
        else if(words[0] == "Feb")
            month = 2;
        else if(words[0] == "Mar")
            month = 3;
        else if(words[0] == "Apr")
            month = 4;
        else if(words[0] == "May")
            month = 5;
        else if(words[0] == "Jun")
            month = 6;
        else if(words[0] == "Jul")
            month = 7;
        else if(words[0] == "Aug")
            month = 8;
        else if(words[0] == "Sep")
            month = 9;
        else if(words[0] == "Oct")
            month = 10;
        else if(words[0] == "Nov")
            month = 11;
        else
            month = 12;
        day = atoi(words[1].c_str());
        year = atoi(words[2].c_str());
    }
}

//build date from individual parts
SFDate::SFDate(int aMonth, int aDay, int aYear){
    month = aMonth;
    day = aDay;
    year = aYear;
}

// copy constructor
SFDate::SFDate(const SFDate &aCopy){
    year = aCopy.year;
    month = aCopy.month;
    day = aCopy.day;
}

SFDate::SFDate(const SFDateTime &aCopy){
    year = aCopy.theDate->getYear();
    month = aCopy.theDate->getMonth();
    day = aCopy.theDate->getDay();
}

SFDate& SFDate::operator ++(){ //advance by one day
    day++;
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
        if(month > 12){
            month -= 12;
            year++;
        }
    }
    return *this;
}

SFDate& SFDate::operator --(){ //back up by one day...
    day--;
    if(day <= 0){
        month--;
        if(month <= 0){
            year++;
            month += 12;
        }
        day += daysInMonth();
    }
    return *this;
}

SFInterval SFDate::operator-(const SFDate &other) const{ //determine interval between two dates...
    int years = other.year - year;
    int months = other.month - month;
    int days = other.day - day;
    bool positive = true;
    if(*this > other){
        years = -years;
        months = -months;
        days = -days;
        positive = false;
    }
    return SFInterval(years, months, days, 0, 0, 0, positive);
}
SFInterval SFDate::operator-(const SFDateTime &other) const{ //determine interval between two objects...
    return operator-(* other.theDate);
}

SFDate& SFDate::adjustByDays(int n){ // to add or subtract N days from the given date
    day += n;
    while(day > daysInMonth()){
        day -= daysInMonth();
        month++;
        if(month > 12){
            month -= 12;
            year++;
        }
    }
    while(day <= 0){
        month--;
        if(month <= 0){
            year--;
            month += 12;
        }
        day += daysInMonth();
    }
    return *this;
}
SFDate& SFDate::adjustByWeeks(int n){ // to add or subtract N weeks from the given date
    return adjustByDays(n * 7);
}
SFDate& SFDate::adjustByMonths(int n){ // to add or subtract N months from the given date
    month += n;
    while(month > 12){
        month -= 12;
        year++;
    }
    while(month <= 0){
        month += 12;
        year--;
    }
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
        if(month > 12){
            month -= 12;
            year++;
        }
    }
    return *this;
}
SFDate& SFDate::adjustByYears(int n){ // to add or subtract N years from the given date
    year += n;
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
        if(month > 12){
            month -= 12;
            year++;
        }
    }
    return *this;
}

SFDate& SFDate::setDay(int aDay){      //set the current day of the given date object; aDay must be in valid range
    day = aDay;
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
        if(month > 12){
            month -= 12;
            year++;
        }
    }
    return *this;
}
SFDate& SFDate::setMonth(int aMonth){  //set the current month of the given date object aMonth must be in valid range
    month = aMonth;
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
    }
    return *this;
}
SFDate& SFDate::setYear(int aYear){    //set the current year; must be in valid range
    year = aYear;
    if(day > daysInMonth()){
        day -= daysInMonth();
        month++;
    }
    return *this;
}

int   SFDate::getDay(){    //if date is 12/15/2018, the day is the 15th
    return day;
}
int   SFDate::getMonth(){  //if date is 12/15/2018, the month is 12 (dec)
    return month;
}
int   SFDate::getYear(){   //if date is 12/15/2018, the year is 2018
    return year;
}

int   SFDate::getWeekOfYear(){ //if date is 01/10/2018, the week of year is 2 (range is 1..52)
    SFDate firstDay(*this);
    int firstDayOfFirstWeek = firstDay.startOfYear().getDayOfweek();
    int theDays = getDayOfYear();
    int numOfWeeks = (theDays + firstDayOfFirstWeek) / 7;
    if(theDays % 7 != 0)
        numOfWeeks++;
    return numOfWeeks;
}
int   SFDate::getDayOfYear(){  //if date is 01/04/1961, the day of year is 4 (range is 1..365)
    int res = 0;
    int originMonth = month;
    for(month = 1; month < originMonth; month++){
        res += daysInMonth();
    }
    res += day;
    return res;
}
int   SFDate::getDayOfweek(){  //range (0..6 -- 0==sunday)
    int theMonth = month;
    int theYear = year;
    if(theMonth == 1 || theMonth == 2){
        theMonth += 12;
        theYear--;
    }
    int theWeekDay = (day + 1 + 2 * theMonth + 3 * (theMonth + 1) / 5 + theYear + theYear / 4 - theYear / 100 + theYear / 400) % 7;
    return theWeekDay;
}
int   SFDate::daysInMonth(){   //based on month/year, return # of days in the month
    int days = 0;
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        case 2:
            if(isLeap())
                days = 29;
            else
                days = 28;
            break;
    }
    return days;
}

SFDate& SFDate::startOfMonth(){ //if date is 12/15/2018, return 12/01/2018
    day = 1;
    return *this;
}
SFDate& SFDate::endOfMonth(){  //if date is 12/15/2018, return 12/31/2018
    day = daysInMonth();
    return *this;
}

SFDate& SFDate::startOfYear(){  //if date is 12/15/2018, return 01/01/2018
    month = 1;
    day = 1;
    return *this;
}
SFDate& SFDate::endOfYear(){    //if date is 12/15/2018, return 12/31/2018
    month = 12;
    day = 31;
    return *this;
}

// Return a string of the form MM/DD/YYYY
std::string SFDate::toDateString(){
    std::string monStr = month < 10 ? ("0" + std::to_string(month)) : std::to_string(month);
    std::string dayStr = day < 10 ? ("0" + std::to_string(day)) : std::to_string(day);
    std::string res = monStr + '/' + dayStr + '/' + std::to_string(year);
    return res;
}

// cast to char*
SFDate::operator const char*(){
    return toDateString().c_str();
}

//ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
bool SFDate::operator>(const SFDate& aDate) const{
    if(year > aDate.year)
        return true;
    else if(year == aDate.year){
        if(month > aDate.month)
            return true;
        else if(month == aDate.month){
            if(day > aDate.day)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
bool SFDate::operator<(const SFDate& aDate) const{
    if(year < aDate.year)
        return true;
    else if(year == aDate.year){
        if(month < aDate.month)
            return true;
        else if(month == aDate.month){
            if(day < aDate.day)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
bool SFDate::operator>=(const SFDate& aDate) const{
    return !operator<(aDate);
}
bool SFDate::operator<=(const SFDate& aDate) const{
    return !operator>(aDate);
}
bool SFDate::operator==(const SFDate& aDate) const{
    if(day == aDate.day && month == aDate.month && year == aDate.year)
        return true;
    else
        return false;
}
bool SFDate::operator!=(const SFDate& aDate) const{
    return !operator==(aDate);
}

// judge if it is a leap year
bool SFDate::isLeap(){
    if ((year % 400) == 0 || ((year % 4) == 0 && (year % 100) != 0))
        return true;
    else
        return false;
}

