#ifndef Day_Of_Week_h_wxWidgets_h
#define Day_Of_Week_h_wxWidgets_h

#include <wx/wx.h>
#include <wx/panel.h>

#include "DailyPanel.h"

class DailyPanel;

class DayOfWeek : public wxPanel
{
public:
  DayOfWeek(DailyPanel *parent, const wxChar* day);
 
  DailyPanel *m_parent;
  wxComboBox *cb_feeling;
  int cbid;
  void feeling(wxCommandEvent & event);
  int fval;

};

#endif
