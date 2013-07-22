#ifndef Weekinfo_h_wxWidgets_Running_Log
#define Weekinfo_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <string>

class WeekInfo : public wxPanel
{
public:
  WeekInfo(wxWindow *parent, int weekNo, const wxChar* season, int beginDay, int beginMonth, int beginYear);

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
