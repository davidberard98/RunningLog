#ifndef WorkoutNotes_h_wxWidgets_Running_Log
#define WorkoutNotes_h_wxWidgets_Running_Log

#include "DailyPanel.h"
#include <wx/wx.h>
#include <wx/panel.h>
#include <iostream>
#include <string>

class DailyPanel;

class WorkoutNotes : public wxPanel
{
public:
  WorkoutNotes(DailyPanel *parent, int tid, int min_width, const wxChar* message);
  
  const int ID;
  int notesID;
  wxTextCtrl *notes;
  DailyPanel *m_parent;

  void onChange(wxCommandEvent & event);

};


#endif
