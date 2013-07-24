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
std::cout << scomm << std::endl;
return AddComments(scomm, td);
}

bool StoreRun::AddComments(const wxChar* comm, Dates td)
{
std::string scomm = std::string(wxString(comm).mb_str());
std::cout << scomm << std::endl;
return AddComments(scomm, td);
}

bool StoreRun::AddComments(Dates td, std::string d)
{ return AddComments(d, td); }

bool StoreRun::AddComments(std::string com, Dates td)
{
int i=idOfDay(td); 
if(i != -1)
  storage[i].comments = com;
else
  storage.push_back(DayRun(td, com, std::string(""), 0, 0, true));

return true;
}
