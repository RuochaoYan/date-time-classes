//
//  SFTestHarness.cpp
//  ECE180-Assignment3
//
//  Created by rick gessner on 2/12/18.
//

#include "SFTestHarness.hpp"
#include "SFDate.hpp"
#include "SFTime.hpp"
#include "SFTimezone.hpp"
#include <iostream>
using SoftwareFoundations::SFTestHarness;

//compare results and return error status (side-effect output to terminal)...
int compare(const std::string &str1, const std::string &str2, const char* aMessage) {
    const char* s1=str1.c_str();
    const char* s2=str2.c_str();

    std::cout << "Test: " << aMessage;
    if(strcmp(s1,s2)) {
        std::cout << " Error! s1(" << s1 << ") s2(" << s2 << ")" << std::endl;
        return 1;
    }

    std::cout << " ok " << std::endl;
    return 0;
}

//compare int results and return error status (side-effect output to terminal)...
int compare(int anArg1, int anArg2,const char* aMessage) {
    std::cout << "Test: " << aMessage;
    if(anArg1!=anArg2) {
        std::cout << " Error! " << std::endl;
        return 1;
    }
    std::cout << " ok " << std::endl;
    return 0;
}


int SFTestHarness::runDateTests() {
    int theResult = 0;
    std::cout << "Test SFDate class" << std::endl;
    // test constructors and toString function
    SFDate d1("02/28/2018");
    SFDate d2(2, 15, 2018);
    SFDate d3(d1);
    SFDateTime dt1(2, 10, 2018, 12, 30, 15);
    SFDate d4(dt1);
    SFDate d5("Jan 4, 1961");
    theResult += compare(d1.toDateString(), "02/28/2018", "constructor1");
    theResult += compare(d2.toDateString(), "02/15/2018", "constructor2");
    theResult += compare(d3.toDateString(), "02/28/2018", "constructor3");
    theResult += compare(d4.toDateString(), "02/10/2018", "constructor4");
    theResult += compare(d5.toDateString(), "01/04/1961", "another string format");
    theResult += compare(std::string((const char*)d1), "02/28/2018", "cast to char*");
    // test ++ and -- operators
    ++d1;
    theResult += compare(d1.toDateString(), "03/01/2018", "++");
    --d1;
    theResult += compare(d1.toDateString(), "02/28/2018", "--");
    // test - operators
    theResult += compare(std::string(d1-d2), "0 years, 0 months, 13 days, 0 hours, 0 minutes and 0 seconds", "date - date");
    theResult += compare(std::string(d1-dt1), "0 years, 0 months, 18 days, 0 hours, 0 minutes and 0 seconds", "date - dateTime");
    // test adjustment operations
    d1.adjustByDays(1);
    theResult += compare(d1.toDateString(), "03/01/2018", "adjustByDays");
    d1.adjustByWeeks(4);
    theResult += compare(d1.toDateString(), "03/29/2018", "adjustByWeeks");
    d1.adjustByMonths(-1);
    theResult += compare(d1.toDateString(), "03/01/2018", "adjustByMonths");
    d1.adjustByYears(1);
    theResult += compare(d1.toDateString(), "03/01/2019", "adjustByYears");
    // test set operations
    d1.setDay(30);
    theResult += compare(d1.toDateString(), "03/30/2019", "setByDays");
    d1.setMonth(2);
    theResult += compare(d1.toDateString(), "03/02/2019", "setByMonths");
    d1.setYear(2018);
    theResult += compare(d1.toDateString(), "03/02/2018", "setByYears");
    // test get operations
    theResult += compare(d1.getDay(), 2, "getDay");
    theResult += compare(d1.getMonth(), 3, "getMonth");
    theResult += compare(d1.getYear(), 2018, "getYear");
    theResult += compare(d1.getWeekOfYear(), 9, "getWeekOfYear");
    theResult += compare(d1.getDayOfYear(), 61, "getDayOfYear");
    theResult += compare(d1.getDayOfweek(), 5, "getDayOfWeek");
    theResult += compare(d1.daysInMonth(), 31, "getDaysInMonth");
    // test start & end
    theResult += compare(d1.startOfMonth().toDateString(), "03/01/2018", "startOfMonth");
    theResult += compare(d1.endOfMonth().toDateString(), "03/31/2018", "endOfMonth");
    theResult += compare(d1.startOfYear().toDateString(), "01/01/2018", "startOfYear");
    theResult += compare(d1.endOfYear().toDateString(), "12/31/2018", "endOfYear");

    // test relational opeartors
    theResult += compare(d1 < d2, false, "<");
    theResult += compare(d1 <= d2, false, "<=");
    theResult += compare(d1 > d2, true, ">");
    theResult += compare(d1 >= d2, true, ">=");
    theResult += compare(d1 == d2, false, "==");
    theResult += compare(d1 != d2, true, "!=");
    
    std::cout << "" << std::endl;
    return theResult;
}

