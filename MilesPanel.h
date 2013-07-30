#ifndef MilesPanel_h_wxWidgets_Running_Log
#define MilesPanel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>
#include <string>

#include "Dates.h"
#include "DailyPanel.h"
#include "rlIds.h"

class DailyPanel;

class MilesPanel : public wxPanel
{
public:
  MilesPanel(DailyPanel *parent, rlIds *idm, int iid);

  int ID;
  rlIds *IdManage;
  DailyPanel *m_parent;
  wxTextCtrl *miles_text;
  int miles_textID, miKmID;
  int hoursID, minutesID, secondsID;
  wxStaticText *mileage_label;
  wxStaticText *time_label;
  wxTextCtrl *hours;
  wxTextCtrl *minutes;
  wxTextCtrl *seconds;
  wxComboBox *miKm;
  bool MileageSetBySetValue;

  void MilesChanged(wxCommandEvent & event);
  void MiKmChanged(wxCommandEvent & event);
  void TimeChanged(wxCommandEvent & event);
  void onKeyDown(wxNavigationKeyEvent & event);
  void SetFocusFromKbd();
  void SetDistance(double dist);
  void SetType(bool type);
  void SetTime(double time);

  DECLARE_EVENT_TABLE()
};

#endif
