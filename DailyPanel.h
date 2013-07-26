#ifndef Daily_Panel_h_wxWidgets_Running_Log
#define Daily_Panel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>

#include "MyFrame.h"
#include "WorkoutNotes.h"
#include "MilesPanel.h"
#include "DayOfWeek.h"
#include "Dates.h"
#include "rlIds.h"

class MyFrame;
class WorkoutNotes;
class MilesPanel;
class DayOfWeek;

class DailyPanel : public wxPanel
{
public:
  DailyPanel(wxWindow *parent, rlIds *idm, MyFrame *rparent, int iid, const Dates tday);

  int ID;
  rlIds *IdManage;
  MyFrame *m_parent;
  MilesPanel *mp;
  int wnid, awnid, dowid, mpid;
  WorkoutNotes *wn;
  WorkoutNotes *awn;
  DayOfWeek *dow;
  const Dates today;

  void ChangeComments(const wxChar* comm, int inid);
  void ChangeDistance(const double d);
  void ChangeType(bool t);
  void ChangeTime(double t);
  void ChangeFeeling(int f);

//  DECLARE_EVENT_TABLE()
};

#endif
