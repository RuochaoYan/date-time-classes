//
//  SFTimezone.hpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#ifndef SFTimezone_hpp
#define SFTimezone_hpp

#include <stdio.h>

namespace SoftwareFoundations {

class SFTimezone {
    public:
        SFTimezone(); // add default constructor
        SFTimezone(const char* aTimezoneAbbrev); //GMT, EST, CST, PST
        SFTimezone(const SFTimezone &aTimezone); //copy
        
        operator const char*(); // Returns the 3 letter abbreviation of the timezone object
        
        //...other members as needed...
        int diff;
    };
    
}
#endif /* SFTimezone_hpp */
