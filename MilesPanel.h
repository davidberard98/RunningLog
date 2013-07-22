#ifndef MilesPanel_h_wxWidgets_Running_Log
#define MilesPanel_h_wxWidgets_Running_Log

#include <wx/wx.h>
#include <wx/panel.h>

class MilesPanel : public wxPanel
{
public:
  MilesPanel(wxWindow *parent);
  wxTextCtrl *miles_text;
  wxStaticText *mt_label;
  wxStaticText *time_label;
  wxTextCtrl *hours;
  wxTextCtrl *minutes;
  wxTextCtrl *seconds;
  wxComboBox *miKm;
};

#endif
