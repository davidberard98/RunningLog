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
  int idOfDay(Dates);

  std::vector<DayRun> storage;

};


#endif
