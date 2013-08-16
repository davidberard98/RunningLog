#ifndef Day_Of_Week_h_wxWidgets_h
#define Day_Of_Week_h_wxWidgets_h

#include <wx/wx.h>
#include <wx/panel.h>

#include "DailyPanel.h"
#include "Dates.h"

class DailyPanel;

class DayOfWeek : public wxPanel
{
public:
  DayOfWeek(DailyPanel *parent, rlIds *idm, int iid, Dates day);
 
  int ID;
  rlIds *IdManage;
  DailyPanel *m_parent;
  wxStaticText *dowText;
  wxStaticText *ShortDateText;
  wxComboBox *cb_feeling;
  Dates today;
  int cbid;
  int fval;

  void feeling(wxCommandEvent & event);
  void SetFeeling(int);
  void SetDate(Dates day);

};

enum
{
FEELING_GREAT = 5,
FEELING_GOOD = 4,
FEELING_OKAY = 3,
FEELING_BAD = 2,
FEELING_AWFUL = 1
};

#endif
