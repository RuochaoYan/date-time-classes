//
//  SFTime.hpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#ifndef SFTime_hpp
#define SFTime_hpp
#include "SFDateTime.hpp"
#include "SFInterval.hpp"
#include <string>
#include <stdio.h>

namespace SoftwareFoundations {

    class SFTime {
    public:
        SFTime();                             //default to now(HH:MM:SS)
        SFTime(const char *aTimeString);      //must parse the given string of the form "HH:MM:SS"
        SFTime(int anHour, int aMinutes, int aSeconds); //build time from individual parts
        SFTime(const SFTime &aCopy);
        SFTime(const SFDateTime &aCopy);
        
        SFTime& adjustByMinutes(int n); // to +/- N minutes from the given time
        SFTime& adjustByHours(int n); // to +/- N hours from the given time. 11:15pm + 2hours is 1:15a (rolls over)
        
        SFInterval operator-(const SFTime &other) const; //determine interval between two times...
        SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...
        
        int   getHour();
        int   getMinutes();
        int   getSeconds();
        
        SFTime& startOfDay(); //change time to (00:00:00)
        SFTime& endOfDay();   //change time to (23:59:59)
        
        std::string toTimeString();  //Returns string of the form HH:MM:SS
        operator const char*();
        
        //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
        
        bool operator>(const SFTime& aTime) const;
        bool operator<(const SFTime& aTime) const;
        bool operator>=(const SFTime& aTime) const;
        bool operator<=(const SFTime& aTime) const;
        bool operator==(const SFTime& aTime) const;
        bool operator!=(const SFTime& aTime) const;
        
        //... more members here as necessary...
    private:
        int second;
        int minute;
        int hour;
    };
}
#endif /* SFTime_hpp */
