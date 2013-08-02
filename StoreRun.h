#ifndef StoreRun_h_wxWidgets_Running_Log
#define StoreRun_h_wxWidgets_Running_Log

#include <vector>
#include "DayRun.h"
#include <wx/string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Dates.h"

class StoreRun
{
public:
  StoreRun();
  bool AddComments(const wxChar*, Dates);
  bool AddComments(Dates, const wxChar*);
  bool AddComments(std::string, Dates);
  bool AddComments(Dates, std::string);
  bool AddMoreComments(const wxChar*, Dates);
  bool AddMoreComments(Dates, const wxChar*);
  bool AddMoreComments(std::string, Dates);
  bool AddMoreComments(Dates, std::string);
  bool AddTime(double, Dates);
  bool AddType(bool, Dates);
  bool AddMilesOrKm(bool, Dates);
  bool AddDistance(double, Dates);
  bool AddFeeling(int, Dates);
  bool AddSeason(std::string, Dates);
  bool AddSeason(std::string, int, Dates);
  bool AddWeekNumber(int, Dates);
  bool AddWeek(int, Dates);
  std::vector<std::string> ListSeasons() const;
  void ListSeasons(std::vector<std::string>&) const;
  std::string season(Dates day) const;
  int WeekNumber(Dates day) const;
  std::string GetSeason(Dates day) const;
  int GetWeekNumber(Dates day) const;
  double GetDistance(Dates day) const;
  std::string GetComments(Dates day) const;
  std::string GetMoreComments(Dates day) const;
  double GetTime(Dates day) const;
  int GetFeeling(Dates day) const;
  bool GetType(Dates day) const;
  bool save();
  bool open();
  
  int idOfDay(Dates) const;

  std::vector<DayRun> storage;

};

#endif
