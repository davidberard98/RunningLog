#ifndef DayRun_h_wxWidgets_Running_Log
#define DayRun_h_wxWidgets_Running_Log

//#include <wx/string.h>
#include <string>
#include <vector>
#include "pugixml/pugixml.hpp"

#include "Dates.h"

class DayRun
{
public:
  DayRun(Dates);//dmy
  DayRun(pugi::xml_node&); //for XML reading
  DayRun(Dates, int, std::string);//dmy week season
  DayRun(Dates, std::string, std::string, double, double, bool, int);
  //      dmy     comments      moreC     time     dist   mi/km feel wk  season
  DayRun(Dates, std::string, std::string, double, double, bool, int, int, std::string);
  DayRun(const DayRun&);
  void update(std::string, std::string, double, double, bool, int, int, std::string);
  void updateComments(std::string);
  void updateMoreComments(std::string);
  void updateType(bool);
  void updateMilesOrKm(bool);
  void clear();
  void XML(pugi::xml_node&) const;
  static std::string ReplaceInvalidCharacters(std::string);

  Dates day; //perhaps stored [a-zA-Z day][month A-Z][year a-zA-Z][year a-zA-Z] -> uses 32 bits.
  std::string comments;
  std::string moreComments;
  double time; //run time
  double distance;
  bool milesOrKm; // true = miles, false = km
  int feeling;
  int week; // week of the season
  std::string season;

private:


};


#endif
