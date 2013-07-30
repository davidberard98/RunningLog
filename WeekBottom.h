#ifndef WeekBottom_h_wxWidgets_RunningLog
#define WeekBottom_h_wxWidgets_RunningLog

#include <wx/wx.h>
#include <wx/panel.h>

#include "MyFrame.h"
#include "rlIds.h"
#include "Dates.h"

class MyFrame;

class WeekBottom : public wxPanel
{
public:
  WeekBottom(wxWindow *parent, MyFrame *realparent, rlIds *idm, int iid, Dates day);

  Dates begin;
  int ID;
  rlIds *IdManage;
  MyFrame *m_parent;

  wxButton *NextWeekButton;
  wxButton *LastWeekButton;
  int LastWeekID, NextWeekID;
  wxComboBox *SkipToMonth;
  wxComboBox *SkipToYear;
  wxButton *SkipToGo;
  int SkipToMonthID, SkipToYearID, SkipToGoID;
  wxStaticText *TotalMileage;
  wxBoxSizer *sizer;

  void clickLastWeek(wxCommandEvent & event);
  void clickNextWeek(wxCommandEvent & event);
  void clickSkipTo(wxCommandEvent & event);
  void onTabDown(wxNavigationKeyEvent & event);
  void update(Dates day);
  void update();
  void SetFocusFromKbd();

  DECLARE_EVENT_TABLE()

};


#endif
