#ifndef MilesPanel_h_wxWidgets_Running_Log
#define MilesPanel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <string>

#include "Dates.h"
#include "DailyPanel.h"

class DailyPanel;

class MilesPanel : public wxPanel
{
public:
  MilesPanel(DailyPanel *parent);

  Dates d;
  DailyPanel *m_parent;
  wxTextCtrl *miles_text;
  wxStaticText *mt_label;
  int mtid, mkid;
  int thid, tmid, tsid;
  wxStaticText *time_label;
  wxTextCtrl *hours;
  wxTextCtrl *minutes;
  wxTextCtrl *seconds;
  wxComboBox *miKm;

  void MilesChanged(wxCommandEvent & event);
  void MiKmChanged(wxCommandEvent & event);
  void TimeChanged(wxCommandEvent & event);
};

#endif
