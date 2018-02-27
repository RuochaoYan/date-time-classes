//
//  SFInterval.hpp
//  Assignment3Project
//
//  Created by 严若超 on 2/21/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#ifndef SFInterval_hpp
#define SFInterval_hpp

#include <stdio.h>

namespace SoftwareFoundations {

    class SFInterval {
    public:
        SFInterval(int year=0, int month=0, int day=0, int hour=0, int minute=0, int second=0, bool positive=true);
        
        operator const char*(); // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
        // Ex. 5 years, 3 months, 2 days, 6 hours, 7 minutes and 10 seconds
        bool positive;
    private:
        int years;
        int months;
        int days;
        int hours;
        int minutes;
        int seconds;
    };
    
}
#endif /* SFInterval_hpp */
