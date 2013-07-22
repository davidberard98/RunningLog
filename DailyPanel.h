#ifndef Daily_Panel_h_wxWidgets_Running_Log
#define Daily_Panel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>

#include "MyFrame.h"
#include "WorkoutNotes.h"
#include "MilesPanel.h"
#include "DayOfWeek.h"

class MyFrame;
class WorkoutNotes;

class DailyPanel : public wxPanel
{
public:
  DailyPanel(wxWindow *parent, MyFrame *rparent, const wxChar* day);

  MyFrame *m_parent;
  MilesPanel *mp;
  WorkoutNotes *wn;
  WorkoutNotes *awn;
  DayOfWeek *dow;

  void ChangeComments(const wxChar* comm);

};

#endif