int SFTestHarness::runTimeTests() {
    int theResult = 0;
    std::cout << "Test SFTime class" << std::endl;
    // test constructors and toString operator
    SFTime t1("09:05:15");
    SFTime t2(9, 5, 22);
    SFTime t3(t1);
    SFDateTime dt1(2, 10, 2018, 12, 30, 15);
    SFTime t4(dt1);
    theResult += compare(t1.toTimeString(), "09:05:15", "constructor1");
    theResult += compare(t2.toTimeString(), "09:05:22", "constructor2");
    theResult += compare(t3.toTimeString(), "09:05:15", "constructor3");
    theResult += compare(t4.toTimeString(), "12:30:15", "constructor4");
    theResult += compare(std::string((const char*)t1), "09:05:15", "cast to char*");
    // test adjustment operations
    t1.adjustByMinutes(80);
    theResult += compare(t1.toTimeString(), "10:25:15", "adjustByMinutes");
    t1.adjustByHours(-12);
    theResult += compare(t1.toTimeString(), "22:25:15", "adjustByHours");
    // test - operators
    theResult += compare(std::string(t1-t2), "0 years, 0 months, 0 days, 13 hours, 19 minutes and 53 seconds", "time - time");
    theResult += compare(std::string(t1-dt1), "0 years, 0 months, 0 days, 9 hours, 55 minutes and 0 seconds", "time - dateTime");
    // test get operations
    theResult += compare(t1.getHour(), 22, "getHour");
    theResult += compare(t1.getMinutes(), 25, "getMinutes");
    theResult += compare(t1.getSeconds(), 15, "getSeconds");
    // test start & end
    theResult += compare(t1.startOfDay().toTimeString(), "00:00:00", "startOfDay");
    theResult += compare(t1.endOfDay().toTimeString(), "23:59:59", "endOfMonth");
    // test relational opeartors
    theResult += compare(t1 < t2, false, "<");
    theResult += compare(t1 <= t2, false, "<=");
    theResult += compare(t1 > t2, true, ">");
    theResult += compare(t1 >= t2, true, ">=");
    theResult += compare(t1 == t2, false, "==");
    theResult += compare(t1 != t2, true, "!=");
    
    std::cout << "" << std::endl;
    return theResult;
}

int SFTestHarness::runDateTimeTests() {
    int theResult = 0;
    std::cout << "Test SFDateTime class" << std::endl;
    // test constructors and toString function
    SFDateTime dt1(2, 29, 2016, 9, 35, 47);
    SFTimezone tz1("PST");
    SFDateTime dt2(dt1);
    SFDateTime dt3("02/15/2016 09:05:15", &tz1);
    SFDate d1("02/29/2016");
    SFTime t1("09:35::47");
    SFDateTime dt4(d1, t1);
    SFDateTime dt5("Jan 24, 1961 10:11:12");
    theResult += compare(dt1.toDateTimeString(), dt2.toDateTimeString(), "constructor");
    theResult += compare(dt3.toDateTimeString(), "Feb 15, 2016 09:05:15 PST", "constructor");
    theResult += compare(dt4.toDateTimeString(), dt1.toDateTimeString(), "constructor");
    theResult += compare(dt5.toDateTimeString(), "Jan 24, 1961 10:11:12 GMT", "another string format");
    // test -
    theResult += compare(std::string(dt1-dt3), "0 years, 0 months, 13 days, 16 hours, 30 minutes and 32 seconds", "datetime - datetime");
    // test timezone
    theResult += compare(std::string(dt1.getTimezone()), "GMT", "get timezone");
    theResult += compare(dt1.setTimezone(tz1).toDateTimeString(), "Feb 29, 2016 01:35:47 PST", "set timezone");
    // relational operators
    theResult += compare(dt2 < dt3, false, "<");
    theResult += compare(dt2 <= dt3, false, "<=");
    theResult += compare(dt2 > dt3, true, ">");
    theResult += compare(dt2 >= dt3, true, ">=");
    theResult += compare(dt2 == dt3, false, "==");
    theResult += compare(dt2 != dt3, true, "!=");
    // convert operators
    theResult += compare(std::string((const char*)dt1), "Feb 29, 2016 01:35:47 PST", "cast to char*");
    theResult += compare(((SFDate)dt1).toDateString(), "02/29/2016", "cast to SFDate");
    theResult += compare(((SFTime)dt1).toTimeString(), "01:35:47", "cast to SFTime");
    SFTimezone tz2 = dt1;
    theResult += compare(std::string((const char*)tz2), "PST", "cast to SFTimezone");

    
    std::cout << "" << std::endl;
    return theResult;
}

