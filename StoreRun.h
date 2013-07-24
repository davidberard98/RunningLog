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
  bool AddComments(const wxChar*, int, int, int);
  bool AddComments(int, int, int, const wxChar*);
  bool AddComments(std::string, int, int, int);
  bool AddComments(int, int, int, std::string);
                 //comments      d    m   y  
  int idOfDay(int, int, int);

  std::vector<DayRun> storage;

};


#endif
