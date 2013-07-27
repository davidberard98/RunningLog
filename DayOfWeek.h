#ifndef Day_Of_Week_h_wxWidgets_h
#define Day_Of_Week_h_wxWidgets_h

#include <wx/wx.h>
#include <wx/panel.h>

#include "DailyPanel.h"

class DailyPanel;

class DayOfWeek : public wxPanel
{
public:
  DayOfWeek(DailyPanel *parent, rlIds *idm, int iid, const wxChar* date);
 
  int ID;
  rlIds *IdManage;
  DailyPanel *m_parent;
  wxComboBox *cb_feeling;
  int cbid;
  int fval;

  void feeling(wxCommandEvent & event);

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
