#ifndef Weekinfo_h_wxWidgets_Running_Log
#define Weekinfo_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <string>

#include "rlIds.h"

class WeekInfo : public wxPanel
{
public:
  WeekInfo(wxWindow *parent, rlIds *idm, int weekNo, const wxChar* season, int beginDay, int beginMonth, int beginYear);

  rlIds *IdManage;
  wxStaticText *wxWeekNo;
  wxButton *editButton;

  void Edit(wxCommandEvent & event);

  std::string month(int mtc);
  std::string its(int);
  std::string iits(int);

private:
  int editID;
};

#endif
