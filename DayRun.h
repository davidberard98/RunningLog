#ifndef DayRun_h_wxWidgets_Running_Log
#define DayRun_h_wxWidgets_Running_Log

#include <wx/string.h>
#include <string>

#include "Dates.h"

class DayRun
{
public:
  DayRun(Dates);//dmy
  DayRun(Dates, int, std::string);//dmy week season
  DayRun(Dates, std::string, std::string, int, int, bool);
  //        d    m    y    comments      moreC     time dist mi/km wk    season
  DayRun(Dates, std::string, std::string, int, int, bool, int, std::string);
  DayRun(const DayRun&);
  void update(std::string, std::string, int, int, bool, int, std::string);
  void updateComments(std::string);
  void updateMoreComments(std::string);
  void updateType(bool);
  void updateMilesOrKm(bool);

  Dates day;
  std::string comments;
  std::string moreComments;
  int time; //run time
  int distance;
  bool milesOrKm; // true = miles, false = km
  int week;
  std::string season;

private:


};


#endif
