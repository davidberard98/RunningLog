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

DayRun::DayRun(std::string in) //for xml 'in'
  {
  std::vector<std::string> contents;
  for(int i=0;i<11;++i)
    contents.push_back("");
    //0 = year 1 = month 2 = day
    //3 = comments 4 = More Comments
    //5 = time 6 =distance 7 = type
    //8= feeling 9= week 10 =season
  int current =-1;
  bool backslash = false; //monitors if the last character was a backslash
  bool lessthan = true; // is it currently where it says 'HERE'? -> <HERE>
  bool insidesection = false; // is it currenty where it says 'HERE'? -> <NAME>  HERE  </NAME>
  for(int i=0;i<in.length();++i)
    {
//    std::cout << "'" << in.at(i) << "' " << i << std::endl;
    if(lessthan == true)
      {
//      std::cout << "Not recording contents" << std::endl;
      if( i > 0 && in.at(i-1) == '>')
        {
//        std::cout << "Coming out of < one of these >" << std::endl;
        if(insidesection == false)
          {
//          std::cout << "Entering <name> one of these </name>" << std::endl;
          insidesection=true;
          lessthan = false;
          ++current;
          }
        else
          {
//          std::cout << "Coming out of <name> one of these </name>" << std::endl;
          insidesection = false;
          }
        }
      }
//    std::cout << lessthan << " " << insidesection << std::endl;
    if(lessthan == false && insidesection == true)
      {
//      std::cout << "currently recording the contents <name> here </name>" << std::endl;
      if(backslash == true)
        {
        if(in.at(i) == '\\')
          contents[current] += '\\';
        else if(in.at(i) == 'n')
          contents[current] += '\n';
        else if(in.at(i) == '<')
          contents[current] += '<';
        backslash = false;
        }
      else
        {
        if(in.at(i) == '\\')
          backslash = true;
        else
          {
          if(in.at(i) == '<')
            {
//            std::cout << "Entering < one of these >" << std::endl;
            lessthan = true;
            }
          else
            {
            contents[current] += in.at(i);
//            std::cout << " " << contents[current] << std::endl;
            }
          }
        }
      }
    }
  
  for(int i=0;i<contents.size();++i)
    {
    std::cout << "  " << contents[i];
    }
  std::cout << std::endl;

  //setting the variables
  int year = int(Dates::stringToDouble(contents[0]));
  int month = int(Dates::stringToDouble(contents[1]));
  int date = int(Dates::stringToDouble(contents[2]));
  day = Dates(date, month, year);
  comments = contents[3];
  moreComments = contents[4];
  time = Dates::stringToDouble(contents[5]);
  distance = Dates::stringToDouble(contents[6]);
  if(contents[7] == "1")
    milesOrKm = true;
  else
    milesOrKm = false;
  feeling = int(Dates::stringToDouble(contents[8]));
  week = int(Dates::stringToDouble(contents[9]));
  season = contents[10];
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

std::string DayRun::XML() const
  {
  std::string out = " <DayRun>\n";
  out += "  <year>" + Dates::its(day.year()) + "</year>\n";
  out += "  <month>" + Dates::its(day.month()) + "</month>\n";
  out += "  <day>" + Dates::its(day.day()) + "</day>\n";
  if(comments != "")
    out += "  <comments>" + ReplaceInvalidCharacters(comments) + "</comments>\n";
  if(moreComments != "")
    out += "  <moreComments>" + ReplaceInvalidCharacters(moreComments) + "</moreComments>\n";
  if(time > 0.0)
    out += "  <time>" + Dates::doubleToString(time) + "</time>\n";
  if(distance > 0.0)
    out += "  <distance>" + Dates::doubleToString(distance) + "</distance>\n";
  if(milesOrKm == true)
    out += "  <milesOrKm>1</milesOrKm>\n";
  else
    out += "  <milesOrKm>0</milesOrKm>\n";
  out += "  <feeling>" + Dates::its(feeling) + "</feeling>\n";
  if(week > 0)
    out += "  <week>" + Dates::its(week) + "</week>\n";
  if(season != "")
    out += "  <season>" + ReplaceInvalidCharacters(season) + "</season>\n";
  out += " </DayRun>\n"; 
  return out;
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
