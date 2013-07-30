#ifndef Dates_h_wxWidgets_RunningLog
#define Dates_h_wxWidgets_RunningLog

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

/*********************
 *Stores individual dates
 *Stores as a struct tm, not a time_t
 ********************/

class Dates
{
public:
Dates();
Dates(const Dates&);
Dates(int);
Dates(int, int, int);
void set();
void set(const Dates&);
void set(int);
void set(int, int, int);
Dates setNew(int) const;
Dates setNew(int, int, int) const;
Dates weekBegin() const;
void weekBegin(int&, int&, int&) const;
Dates weekBegin(int) const;
void weekBegin(int, int&, int&, int&) const;
int year() const;
int day() const;
int month() const;
//Dates weekBegin(int) const;
std::string dow() const;
std::string FullDate() const; 
std::string DateWithoutDow() const; 
std::string ShortDate() const;
bool operator== (const Dates&) const;
bool operator!= (const Dates&) const;
bool operator< (const Dates&) const;
bool operator<= (const Dates&) const;
bool operator> (const Dates&) const;
bool operator>= (const Dates&) const;

static std::string its(int);
static std::string iits(int);
static std::string intToMonth(int);
static std::string intToShortMonth(int);
static int ShortMonthToInt(std::string);
static double stringToDouble(std::string);
static std::string doubleToString(double);
static int power(int, int);

//time_t Ctime;
struct tm Ctime;

};

enum{
DAYS_SUNDAY = 0,
DAYS_MONDAY = 1,
DAYS_TUESDAY = 2,
DAYS_WEDNESDAY = 3,
DAYS_THURSDAY = 4,
DAYS_FRIDAY = 5,
DAYS_SATURDAY = 6,
DAYS_BEGIN_WEEK = 1
};


#endif
