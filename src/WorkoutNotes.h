#ifndef WorkoutNotes_h_wxWidgets_Running_Log
#define WorkoutNotes_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <iostream>
#include <string>

#include "DailyPanel.h"
#include "rlIds.h"

/****************
 *Contains a multi-line text box (wxTextCtrl) for workout notes or additional workout notes
 ****************/

class DailyPanel;

class WorkoutNotes : public wxPanel
{
public:
  WorkoutNotes(DailyPanel *parent, rlIds *idm, int tid, int min_width, const wxChar* message);
  
  rlIds *IdManage;
  const int ID;
  int notesID;
  wxTextCtrl *notes;
  DailyPanel *m_parent;

  void onChange(wxCommandEvent & event);
  void SetValue(const std::string);
  void SetValue(const wxChar*);
};


#endif
