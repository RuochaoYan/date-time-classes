//
//  SFInterval.cpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFInterval.hpp"
#include <string>

using SoftwareFoundations::SFInterval;

SFInterval::SFInterval(int year, int month, int day, int hour, int minute, int second, bool positive){
    years = year;
    months = month;
    days = day;
    hours = hour;
    minutes = minute;
    seconds = second;
    if(seconds < 0){
        seconds += 60;
        minutes--;
    }
    if(minutes < 0){
        minutes += 60;
        hours--;
    }
    if(hours < 0){
        hours += 24;
        days--;
    }
    if(days < 0){
        days += 30;
        months--;
    }
    if(months < 0){
        months += 12;
        years--;
    }
    this->positive = positive;
}

SFInterval::operator const char*(){ // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
    std::string res;
//    if(!positive)
//        res += '-';
    res += std::to_string(years) + " years, " + std::to_string(months) + " months, " + std::to_string(days) + " days, " + std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes and " + std::to_string(seconds) + " seconds";
    return res.c_str();
}
