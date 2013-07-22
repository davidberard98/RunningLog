#ifndef Day_Of_Week_h_wxWidgets_h
#define Day_Of_Week_h_wxWidgets_h

#include <wx/wx.h>
#include <wx/panel.h>

class DayOfWeek : public wxPanel
{
public:
  DayOfWeek(wxWindow* parent, const wxChar* day);
  wxComboBox *cb_feeling;
  int cbid;
  void feeling(wxCommandEvent & event);
  int fval;

};

#endif
