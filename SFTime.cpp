//
//  SFTime.cpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFTime.hpp"
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

// split a string by colons
std::vector<std::string> splitByColon(std::string aStr){
    std::istringstream theStream(aStr);
    std::vector<std::string> words;
    while (!theStream.eof()) {
        std::string theWord;
        getline(theStream, theWord, ':');
        if(theWord.length()) {
            words.push_back(theWord);
        }
    }
    return words;
}

using SoftwareFoundations::SFTime;
using SoftwareFoundations::SFInterval;

//default to now(HH:MM:SS)
SFTime::SFTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm->tm_sec;
}

//must parse the given string of the form "HH:MM:SS"
SFTime::SFTime(const char *aTimeString){
    std::string theStr(aTimeString);
    std::vector<std::string> words = splitByColon(theStr);
    hour = atoi(words[0].c_str());
    minute = atoi(words[1].c_str());
    second = atoi(words[2].c_str());
}

//build time from individual parts
SFTime::SFTime(int anHour, int aMinutes, int aSeconds){
    hour = anHour;
    minute = aMinutes;
    second = aSeconds;
}

SFTime::SFTime(const SFTime &aCopy){
    hour = aCopy.hour;
    minute = aCopy.minute;
    second = aCopy.second;
}
SFTime::SFTime(const SFDateTime &aCopy){
    hour = aCopy.theTime->getHour();
    minute = aCopy.theTime->getMinutes();
    second = aCopy.theTime->getSeconds();
}

SFTime& SFTime::adjustByMinutes(int n){ // to +/- N minutes from the given time
    minute += n;
    while(minute >= 60){
        minute -= 60;
        hour++;
        if(hour >= 24)
            hour -= 24;
    }
    while(minute < 0){
        minute += 60;
        hour--;
        if(hour < 0)
            hour += 24;
    }
    return *this;
}
SFTime& SFTime::adjustByHours(int n){ // to +/- N hours from the given time. 11:15pm + 2hours is 1:15a (rolls over)
    hour += n;
    while(hour >= 24){
        hour -= 24;
    }
    while(hour < 0){
        hour += 24;
    }
    return *this;
}

SFInterval SFTime::operator-(const SFTime &other) const{ //determine interval between two times...
    int hours = other.hour - hour;
    int minutes = other.minute - minute;
    int seconds = other.second - second;
    bool positive = true;
    if(*this > other){
        hours = -hours;
        minutes = -minutes;
        seconds = -seconds;
        positive = false;
    }
    return SFInterval(0, 0, 0, hours, minutes, seconds, positive);
}
SFInterval SFTime::operator-(const SFDateTime &other) const{ //determine interval between two objects...
    return operator-(* other.theTime);
}

int   SFTime::getHour(){
    return hour;
}
int   SFTime::getMinutes(){
    return minute;
}
int   SFTime::getSeconds(){
    return second;
}

SFTime& SFTime::startOfDay(){ //change time to (00:00:00)
    hour = 0;
    minute = 0;
    second = 0;
    return *this;
}
SFTime& SFTime::endOfDay(){   //change time to (23:59:59)
    hour = 23;
    minute = 59;
    second = 59;
    return *this;
}

//Returns string of the form HH:MM:SS
std::string SFTime::toTimeString(){
    std::string hStr = hour < 10 ? ("0" + std::to_string(hour)) : std::to_string(hour);
    std::string mStr = minute < 10 ? ("0" + std::to_string(minute)) : std::to_string(minute);
    std::string sStr = second < 10 ? ("0" + std::to_string(second)) : std::to_string(second);
    std::string res = hStr + ':' + mStr + ':' + sStr;
    return res;
}

SFTime::operator const char*(){
    return toTimeString().c_str();
}

//ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
bool SFTime::operator>(const SFTime& aTime) const{
    if(hour > aTime.hour)
        return true;
    else if(hour == aTime.hour){
        if(minute > aTime.minute)
            return true;
        else if(minute == aTime.minute){
            if(second > aTime.second)
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
bool SFTime::operator<(const SFTime& aTime) const{
    if(hour < aTime.hour)
        return true;
    else if(hour == aTime.hour){
        if(minute < aTime.minute)
            return true;
        else if(minute == aTime.minute){
            if(second < aTime.second)
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
bool SFTime::operator>=(const SFTime& aTime) const{
    return !operator<(aTime);
}
bool SFTime::operator<=(const SFTime& aTime) const{
    return !operator>(aTime);
}
bool SFTime::operator==(const SFTime& aTime) const{
    if(second == aTime.second && minute == aTime.minute && hour == aTime.hour)
        return true;
    else
        return false;
}
bool SFTime::operator!=(const SFTime& aTime) const{
    return !operator==(aTime);
}

//... more members here as necessary...
