#ifndef StoreRun_h_wxWidgets_Running_Log
#define StoreRun_h_wxWidgets_Running_Log

#include <vector>
#include "DayRun.h"
#include <wx/string.h>
#include <iostream>
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
  bool AddDistance(const double, Dates);
  bool AddFeeling(int, Dates);
  
  int idOfDay(Dates);

  std::vector<DayRun> storage;

};


#endif