int SFTestHarness::runIntervalTests() {
    SFInterval inte(1,2,3,4,5,6);
    return compare(std::string(inte), "1 years, 2 months, 3 days, 4 hours, 5 minutes and 6 seconds", "test SFInterval");
}

int SFTestHarness::runTimezoneTests() {
    int theResult = 0;
    // constructors
    SFTimezone tz1("PST");
    SFTimezone tz2(tz1);
    // to char*
    theResult += compare(std::string(tz1), "PST", "test SFTimezone");
    theResult += compare(std::string(tz2), "PST", "test SFTimezone copy");
    std::cout << "" << std::endl;
    return theResult;
}

int SFTestHarness::providedTests(){
    int theResult = 0;
    std::cout << "Run provided tests" << std::endl;
    // test date difference
    std::string s1("02/15/2018"), s2("02/17/2018");
    std::string res1 = dateDifferenceTest(s1, s2);
    std::string ans1 = "0 years, 0 months, 2 days, 0 hours, 0 minutes and 0 seconds";
    theResult += compare(res1, ans1, "date difference");
    // test adjust by weeks
    std::string res2 = adjustDateByWeeksTest(s1, 1);
    std::string ans2 = "02/22/2018";
    theResult += compare(res2, ans2, "adjust date by week");
    // test month set
    std::string res3 = setMonthDateTest(s1, 5);
    std::string ans3 = "05/15/2018";
    theResult += compare(res3, ans3, "set month date");
    // test get day of week
    int res4 = getDayOfWeekDateTest(s1);
    int ans4 = 4;
    theResult += compare(res4, ans4, "get day of week");
    // test end of month
    std::string s3("03/15/2018");
    std::string res5 = endOfMonthDateTest(s3);
    std::string ans5 = "03/31/2018";
    theResult += compare(res5, ans5, "end of month");
    // test time difference
    std::string t1("09:05:15"), t2("09:05:22");
    std::string res6 = timeDifferenceTest(t1, t2);
    std::string ans6 = "0 years, 0 months, 0 days, 0 hours, 0 minutes and 7 seconds";
    theResult += compare(res6, ans6, "time difference");
    // test adjust time by minutes
    std::string res7 = adjustTimeByMinutesTest(t1, 5);
    std::string ans7 = "09:10:15";
    theResult += compare(res7, ans7, "adjust time by minutes");
    // test get minutes
    int res8 = getMinutesTimeTest(t1);
    int ans8 = 5;
    theResult += compare(res8, ans8, "get minutes");
    // datetime difference
    std::string dt1("02/15/2018 09:05:15"), dt2("02/15/2018 11:05:15"), tz1("PST"), tz2("EST");
    std::string res9 = dataTimeDifferenceTest(dt1, tz1, dt2, tz2);
    std::string ans9 = "0 years, 0 months, 0 days, 1 hours, 0 minutes and 0 seconds";
    theResult += compare(res9, ans9, "datetime difference");
    // datetime to string
    std::string res10 = dataTimeToStringTest(dt1, tz1);
    std::string ans10 = "Feb 15, 2018 09:05:15 PST";
    theResult += compare(res10, ans10, "datetime tostring");
    // timezone conversion
    std::string res11 = timezoneConversionDateTimeTest(dt1, tz1);
    std::string ans11 = "Feb 15, 2018 01:05:15 PST";
    theResult += compare(res11, ans11, "timezone conversion");
    // relational operator
    bool res12 = greaterThanDateTimeTest(dt1, tz1, dt2, tz2);
    bool ans12 = true;
    theResult += compare(res12, ans12, "greater than");
    return theResult;
}

/*
 * Return string representation of interval between two dates
 * Ex. aDate1 = "02/15/2018"
 *     aDate2 = "02/17/2018"
 * Returns : "0 years, 0 months, 2 days, 0 hours, 0 minutes and 0 seconds"
 */
std::string SFTestHarness::dateDifferenceTest(std::string aDate1, std::string aDate2) {
    SFDate theDate1(aDate1.c_str());
    SFDate theDate2(aDate2.c_str());
    SFInterval dateDiff = theDate1 - theDate2;
    std::string res(dateDiff);
    return res;
}

/*
 * Return string representation of date with weeks adjusted
 * Ex. aDate = "02/15/2018"
 *     aWeeks = 1
 * Returns : "02/22/2018"
 */
