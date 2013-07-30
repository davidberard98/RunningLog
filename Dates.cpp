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

void Dates::set(const Dates& in)
  {
  time_t x;
  struct tm inCtime = in.Ctime;
  x= mktime ( &inCtime );
  Ctime = *localtime ( &x );
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
  if(weekbegind > Ctime.tm_wday) //explained below
     x-= 7*24*60*60;
  struct tm di = *localtime (&x); //change the time back into a struct tm
  d=di.tm_mday; //day of month [1-31]
  m=di.tm_mon; //month of year [0-11]
  y=di.tm_year+1900; //year [1900-...]

  // sun  mon  tue  wed  thu  fri  sat  sun
  // 0a   1a   2a   3a   4a   5a   6a   7a
  // 0b   1b   2b   3b   4b   5b   6b   7b
  // -> begins on wednesday (3)
  // If we get 1b (monday week 2), it'll say (3-1) = 2, so add 2 =3b.  However, that week
  // begins on 3a, not 3b, so when weekbegin > date, subtract a week.
  }

int Dates::year() const
  {
  return (Ctime.tm_year+1900); //returns integer year (like 2013)
  }

int Dates::month() const
  {
  return Ctime.tm_mon;
  }

int Dates::day() const
  {
  return Ctime.tm_mday;
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

std::string Dates::DateWithoutDow() const //returns date in word form
  {
  char o [80];
  strftime(o, 80, "%B %e %G", &Ctime);
  return std::string(o);
  }

std::string Dates::ShortDate() const
  {
  std::string o = its(Ctime.tm_mon+1) + "/" + its(Ctime.tm_mday);
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

bool Dates::operator!= (const Dates& tc) const
  {
  int d=tc.Ctime.tm_mday;
  int m=tc.Ctime.tm_mon;
  int y=tc.Ctime.tm_year;
  if(d == Ctime.tm_mday && m == Ctime.tm_mon && y == Ctime.tm_year)
    return false;
  return true;
  }

bool Dates::operator< (const Dates& tc) const
  {
  //set the same seconds/minutes for both [only checking day, month, year]
  time_t now;
  time ( &now );
  struct tm thisCtime = *localtime ( &now );
  thisCtime.tm_mday = Ctime.tm_mday; thisCtime.tm_mon = Ctime.tm_mon; thisCtime.tm_year = Ctime.tm_year;
  struct tm thatCtime = *localtime ( &now );
  thatCtime.tm_mday = tc.Ctime.tm_mday; thatCtime.tm_mon = tc.Ctime.tm_mon; thatCtime.tm_year = tc.Ctime.tm_year;
  //change to time_t (integer)
  time_t thistime = mktime ( &thisCtime );
  time_t thattime = mktime ( &thatCtime );
  if(thistime < thattime)
    return true;
  return false;
  }

bool Dates::operator> (const Dates& tc) const
  {
  //set the same seconds/minutes for both [only checking day, month, year]
  time_t now;
  time ( &now );
  struct tm thisCtime = *localtime ( &now );
  thisCtime.tm_mday = Ctime.tm_mday; thisCtime.tm_mon = Ctime.tm_mon; thisCtime.tm_year = Ctime.tm_year;
  struct tm thatCtime = *localtime ( &now );
  thatCtime.tm_mday = tc.Ctime.tm_mday; thatCtime.tm_mon = tc.Ctime.tm_mon; thatCtime.tm_year = tc.Ctime.tm_year;
  //change to time_t (integer)
  time_t thistime = mktime ( &thisCtime );
  time_t thattime = mktime ( &thatCtime );
  if(thistime > thattime)
    return true;
  return false;
  }

bool Dates::operator>= (const Dates& tc) const
  {
  //set the same seconds/minutes for both [only checking day, month, year]
  time_t now;
  time ( &now );
  struct tm thisCtime = *localtime ( &now );
  thisCtime.tm_mday = Ctime.tm_mday; thisCtime.tm_mon = Ctime.tm_mon; thisCtime.tm_year = Ctime.tm_year;
  struct tm thatCtime = *localtime ( &now );
  thatCtime.tm_mday = tc.Ctime.tm_mday; thatCtime.tm_mon = tc.Ctime.tm_mon; thatCtime.tm_year = tc.Ctime.tm_year;
  //change to time_t (integer)
  time_t thistime = mktime ( &thisCtime );
  time_t thattime = mktime ( &thatCtime );
  if(thistime >= thattime)
    return true;
  return false;
  }

bool Dates::operator<= (const Dates& tc) const
  {
  //set the same seconds/minutes for both [only checking day, month, year]
  time_t now;
  time ( &now );
  struct tm thisCtime = *localtime ( &now );
  thisCtime.tm_mday = Ctime.tm_mday; thisCtime.tm_mon = Ctime.tm_mon; thisCtime.tm_year = Ctime.tm_year;
  struct tm thatCtime = *localtime ( &now );
  thatCtime.tm_mday = tc.Ctime.tm_mday; thatCtime.tm_mon = tc.Ctime.tm_mon; thatCtime.tm_year = tc.Ctime.tm_year;
  //change to time_t (integer)
  time_t thistime = mktime ( &thisCtime );
  time_t thattime = mktime ( &thatCtime );
  if(thistime <= thattime)
    return true;
  return false;
  }

std::string Dates::its(int tc) //int to string
  {
  std::string to;
  if(tc == 0)
    to="0";
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

std::string Dates::intToShortMonth(int mtc)
  {
  switch(mtc)
    {
    case 0: return "Jan"; break;
    case 1: return "Feb"; break;
    case 2: return "Mar"; break;
    case 3: return "Apr"; break;
    case 4: return "May"; break;
    case 5: return "Jun"; break;
    case 6: return "Jul"; break;
    case 7: return "Aug"; break;
    case 8: return "Sep"; break;
    case 9: return "Oct"; break;
    case 10: return "Nov"; break;
    case 11: return "Dec"; break;
    default: return "";break;
    }
  return "";
  }

int Dates::ShortMonthToInt(std::string in)
  {
  if(in == "Jan")
    return 0;
  if(in == "Feb")
    return 1;
  if(in == "Mar")
    return 2;
  if(in == "Apr")
    return 3;
  if(in == "May")
    return 4;
  if(in == "Jun")
    return 5;
  if(in == "Jul")
    return 6;
  if(in == "Aug")
    return 7;
  if(in == "Sep")
    return 8;
  if(in == "Oct")
    return 9;
  if(in == "Nov")
    return 10;
  if(in == "Dec")
    return 11;
  return -1;
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
  while(int(afta*100000) != 0)//floating point isn't exact, so double(6) - int(6) = 0.000000000355, so you want that to equal 0 
    {
    afta *=10;
    aftb *=10;
    aftb +=int(afta+0.000001); //sometimes afta = 6 is actually afta = 5.99999999932, so add 0.000001 to offset that
    afta -= int(afta+0.000001); 
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
