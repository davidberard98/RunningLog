#ifndef DayRun_h_wxWidgets_Running_Log
#define DayRun_h_wxWidgets_Running_Log

#include <wx/string.h>

#include <string>

class DayRun
{
public:
  DayRun(int, int, int);//dmy
  DayRun(int, int, int, int, std::string);//dmy week season
  DayRun(int, int, int, std::string, std::string, int, int, bool);
  //        d    m    y    comments      moreC     time dist mi/km wk    season
  DayRun(int, int, int, std::string, std::string, int, int, bool, int, std::string);
  DayRun(const DayRun&);
  void update(std::string, std::string, int, int, bool, int, std::string);
  void updateComments(std::string);
  void updateMoreComments(std::string);
  void updateType(bool);
  void updateMilesOrKm(bool);

  int day, month, year;
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
