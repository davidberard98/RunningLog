#ifndef Weekinfo_h_wxWidgets_Running_Log
#define Weekinfo_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <string>

#include "MyFrame.h"
#include "SeasonsEdit.h"
#include "Dates.h"
#include "rlIds.h"

class MyFrame;

class WeekInfo : public wxPanel
{
public:
  WeekInfo(wxWindow *parent, MyFrame *realparent, rlIds *idm, int iid, int weekNo, const wxChar* season, Dates beginDate);

  MyFrame *m_parent;
  int ID;
  Dates begin;
  rlIds *IdManage;

//  wxPanel *contain;

  wxStaticText *wxWeekNoLabel;
  wxStaticText *wxWeekNo;
  wxStaticText *SeasonFormattedLabel;
  wxStaticText *SeasonFormatted;
  wxStaticText *ActualDateLabel;
  wxStaticText *ActualDate;
  wxButton *editButton;
  wxBoxSizer *sizer;

  void Edit(wxCommandEvent & event);

/*
  std::string month(int mtc);
  std::string its(int);
  std::string iits(int);*/

private:
  int editID;
};

#endif
