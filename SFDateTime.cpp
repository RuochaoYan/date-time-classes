//
//  SFDateTime.cpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFDateTime.hpp"
#include "SFDate.hpp"
#include "SFTime.hpp"
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

using SoftwareFoundations::SFDateTime;
using SoftwareFoundations::SFInterval;
using SoftwareFoundations::SFTimezone;

//init a new datetime based on GMT, unless a valid timezone is provided
SFDateTime::SFDateTime(SFTimezone *aTimezone){
    time_t now = time(0);
    tm *ltm = gmtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;
    theDate = new SFDate(month, day, year);
    theTime = new SFTime(hour, minute, second);
    tz = SFTimezone("GMT");
    if(aTimezone){
        timezoneConvert(*aTimezone);
    }
}

// destructor
SFDateTime::~SFDateTime(){
    delete theTime;
    delete theDate;
}

SFDateTime::SFDateTime(const SFDateTime &aCopy){
    theDate = new SFDate(aCopy);
    theTime = new SFTime(aCopy);
    tz = SFTimezone(aCopy.tz);
}

SFDateTime::SFDateTime(int aMonth, int aDay, int aYear, int anHour, int aMinutes, int aSeconds, SFTimezone *aTimezone){
    theDate = new SFDate(aMonth, aDay, aYear);
    theTime = new SFTime(anHour, aMinutes, aSeconds);
    if(aTimezone){
        tz = *aTimezone;
    }
    else
        tz = SFTimezone("GMT");
}

//parse the given string of the form "MM/DD/YYYY HH:MM:SS"
SFDateTime::SFDateTime(const char* aString, SFTimezone *aTimezone){
    std::string theString(aString);
    std::istringstream theStream(theString);
    std::vector<std::string> words;
    while (!theStream.eof()) {
        std::string theWord;
        getline(theStream, theWord, ' ');
        if(theWord.length()) {
            words.push_back(theWord);
        }
    }
    if(theString[0] >= '0' && theString[0] <= '9'){
        this->theDate = new SFDate(words[0].c_str());
        this->theTime = new SFTime(words[1].c_str());
    }
    else{
        std::string input = words[0] + " " + words[1] + " " + words[2];
        this->theDate = new SFDate(input.c_str());
        this->theTime = new SFTime(words[3].c_str());
    }
    
    if(aTimezone){
        tz = *aTimezone;
    }
    else
        tz = SFTimezone("GMT");
}

SFDateTime::SFDateTime(const SFDate &aDate, const SFTime &aTime, SFTimezone *aTimezone){
    theDate = new SFDate(aDate);
    theTime = new SFTime(aTime);
    if(aTimezone){
        tz = *aTimezone;
    }
    else
        tz = SFTimezone("GMT");
}

SFInterval SFDateTime::operator-(const SFDateTime &other) const{ //determine interval between two objects...
    SFDateTime theOther(other);
    theOther.timezoneConvert(this->tz);
    int years =  theOther.theDate->getYear() - theDate->getYear();
    int months = theOther.theDate->getMonth() - theDate->getMonth();
    int days = theOther.theDate->getDay() - theDate->getDay();
    int hours = theOther.theTime->getHour() - theTime->getHour();
    int minutes = theOther.theTime->getMinutes() - theTime->getMinutes();
    int seconds = theOther.theTime->getSeconds() - theTime->getSeconds();
    bool positive = true;
    if(*this > theOther){
        years = -years;
        months = -months;
        days = -days;
        hours = -hours;
        minutes = -minutes;
        seconds = -seconds;
        positive = false;
    }
    return SFInterval(years, months, days, hours, minutes, seconds, positive);
}

SFTimezone&  SFDateTime::getTimezone(){ //retrieve timezone currently associated with this object
    return tz;
}
SFDateTime&  SFDateTime::setTimezone(SFTimezone &aTimezone){ //change timezone
    timezoneConvert(aTimezone);
    return *this;
}

//ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
bool SFDateTime::operator>(const SFDateTime& aDateTime) const{
    SFDateTime theDateTime(aDateTime);
    theDateTime.timezoneConvert(this->tz);
    if(*theDate > *(theDateTime.theDate))
        return true;
    else if(*theDate == *(theDateTime.theDate)){
        if(*theTime > *(theDateTime.theTime))
            return true;
        else
            return false;
    }
    else
        return false;
}
bool SFDateTime::operator<(const SFDateTime& aDateTime) const{
    SFDateTime theDateTime(aDateTime);
    theDateTime.timezoneConvert(this->tz);
    if(*theDate < *(theDateTime.theDate))
        return true;
    else if(*theDate == *(theDateTime.theDate)){
        if(*theTime < *(theDateTime.theTime))
            return true;
        else
            return false;
    }
    else
        return false;
}
bool SFDateTime::operator>=(const SFDateTime& aDateTime) const{
    return !operator<(aDateTime);
}
bool SFDateTime::operator<=(const SFDateTime& aDateTime) const{
    return !operator>(aDateTime);
}
bool SFDateTime::operator==(const SFDateTime& aDateTime) const{
    SFDateTime theDateTime(aDateTime);
    theDateTime.timezoneConvert(this->tz);
    if(*theDate == *(theDateTime.theDate) && *theTime == *(theDateTime.theTime))
        return true;
    else
        return false;
}
bool SFDateTime::operator!=(const SFDateTime& aDateTime) const{
    return !operator==(aDateTime);
}


SFDateTime::operator const char*(){   //Returns string of the form "MON DATE, YEAR HH:MM:SS TIMEZONE" Ex. Jan 4, 1961 09:15:00 PST
    return toDateTimeString().c_str();
}
SFDateTime::operator SFDate(){
    return *theDate;
}
SFDateTime::operator SFTime(){
    return *theTime;
}
SFDateTime::operator SFTimezone(){
    return tz;
}

std::string SFDateTime::toDateTimeString(){   //Jan 4, 1961 09:15:00 PST (always this format)
    std::string map[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    std::string res = map[theDate->getMonth()-1] + " " + std::to_string(theDate->getDay()) + ", " + std::to_string(theDate->getYear()) + " " + theTime->toTimeString() + " " + std::string((const char*)tz);
    return res;
}

//... more members here as necessary...

void SFDateTime::timezoneConvert(const SFTimezone &aTimezone){
    int diffHour = aTimezone.diff - tz.diff;
    if(theTime->getHour() + diffHour >= 24){
        theDate->adjustByDays(1);
    }
    if(theTime->getHour() + diffHour < 0){
        theDate->adjustByDays(-1);
    }
    theTime->adjustByHours(diffHour);
    tz.diff = aTimezone.diff;
}

// judge if the datetime is in the DST
// DST begins at 2:00 a.m. on the second Sunday in March, and ends at 2:00 a.m. on the first Sunday in November
//bool SFDateTime::isDST(){
//}

