//
//  SFTimezone.cpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFTimezone.hpp"
#include <cstring>

using SoftwareFoundations::SFTimezone;

SFTimezone::SFTimezone(){
    diff = 0;
}

SFTimezone::SFTimezone(const char* aTimezoneAbbrev){ //GMT, EST, CST, PST
    if(strcmp(aTimezoneAbbrev, "EST") == 0)
        diff = -5;
    else if(strcmp(aTimezoneAbbrev, "CST") == 0)
        diff = -6;
    else if(strcmp(aTimezoneAbbrev, "PST") == 0)
        diff = -8;
    else
        diff = 0; // represents "GMT"
}

SFTimezone::SFTimezone(const SFTimezone &aTimezone){ //copy
    diff = aTimezone.diff;
}

SFTimezone::operator const char*(){ // Returns the 3 letter abbreviation of the timezone object
    if(diff == -5)
        return "EST";
    else if(diff == -6)
        return "CST";
    else if(diff == -8)
        return "PST";
    else
        return "GMT";
}
