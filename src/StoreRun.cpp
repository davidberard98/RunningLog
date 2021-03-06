#include "StoreRun.h"

StoreRun::StoreRun()
  {}

int StoreRun::idOfDay(Dates td) const //days are stored in vector, so it finds the position of that day in the vector
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
//  std::cout << "SR::AC" << std::endl;
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
//  std::cout << "SR::AMC" << std::endl;
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].moreComments = com;
  else
    storage.push_back(DayRun(td, std::string(""), com, 0.0, 0.0, true, 5));
  return true;
  }

bool StoreRun::AddTime(double t, Dates td)
  {
//  std::cout << "SR::ATime " << t << " " << int(t/3600) << ":" << int((t-int(t/3600)*3600)/60) << ":" << t-int((t-int(t/3600)*3600)/60)*60-int(t/3600)*3600 <<std::endl;
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].time = t;
  else
    storage.push_back(DayRun(td, std::string(""), std::string(""), t, 0.0, true, 5));
  return true;
  }

bool StoreRun::AddType(bool t, Dates td)
  {
//  std::cout << "SR::AType" << t << std::endl;
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].milesOrKm = t;
  else
    storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, 0.0, t, 5));
  return true;
  }

bool StoreRun::AddMilesOrKm(bool t, Dates td)
  { return AddType(t, td); }

bool StoreRun::AddDistance(double d, Dates td)
  {
  if(d != -1.0)
    {
    int i=idOfDay(td); 
    if(i != -1)
      storage[i].distance=d;
    else
      {
      i=storage.size();
      storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, d, true, 5));
      }
//    std::cout << "SR:AD " << d << " " << storage[i].distance << std::endl;
    }
  return true;
  }

bool StoreRun::AddFeeling(int f, Dates td)
  {
//  std::cout << "SR:AF" << f << std::endl;
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].feeling=f;
  else
    storage.push_back(DayRun(td, std::string(""), std::string(""), 0.0, 0.0, true, f));
  return true;
  }

bool StoreRun::AddSeason(std::string seas, Dates td)
  {
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].season=seas;
  else
    storage.push_back(DayRun(td, -1, seas));
  return true;
  }

bool StoreRun::AddSeason(std::string seas, int wn, Dates td)
  {
  int i=idOfDay(td); 
  if(i != -1)
    {
    storage[i].season=seas;
    storage[i].week=wn;
    }
  else
    storage.push_back(DayRun(td, wn, seas));
  return true;
  }

bool StoreRun::AddWeekNumber(int wn, Dates td)
  {
  int i=idOfDay(td); 
  if(i != -1)
    storage[i].week=wn;
  else
    storage.push_back(DayRun(td, wn, ""));
  return true;
  }

bool StoreRun::AddWeek(int wn, Dates td)
  {
  return AddWeekNumber(wn, td);
  }

std::vector<std::string> StoreRun::ListSeasons() const
  {
  std::vector<std::string> out;
  ListSeasons(out);
  return out;
  }

bool StoreRun::save()
  {
  pugi::xml_document doc;

  pugi::xml_node RL = doc.append_child("RL");
  
  for(int i=0;i<storage.size();++i)
    {
    storage[i].XML(RL);
    }
  
  doc.save_file("DavidBerard.xml");
  std::cout << "Successfully saved" << std::endl;

  return true;
  }

bool StoreRun::open()
  {
  storage.clear();

  pugi::xml_document doc;
  doc.load_file("DavidBerard.xml");

  pugi::xml_node RL = doc.child("RL");

  for(pugi::xml_node DR = RL.child("DayRun"); DR; DR = DR.next_sibling("DayRun"))
    {
    storage.push_back(DayRun(DR));
    }
  
  return true;
  }

void StoreRun::ListSeasons(std::vector<std::string> &seas) const
  {
  seas.clear();
  for(int i=0;i<storage.size();++i) // look through every day stored
    {
    if(storage[i].season != "") //don't look at days with a null season
      {
      bool found=false;
      for(int j=0;j<seas.size();++j) //compare to all the seasons that have already been seen
        {
        if(storage[i].season == seas[j])
          {
          found=true;
          break;
          }
        }
      if(found ==false)
        seas.push_back(storage[i].season);
      }
    }
  }

std::string StoreRun::season(Dates day) const
  {
  int id = idOfDay(day);
  std::string out;
  if(id != -1)
    out = storage[id].season;
  else
    out = "";
  return out;
  }

std::string StoreRun::GetSeason(Dates day) const
  {
  return season(day);
  }

int StoreRun::GetWeekNumber(Dates day) const
  {
  return WeekNumber(day);
  }

int StoreRun::WeekNumber(Dates day) const
  {
  int id = idOfDay(day);
  int out =-1;
  if(id != -1)
    out = storage[id].week;
  return out;
  }

double StoreRun::GetDistance(Dates day) const
  {
  int id = idOfDay(day);
  double out =-1.0;
  if(id != -1)
    out = storage[id].distance;
  return out;
  }

std::string StoreRun::GetComments(Dates day) const
  {
  int id = idOfDay(day);
  std::string out ="";
  if(id != -1)
    out = storage[id].comments;
  return out;
  }

std::string StoreRun::GetMoreComments(Dates day) const
  {
  int id = idOfDay(day);
  std::string out ="";
  if(id != -1)
    out = storage[id].moreComments;
  return out;
  }

double StoreRun::GetTime(Dates day) const
  {
  int id = idOfDay(day);
  double out =0;
  if(id != -1)
    out = storage[id].time;
  return out;
  }

int StoreRun::GetFeeling(Dates day) const
  {
  int id = idOfDay(day);
  int out =0;
  if(id != -1)
    out = storage[id].feeling;
  return out;
  }

bool StoreRun::GetType(Dates day) const
  {
  int id = idOfDay(day);
  bool out =true;
  if(id != -1)
    out = storage[id].milesOrKm;
  return out;
  }
