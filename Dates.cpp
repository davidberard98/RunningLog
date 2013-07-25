#include "Dates.h"

Dates::Dates()
{
time_t x;
time(&x);
Ctime = *localtime( &x );
}

Dates::Dates(const Dates& ts)
{
Ctime=ts.Ctime;
}

Dates::Dates(int off)
{
time_t x;
time(&x);
Ctime = *localtime( &x );
set(off);
}

Dates::Dates(int d, int m, int y)
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

void Dates::set()
{
time_t x;
time(&x);
Ctime = *localtime( &x );
}

void Dates::set(int off)
{
int d, m, y;
time_t x = mktime(&Ctime);
x+= off*24*60*60;
Ctime = *localtime (&x);
}

void Dates::set(int d, int m, int y)
{
struct tm dateinfo = Ctime;
dateinfo.tm_mday = d;
dateinfo.tm_mon = m;
dateinfo.tm_year = y-1900;
time_t x=mktime(&dateinfo);
dateinfo=*localtime(&x);
Ctime = dateinfo;
}

Dates Dates::setNew(int off) const
{
Dates m(*this);
m.set(off);
return m;
}

Dates Dates::setNew(int d, int m, int y) const
{
Dates x(*this);
x.set(d,m,y);
return x;
}

Dates Dates::weekBegin() const
{
int d, m, y;
weekBegin(DAYS_BEGIN_WEEK, d, m, y);
return Dates(d, m, y);
}

Dates Dates::weekBegin(int wb) const
{
int d, m, y;
weekBegin(wb, d, m, y);
return Dates(d, m, y);
}

void Dates::weekBegin(int& d, int& m, int& y) const
{
weekBegin(DAYS_BEGIN_WEEK, d, m, y);
}

void Dates::weekBegin(int weekbegind, int& d, int& m, int& y) const
  {
  weekbegind = weekbegind%7;
  struct tm ctc = Ctime;
  time_t x=mktime(&ctc);
  x+=(weekbegind-Ctime.tm_wday)*24*60*60;
  struct tm di = *localtime (&x);
  d=di.tm_mday;
  m=di.tm_mon;
  y=di.tm_year+1900;
  }

std::string Dates::dow() const
  {
  char aname [10];
  strftime(aname, 10, "%A", &Ctime);
  return std::string(aname);
  }

std::string Dates::FullDate() const
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

std::string Dates::its(int tc)
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

int Dates::power (int base, int exp)
{
int nb=1;
for(int i=0;i<exp; ++i)
  nb*=base;
return nb;
}
