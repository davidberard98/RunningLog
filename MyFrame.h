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

class DailyPanel;

class MyFrame : public wxFrame
{
public:
  MyFrame(const wxChar *title, int xpos, int ypos, int width, int height);
  ~MyFrame();
  //wxPanel *m_parent;
  wxScrolledWindow *m_parent;
  std::vector< DailyPanel* > days;
  WeekInfo *weekinfo;
  StoreRun storage;
//  DailyPanel days[7];

  void ChangeComments(const wxChar* comm, const Dates day);
  void ChangeMoreComments(const wxChar* comm, const Dates day);
  void ChangeDistance(const double d, const Dates day);
};

#endif
