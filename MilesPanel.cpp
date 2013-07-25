#include "MilesPanel.h"
#include <string>

MilesPanel::MilesPanel(wxWindow *parent, DailyPanel *rparent)
  :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
m_parent=rparent;

wxBoxSizer *vspace = new wxBoxSizer(wxVERTICAL);

wxPanel *hms = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
wxPanel *distance = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

mt_label = new wxStaticText(this, -1, wxT("Mileage:"), wxDefaultPosition);
time_label = new wxStaticText(this, -1, wxT("Time (h:m:s):"), wxDefaultPosition);

const wxString dop[] = { wxT("mi") , wxT("km") };

mtid=152;
mkid=153;
miles_text = new wxTextCtrl(distance, mtid, wxT(""), wxDefaultPosition, wxSize(35,25));
miKm = new wxComboBox(distance, mkid, wxT("mi"), wxDefaultPosition, wxSize(65, 25), 2, dop, wxCB_DROPDOWN);
Connect(mtid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MilesChanged));
Connect(mkid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MiKmChanged));

wxBoxSizer *dspace = new wxBoxSizer(wxHORIZONTAL);
dspace->Add(miles_text,0);
dspace->Add(miKm, 0);

distance->SetSizer(dspace);

thid = 155;
tmid = 156;
tsid = 157;
hours = new wxTextCtrl(hms, thid, wxT(""), wxDefaultPosition, wxSize(20,25));
minutes = new wxTextCtrl(hms, tmid, wxT(""), wxDefaultPosition, wxSize(28,25));
seconds = new wxTextCtrl(hms, tsid, wxT(""), wxDefaultPosition, wxSize(28,25));
Connect(thid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
Connect(tmid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
Connect(tsid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));

wxStaticText *colon = new wxStaticText(hms, -1, wxT(":"),wxDefaultPosition);
wxStaticText *colon2 = new wxStaticText(hms, -1, wxT(":"),wxDefaultPosition);

wxFont font = colon->GetFont();
font.SetPointSize(15);
font.SetWeight(wxFONTWEIGHT_BOLD);
colon->SetFont(font);
colon2->SetFont(font);

wxBoxSizer *hspace = new wxBoxSizer(wxHORIZONTAL);
hspace->Add(hours, 0);
hspace->Add(colon,0);
hspace->Add(minutes, 0);
hspace->Add(colon2,0);
hspace->Add(seconds, 0);

hms->SetSizer(hspace);

vspace->Add(mt_label, 0);
//vspace->Add(miles_text, 0);
vspace->Add(distance, 0);
vspace->Add(time_label, 0);
vspace->Add(hms, 0, wxEXPAND);

this->SetSizer(vspace);
}

void MilesPanel::MilesChanged(wxCommandEvent & WXUNUSED(event))
  {
  std::string v = std::string(miles_text->GetValue().mb_str());
  m_parent->ChangeDistance(d.stringToDouble(v));
  }
void MilesPanel::MiKmChanged(wxCommandEvent & WXUNUSED(event))
  {
  if(std::string(miKm->GetValue().mb_str()) == "km")
    m_parent->ChangeType(false);
  else
    m_parent->ChangeType(true);
  }
void MilesPanel::TimeChanged(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "MP:TC" << std::endl;
  int h = int(d.stringToDouble(std::string(hours->GetValue().mb_str())));
  int m = int(d.stringToDouble(std::string(minutes->GetValue().mb_str())));
  double s = d.stringToDouble(std::string(seconds->GetValue().mb_str()));
  if(s >= 60)
    {
    double ns = s-60;
    int nm = m+1;
    seconds->SetValue(wxString(d.doubleToString(ns).c_str(), wxConvUTF8));
    minutes->SetValue(wxString(d.doubleToString(nm).c_str(), wxConvUTF8));
    }
  if(m >= 60)
    {
    double nm = m-60;
    int nh = h+1;
    minutes->SetValue(wxString(d.doubleToString(nm).c_str(), wxConvUTF8));
    hours->SetValue(wxString(d.doubleToString(nh).c_str(), wxConvUTF8));
    }
  s+=m*60;
  s+=h*60*60;
  m_parent->ChangeTime(s);
  }