std::string SFTestHarness::adjustDateByWeeksTest(std::string aDate, int aWeeks) {
    SFDate theDate(aDate.c_str());
    theDate.adjustByWeeks(aWeeks);
    return theDate.toDateString();
}

/*
 * Return string representation of date with month changed
 * Ex. aDate = "02/15/2018"
 *     aMonth = 5
 * Returns : "05/15/2018"
 */
std::string SFTestHarness::setMonthDateTest(std::string aDate, int aMonth) {
    SFDate theDate(aDate.c_str());
    theDate.setMonth(aMonth);
    return theDate.toDateString();
}

/*
 * Return integer representation of the day of the week for the given date
 * Ex. aDate = "02/15/2018"
 * Returns : 4
 */
int SFTestHarness::getDayOfWeekDateTest(std::string aDate) {
    SFDate theDate(aDate.c_str());
    return theDate.getDayOfweek();
}

/*
 * Return string representation of date at the end of month of the given date
 * Ex. aDate = "03/15/2018"
 * Returns : "03/31/2018"
 */
std::string SFTestHarness::endOfMonthDateTest(std::string aDate) {
    SFDate theDate(aDate.c_str());
    return theDate.endOfMonth().toDateString();
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aTime2 = "09:05:22"
 * Returns : "0 years, 0 months, 0 days, 0 hours, 0 minutes and 7 seconds"
 */
std::string SFTestHarness::timeDifferenceTest(std::string aTime1, std::string aTime2) {
    SFTime theTime1(aTime1.c_str()), theTime2(aTime2.c_str());
    SFInterval timeDiff = theTime1 - theTime2;
    std::string res(timeDiff);
    return res;
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aMinutes = 5
 * Returns : "09:10:15"
 */
std::string SFTestHarness::adjustTimeByMinutesTest(std::string aTime1, int aMinutes) {
    SFTime theTime(aTime1.c_str());
    theTime.adjustByMinutes(aMinutes);
    return theTime.toTimeString();
}

/*
 * Return minutes from the given time
 * Ex. aTime = "09:05:15"
 * Returns : 5
 */
int SFTestHarness::getMinutesTimeTest(std::string aTime) {
    SFTime theTime(aTime.c_str());
    return theTime.getMinutes();
}

/*
 * Return string representation of interval between two times
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : "0 years, 0 months, 0 days, 1 hours, 0 minutes and 0 seconds"
 */
std::string SFTestHarness::dataTimeDifferenceTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {
    SFTimezone theTimezone1(aTimezone1.c_str());
    SFTimezone theTimezone2(aTimezone2.c_str());
    SFDateTime theDateTime1(aDateTime1.c_str(), &theTimezone1);
    SFDateTime theDateTime2(aDateTime2.c_str(), &theTimezone2);
    SFInterval diff = theDateTime1 - theDateTime2;
    std::string res(diff);
    return res;
}

/*
 * Return string representation of given date-time
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 09:05:15 PST"
 */
std::string SFTestHarness::dataTimeToStringTest(std::string aDateTime, std::string timezone) {
    SFTimezone theTimezone(timezone.c_str());
    SFDateTime theDateTime(aDateTime.c_str(), &theTimezone);
    return theDateTime.toDateTimeString();
}

/*
 * Return string representation of given GMT date-time converted to given timezone
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 01:05:15 PST"
 */
std::string SFTestHarness::timezoneConversionDateTimeTest(std::string aDateTime, std::string timezone) {
    SFDateTime theDateTime(aDateTime.c_str());
    SFTimezone theTimezone(timezone.c_str());
    theDateTime.timezoneConvert(theTimezone);
    return theDateTime.toDateTimeString();
}

/*
 * Return true if aDateTime1 is stricty greater than aDateTime2
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : true
 */
bool SFTestHarness::greaterThanDateTimeTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {
    SFTimezone theTimezone1(aTimezone1.c_str());
    SFTimezone theTimezone2(aTimezone2.c_str());
    SFDateTime theDateTime1(aDateTime1.c_str(), &theTimezone1);
    SFDateTime theDateTime2(aDateTime2.c_str(), &theTimezone2);
    return theDateTime1 > theDateTime2;
}

int SFTestHarness::runAllTests() {
    int theResult = runDateTests();
    theResult+=runTimeTests();
    theResult+=runDateTimeTests();
    theResult+=runIntervalTests();
    theResult+=runTimezoneTests();
    theResult+=providedTests();
    std::cout << theResult << " errors found -- " << (theResult ? "too bad!" : "woot!") << std::endl;
    return theResult;
}
