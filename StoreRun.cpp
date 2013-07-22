#include "StoreRun.h"

StoreRun::StoreRun()
{}

int StoreRun::idOfDay(int a, int b, int c)
{
for(int i=0;i<storage.size();++i)
  {
  if(storage[i].day == a && storage[i].month == b && storage[i].year == c)
    return i;
  }
return -1;
}

bool StoreRun::AddComments(int a, int b, int c, const wxChar* comm)
{
std::string scomm = std::string(wxString(comm).mb_str());
std::cout << scomm << std::endl;
return AddComments(scomm, a, b, c);
}

bool StoreRun::AddComments(const wxChar* comm, int a, int b, int c)
{
std::string scomm = std::string(wxString(comm).mb_str());
std::cout << scomm << std::endl;
return AddComments(scomm, a, b, c);
}

bool StoreRun::AddComments(int a, int b , int c, std::string d)
{ return AddComments(d, a, b, c); }

bool StoreRun::AddComments(std::string com, int d, int m, int y)
{
int i=idOfDay(d, m, y);
if(i != -1)
  storage[i].comments = com;
else
  storage.push_back(DayRun(d, m, y, com, std::string(""), 0, 0, true));

return true;
}
