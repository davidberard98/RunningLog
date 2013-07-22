#include "DayRun.h"

DayRun::DayRun(int a, int b, int c)
  :day(a), month(b), year(c), time(-1), distance(-1), milesOrKm(true), week(-1)
{}
DayRun::DayRun(int a, int b, int c, int d, std::string e)
  :day(a), month(b), year(c), week(d), season(e), time(-1), distance(-1), milesOrKm(true)
{}
DayRun::DayRun(int d, int m, int y, std::string com, std::string mc, int t, int dist, bool type)
  :day(d), month(m), year(y), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(-1)
{}
DayRun::DayRun(int d, int m, int y, std::string com, std::string mc, int t, int dist, bool type, int wk, std::string seas)
  :day(d), month(m), year(y), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(wk), season(seas)
{}
DayRun::DayRun(const DayRun& sr)
  :day(sr.day), month(sr.month), year(sr.year), comments(sr.comments), time(sr.time), distance(sr.distance), milesOrKm(sr.milesOrKm), week(sr.week), season(sr.season)
{}

void DayRun::update(std::string comm, std::string mcomm, int t, int dist, bool type, int wk, std::string seas)
{
if(comm != "" && comm != "NULL")
comments=comm;
if(mcomm != "" && mcomm != "NULL")
  moreComments=mcomm;
if(t > 0)
  time=t;
if(dist > 0)
  distance=dist;
milesOrKm=type;
if(wk > 0)
  week=wk;
if(seas != "")
  season = season;
}

void DayRun::updateComments(std::string comm)
{ comments=comm; }

void DayRun::updateMoreComments(std::string mcomm)
{ moreComments=mcomm; }

void DayRun::updateMilesOrKm(bool a)
{ updateType(a); }

void DayRun::updateType(bool type)
{ milesOrKm=type; }

