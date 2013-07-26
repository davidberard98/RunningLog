#include "MilesPanel.h"

BEGIN_EVENT_TABLE(MilesPanel, wxPanel)
  EVT_NAVIGATION_KEY( MilesPanel::onKeyDown )
END_EVENT_TABLE()

MilesPanel::MilesPanel(DailyPanel *parent, rlIds *idm, int iid)
  :wxPanel(parent, iid, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxWANTS_CHARS |wxTAB_TRAVERSAL)
  {
  ID=iid; // wx ID of this
  IdManage=idm; // instance of rlIds which assigns valid IDs to 
  m_parent=parent; // pointer to parent, for calling methods of the parent object.
  
  wxBoxSizer *vsize = new wxBoxSizer(wxVERTICAL); // vertical sizer holding RunTime and distance
  
/*  wxPanel *RunTime = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    //holds the hours, minutes, and seconds textCtrl objects for the time of the run
  wxPanel *distance = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    //holds the distance for distance of run and km/miles combobox
*/
  mt_label = new wxStaticText(this, -1, wxT("Mileage:"), wxDefaultPosition);
  time_label = new wxStaticText(this, -1, wxT("Time (h:m:s):"), wxDefaultPosition);
  
  const wxString dop[] = { wxT("mi") , wxT("km") };
  
  mtid=IdManage->get(ID, 0);
  mkid=IdManage->get(ID, 1);
//  miles_text = new wxTextCtrl(distance, mtid, wxT(""), wxDefaultPosition, wxSize(35,25));
//  miKm = new wxComboBox(distance, mkid, wxT("mi"), wxDefaultPosition, wxSize(65, 25), 2, dop, wxCB_DROPDOWN);
  miles_text = new wxTextCtrl(this, mtid, wxT(""), wxDefaultPosition, wxSize(35,25));
  miKm = new wxComboBox(this, mkid, wxT("mi"), wxDefaultPosition, wxSize(65, 25), 2, dop, wxCB_DROPDOWN);
  Connect(mtid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MilesChanged));
  Connect(mkid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MiKmChanged));

  wxBoxSizer *dspace = new wxBoxSizer(wxHORIZONTAL);
  dspace->Add(miles_text,0);
  dspace->Add(miKm, 0);
  
//  distance->SetSizer(dspace);
  
  thid = IdManage->get(ID, 2);
  tmid = IdManage->get(ID, 3);
  tsid = IdManage->get(ID, 4);
/*  hours = new wxTextCtrl(RunTime, thid, wxT(""), wxDefaultPosition, wxSize(20,25));
  minutes = new wxTextCtrl(RunTime, tmid, wxT(""), wxDefaultPosition, wxSize(28,25));
  seconds = new wxTextCtrl(RunTime, tsid, wxT(""), wxDefaultPosition, wxSize(28,25));*/
  hours = new wxTextCtrl(this, thid, wxT(""), wxDefaultPosition, wxSize(20,25));
  minutes = new wxTextCtrl(this, tmid, wxT(""), wxDefaultPosition, wxSize(28,25));
  seconds = new wxTextCtrl(this, tsid, wxT(""), wxDefaultPosition, wxSize(28,25));
  Connect(thid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  Connect(tmid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  Connect(tsid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  
  wxStaticText *colon = new wxStaticText(this, -1, wxT(":"),wxDefaultPosition);
  wxStaticText *colon2 = new wxStaticText(this, -1, wxT(":"),wxDefaultPosition);
  
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
  //RunTime->SetSizer(hspace);

  mt_label->SetFocus();
  
  vsize->Add(mt_label, 0);
//vsize->Add(miles_text, 0);
  vsize->Add(dspace, 0);
  vsize->Add(time_label, 0);
  vsize->Add(hspace, 0, wxEXPAND);
  
  this->SetSizer(vsize);
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

void MilesPanel::onKeyDown(wxNavigationKeyEvent &event)
  {
  if(event.IsFromTab())
    {
    int currentFocusId = FindFocus()->GetId();
    int nextFocusId = IdManage->next(ID,currentFocusId);
    if(nextFocusId != -1)
      FindWindow(nextFocusId)->SetFocus();
    }
  }
