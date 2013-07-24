#include "DayRun.h"

DayRun::DayRun(Dates d)
  :day(d), time(-1), distance(-1), milesOrKm(true), week(-1)
{}
DayRun::DayRun(Dates a, int d, std::string e)
  :day(a), week(d), season(e), time(-1), distance(-1), milesOrKm(true)
{}
DayRun::DayRun(Dates d, std::string com, std::string mc, int t, int dist, bool type)
  :day(d), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(-1)
{}
DayRun::DayRun(Dates d, std::string com, std::string mc, int t, int dist, bool type, int wk, std::string seas)
  :day(d), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(wk), season(seas)
{}
DayRun::DayRun(const DayRun& sr)
  :day(sr.day), comments(sr.comments), time(sr.time), distance(sr.distance), milesOrKm(sr.milesOrKm), week(sr.week), season(sr.season)
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

