#ifndef MyFrame_h_wxWidgets_Running_Log
#define MyFrame_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <iostream>
#include <string>

/*#include "MilesPanel.h"
#include "WorkoutNotes.h"
#include "DayOfWeek.h"*/
#include "DailyPanel.h"
#include "WeekInfo.h"
#include "StoreRun.h"
#include "Dates.h"
#include "rlIds.h"
#include "main.h"
#include "WeekBottom.h"

//included because of issues with recursive including & #ifndef #define
class RLog; 
class DailyPanel;
class WeekInfo;
class WeekBottom;

class MyFrame : public wxFrame
{
public:
  MyFrame(RLog *parent, rlIds *idm, const wxChar *title, int xpos, int ypos, int width, int height);
  ~MyFrame();
  //wxPanel *m_parent;
  Dates current;
  RLog *r_parent;
  rlIds *IdManage;
  int ID;
  wxScrolledWindow *m_parent; // window allowing scrolling instead of just getting cut off
  std::vector< DailyPanel* > days; 
  WeekInfo *weekinfo; //header information like season, week #, date
  StoreRun storage; //stores all information entered
  WeekBottom *weekbottom;
//  DailyPanel days[7];

  void ChangeComments(const wxChar* comm, const Dates day);
  void ChangeMoreComments(const wxChar* comm, const Dates day);
  void ChangeDistance(const double d, const Dates day);
  void ChangeType(bool t, const Dates day);
  void ChangeTime(double t, const Dates day);
  void ChangeFeeling(int f, const Dates day);
  void UpdateWeekInfo();
  void UpdateWeeklyDistance();
  void SwitchTabPanel(int currentID);

  std::vector<std::string> ListSeasons() const;

//  DECLARE_EVENT_TABLE()
};

#endif
