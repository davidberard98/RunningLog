#ifndef Daily_Panel_h_wxWidgets_Running_Log
#define Daily_Panel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>

#include "MyFrame.h"
#include "WorkoutNotes.h"
#include "MilesPanel.h"
#include "DayOfWeek.h"
#include "Dates.h"

class MyFrame;
class WorkoutNotes;
class MilesPanel;

class DailyPanel : public wxPanel
{
public:
  DailyPanel(wxWindow *parent, MyFrame *rparent, const Dates tday);

  MyFrame *m_parent;
  MilesPanel *mp;
  int wnid, awnid;
  WorkoutNotes *wn;
  WorkoutNotes *awn;
  DayOfWeek *dow;
  const Dates today;

  void ChangeComments(const wxChar* comm, int inid);
  void ChangeDistance(const double d);
  void ChangeType(bool t);

};

#endif
