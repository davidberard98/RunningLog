#include "DayRun.h"

DayRun::DayRun(Dates d)
  :day(d), time(-1.0), distance(-1.0), milesOrKm(true), week(-1), feeling(5)
  {}
DayRun::DayRun(Dates a, int d, std::string e)
  :day(a), week(d), season(e), time(-1.0), distance(-1.0), milesOrKm(true), feeling(5)
  {}
DayRun::DayRun(Dates d, std::string com, std::string mc, double t, double dist, bool type, int feel)
  :day(d), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(-1), feeling(feel)
  {}
DayRun::DayRun(Dates d, std::string com, std::string mc, double t, double dist, bool type, int feel, int wk, std::string seas)
  :day(d), comments(com), moreComments(mc), time(t), distance(dist), milesOrKm(type), week(wk), season(seas), feeling(feel)
  {}
DayRun::DayRun(const DayRun& sr)
  :day(sr.day), comments(sr.comments), time(sr.time), distance(sr.distance), milesOrKm(sr.milesOrKm), week(sr.week), season(sr.season), feeling(sr.feeling)
  {}

DayRun::DayRun(pugi::xml_node& in)
    :milesOrKm(true)
  {
  day = Dates(in.attribute("d").as_int(), in.attribute("m").as_int(), in.attribute("y").as_int());
  // ... …
  comments = in.attribute("comments").value();
  moreComments = in.attribute("comments").value();
  if(in.attribute("time").value() != "")
    time = Dates::stringToDouble(in.attribute("time").value());
  if(in.attribute("distance").value() != "")
    distance = Dates::stringToDouble(in.attribute("distance").value());
  if(in.attribute("type").value() == "0")
    milesOrKm = false;
  if(in.attribute("week").value() != "")
    week = int(Dates::stringToDouble(in.attribute("week").value()));
  season = in.attribute("season").value();
  
  }

void DayRun::update(std::string comm, std::string mcomm, double t, double dist, bool type, int feel, int wk, std::string seas)
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
  if(feel >0 && feel <6)
    feeling=feel;
  }

void DayRun::updateComments(std::string comm)
  { comments=comm; }

void DayRun::updateMoreComments(std::string mcomm)
  { moreComments=mcomm; }

void DayRun::updateMilesOrKm(bool a)
  { updateType(a); }

void DayRun::updateType(bool type)
  { milesOrKm=type; }

void DayRun::clear()
  {
  time = -1.0;
  distance = -1.0;
  comments="";
  moreComments="";
  week=-1;
  season="";
  milesOrKm=true;
  feeling=5;
  }

void DayRun::XML(pugi::xml_node& rl) const
  { //pugixml
  pugi::xml_node thisNode = rl.append_child("DayRun");
  
  //will put it in as <DayRun d="4" m="8" ...etc... />
  thisNode.append_attribute("d") = Dates::its(day.day()).c_str();
  thisNode.append_attribute("m") = Dates::its(day.month()).c_str();
  thisNode.append_attribute("y") = Dates::its(day.year()).c_str();
  if(comments != "")
    thisNode.append_attribute("comments") = comments.c_str();
  if(moreComments != "")
    thisNode.append_attribute("moreComments") = moreComments.c_str();
  if(time > 0.0)
    thisNode.append_attribute("time") = Dates::doubleToString(time).c_str();
  if(distance > 0.0)
    thisNode.append_attribute("distance") = Dates::doubleToString(distance).c_str();
  thisNode.append_attribute("type") = Dates::its(int(milesOrKm)).c_str();
  if(week > 0)
    thisNode.append_attribute("week") = Dates::its(week).c_str();
  if(season != "")
    thisNode.append_attribute("season") = season.c_str();

  }

std::string DayRun::ReplaceInvalidCharacters(std::string in)
{
  std::string out;
  for(int i=0;i<in.length();++i)
  {
    if(in.at(i) == '\\')
      out+= "\\\\";
    else if(in.at(i) == '<')
      out+= "\\<";
    else if(in.at(i) == '\n')
      out+= "\\n";
    else
      out+=in.at(i);
  }
  return out;
}
