//
//  SFTestHarness.hpp
//  ECE180-Assignment3
//
//  Created by rick gessner on 2/12/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef SFTestHarness_hpp
#define SFTestHarness_hpp
#include <string>

namespace SoftwareFoundations {
  
  class SFTestHarness {
  public:
    static int runAllTests();
    static int runDateTests();
    static int runTimeTests();
    static int runDateTimeTests();
    static int runIntervalTests();
    static int runTimezoneTests();
      static int providedTests();
    static std::string dateDifferenceTest(std::string aDate1, std::string aDate2);
    static std::string adjustDateByWeeksTest(std::string aDate, int aWeeks);
    static std::string setMonthDateTest(std::string aDate, int aMonth);
    static int getDayOfWeekDateTest(std::string aDate);
    static std::string endOfMonthDateTest(std::string aDate);
    static std::string timeDifferenceTest(std::string aTime1, std::string aTime2);
    static std::string adjustTimeByMinutesTest(std::string aTime1, int aMinutes);
    static int getMinutesTimeTest(std::string aTime);
    static std::string dataTimeDifferenceTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2);
    static std::string dataTimeToStringTest(std::string aDateTime, std::string timezone);
    static std::string timezoneConversionDateTimeTest(std::string aDateTime, std::string timezone);
    static bool greaterThanDateTimeTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2);
  };
  
}

#endif /* SFTestHarness_hpp */
