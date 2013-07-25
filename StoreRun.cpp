#include "StoreRun.h"

StoreRun::StoreRun()
{}

int StoreRun::idOfDay(Dates td)
{
for(int i=0;i<storage.size();++i)
  {
  if(storage[i].day == td)
    return i;
  }
return -1;
}

bool StoreRun::AddComments(Dates td, const wxChar* comm)
{
std::string scomm = std::string(wxString(comm).mb_str());
return AddComments(scomm, td);
}

bool StoreRun::AddComments(const wxChar* comm, Dates td)
{
std::string scomm = std::string(wxString(comm).mb_str());
return AddComments(scomm, td);
}

bool StoreRun::AddComments(Dates td, std::string d)
{ return AddComments(d, td); }

bool StoreRun::AddComments(std::string com, Dates td)
{
std::cout << "SR::AC" << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].comments = com;
else
  storage.push_back(DayRun(td, com, std::string(""), 0.0, 0.0, true, 5));
return true;
}

bool StoreRun::AddMoreComments(Dates td, const wxChar* comm)
{
std::string scomm = std::string(wxString(comm).mb_str());
return AddMoreComments(scomm, td);
}

bool StoreRun::AddMoreComments(const wxChar* comm, Dates td)
{
std::string scomm = std::string(wxString(comm).mb_str());
return AddMoreComments(scomm, td);
}

bool StoreRun::AddMoreComments(Dates td, std::string d)
{ return AddMoreComments(d, td); }

bool StoreRun::AddMoreComments(std::string com, Dates td)
{
std::cout << "SR::AMC" << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].moreComments = com;
else
  storage.push_back(DayRun(td, std::string(""), com, 0.0, 0.0, true, 5));
return true;
}

bool StoreRun::AddTime(double t, Dates td)
{
std::cout << "SR::ATime" << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].time = t;
else
  storage.push_back(DayRun(td, std::string(""), std::string(""), t, 0.0, true, 5));
return true;
}

bool StoreRun::AddType(bool t, Dates td)
{
std::cout << "SR::AType" << t << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].milesOrKm = t;
else
  storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, 0.0, t, 5));
return true;
}

bool StoreRun::AddMilesOrKm(bool t, Dates td)
{ return AddType(t, td); }

bool StoreRun::AddDistance(const double d, Dates td)
{
std::cout << "SR:AD " << d << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].distance=d;
else
  storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, d, true, 5));
return true;
}

bool StoreRun::AddFeeling(int f, Dates td)
{
std::cout << "SR:AF" << f << std::endl;
int i=idOfDay(td); 
if(i != -1)
  storage[i].feeling=f;
else
  storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, 0.0, true, f));
return true;
}
