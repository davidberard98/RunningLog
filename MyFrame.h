#ifndef MyFrame_h_wxWidgets_Running_Log
#define MyFrame_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <iostream>

/*#include "MilesPanel.h"
#include "WorkoutNotes.h"
#include "DayOfWeek.h"*/
#include "DailyPanel.h"
#include "WeekInfo.h"
#include "StoreRun.h"
#include "Dates.h"
#include "rlIds.h"

class DailyPanel;

class MyFrame : public wxFrame
{
public:
  MyFrame(const wxChar *title, rlIds *idm, int xpos, int ypos, int width, int height);
  ~MyFrame();
  //wxPanel *m_parent;
  rlIds *IdManage;
  int ID;
  wxScrolledWindow *m_parent; // window allowing scrolling instead of just getting cut off
  std::vector< DailyPanel* > days; 
  WeekInfo *weekinfo; //header information like season, week #, date
  StoreRun storage; //stores all information entered
//  DailyPanel days[7];

  void ChangeComments(const wxChar* comm, const Dates day);
  void ChangeMoreComments(const wxChar* comm, const Dates day);
  void ChangeDistance(const double d, const Dates day);
  void ChangeType(bool t, const Dates day);
  void ChangeTime(double t, const Dates day);
  void ChangeFeeling(int f, const Dates day);

//  DECLARE_EVENT_TABLE()
};

#endif
