#include "Dates.h"

Dates::Dates() // sets time to current time
  {
  time_t x;
  time(&x);
  Ctime = *localtime( &x );
  }

Dates::Dates(const Dates& ts) // sets time based on the Dates passed in
  {
  Ctime=ts.Ctime;
  }

Dates::Dates(int off) // sets time based on current time + the number of days off
  {
  time_t x;
  time(&x);
  Ctime = *localtime( &x );
  set(off);
  }

Dates::Dates(int d, int m, int y) // sets time based on day, month, year passed to it
  {
  time_t x;
  time(&x);
  struct tm dateinfo;
  dateinfo = *localtime( &x );
  dateinfo.tm_mday = d;
  dateinfo.tm_mon = m;
  dateinfo.tm_year = y-1900;
  x=mktime(&dateinfo);
  Ctime = *localtime(&x);
  }

void Dates::set() // sets time to current time
  {
  time_t x;
  time(&x);
  Ctime = *localtime( &x );
  }

void Dates::set(int off) // adds or subtracts off to the current date
  {
  int d, m, y;
  time_t x = mktime(&Ctime);
  x+= off*24*60*60;
  Ctime = *localtime (&x);
  }

void Dates::set(int d, int m, int y) // sets time to the day, month, year passed to it
  {
  struct tm dateinfo = Ctime;
  dateinfo.tm_mday = d;
  dateinfo.tm_mon = m;
  dateinfo.tm_year = y-1900;
  time_t x=mktime(&dateinfo);
  dateinfo=*localtime(&x);
  Ctime = dateinfo;
  }

Dates Dates::setNew(int off) const //returns a new Dates with an offset of (off) days
  {
  Dates m(*this);
  m.set(off);
  return m;
  }
  
Dates Dates::setNew(int d, int m, int y) const //returns a new Dates with Dates(d, m, y)
  {
  Dates x(*this);
  x.set(d,m,y);
  return x;
  }

Dates Dates::weekBegin() const //returns the date that a week begins, based on the const DAYS_BEGIN_WEEK
  {
  int d, m, y;
  weekBegin(DAYS_BEGIN_WEEK, d, m, y);
  return Dates(d, m, y);
  }

Dates Dates::weekBegin(int wb) const //returns day that a week begins, and week begins on wb.
  {
  int d, m, y;
  weekBegin(wb, d, m, y);
  return Dates(d, m, y);
  }

void Dates::weekBegin(int& d, int& m, int& y) const //the below function, but with the beginning of the week = DAYS_BEGIN_WEEK
  {
  weekBegin(DAYS_BEGIN_WEEK, d, m, y);
  }

void Dates::weekBegin(int weekbegind, int& d, int& m, int& y) const // returns d, m, y with the day a week begins on based on weekbegind as the week start
  {
  weekbegind = weekbegind%7;
  struct tm CtimeCopy = Ctime; //copy
  time_t x=mktime(&CtimeCopy); //change struct tm to a time_t
  x+=(weekbegind-Ctime.tm_wday)*24*60*60; //subtract the days since the week began (multiply by 24*60*60 since it is in seconds)
  struct tm di = *localtime (&x); //change the time back into a struct tm
  d=di.tm_mday; //day of month [1-31]
  m=di.tm_mon; //month of year [0-11]
  y=di.tm_year+1900; //year [1900-...]
  }

std::string Dates::dow() const //day of week
  {
  char aname [10];
  strftime(aname, 10, "%A", &Ctime);
  return std::string(aname);
  }

std::string Dates::FullDate() const //returns date in word form
  {
  char o [80];
  strftime(o, 80, "%A %B %e %G", &Ctime);
  return std::string(o);
  }

bool Dates::operator== (const Dates& tc) const
  {
  int d=tc.Ctime.tm_mday;
  int m=tc.Ctime.tm_mon;
  int y=tc.Ctime.tm_year;
  if(d == Ctime.tm_mday && m == Ctime.tm_mon && y == Ctime.tm_year)
    return true;
  return false;
  }

std::string Dates::its(int tc) //int to string
  {
  std::string to;
  while(tc != 0)
    {
    int dig = tc%10;
    int md = tc - dig;
    tc = md/10;
    to = iits(dig)+to;
    }
  return to;
  }

std::string Dates::iits(int tc)
{
  switch(tc)
    {
    case 0: return "0"; break;
    case 1: return "1"; break;
    case 2: return "2"; break;
    case 3: return "3"; break;
    case 4: return "4"; break;
    case 5: return "5"; break;
    case 6: return "6"; break;
    case 7: return "7"; break;
    case 8: return "8"; break;
    case 9: return "9"; break;
    default:return ""; break;
    }
  return "";
  }

std::string Dates::intToMonth(int mtc)
  {
  switch(mtc)
    {
    case 0: return "January"; break;
    case 1: return "February"; break;
    case 2: return "March"; break;
    case 3: return "April"; break;
    case 4: return "May"; break;
    case 5: return "June"; break;
    case 6: return "July"; break;
    case 7: return "August"; break;
    case 8: return "September"; break;
    case 9: return "October"; break;
    case 10: return "November"; break;
    case 11: return "December"; break;
    default: return "";break;
    }
  return "";
  }

double Dates::stringToDouble(std::string in)
  {
  int bef =0;
  int aft =0;
  int as =0;
  bool boa = false;
  for(int i=0;i<in.length();++i)
    {
    if(in.at(i) == '.')
      boa = true;
    if(in.at(i) >= 48 && in.at(i) <= 57)
      {
      if(boa == false)
        {
        bef*=10;
        bef+=int(in.at(i)-48);
        }
      else
        {
        aft*=10;
        aft+=int(in.at(i)-48);
        ++as;
        }
      }
    }
  double out = bef + double(aft)/power(10,as);
  return out;
  }

std::string Dates::doubleToString(double in)
  {
  std::string out = its(int(in));
  double afta = in-int(in);
  int aftb = 0;
  while(afta != 0.0)
    {
    afta *=10;
    aftb *=10;
    aftb +=int(afta);
    afta -= int(afta);
    }
  if(aftb!=0)
    {
    out+="."+its(aftb);
    }
  return out;
  }

int Dates::power (int base, int exp)
  {
  int nb=1;
  for(int i=0;i<exp; ++i)
    nb*=base;
  return nb;
  }
