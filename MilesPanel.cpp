#include "MilesPanel.h"

BEGIN_EVENT_TABLE(MilesPanel, wxPanel)
  EVT_NAVIGATION_KEY( MilesPanel::onKeyDown )
END_EVENT_TABLE()

MilesPanel::MilesPanel(DailyPanel *parent, rlIds *idm, int iid)
    :wxPanel(parent, 	iid, wxDefaultPosition, wxDefaultSize, 		wxBORDER_NONE | wxWANTS_CHARS |wxTAB_TRAVERSAL)
    //    parent window, id, position & size will be determined by sizers, no border, accept tab & enter, allow tabbing between objects
    ,ID(iid), m_parent(parent), IdManage(idm)
  {
  //assigning IDs with IdManage and setting tabbing order
  miles_textID = IdManage->get(ID, 0);
             // get an ID with group = int(ID) and it is #0 in the group
  miKmID = IdManage->get(ID, 1); 
  hoursID = IdManage->get(ID, 2); 
  minutesID = IdManage->get(ID, 3); 
  secondsID = IdManage->get(ID, 4); 
  
  //Miles text box (distance)
  mileage_label = new wxStaticText(this, -1, wxT("Mileage:"), wxDefaultPosition);
  miles_text = new wxTextCtrl(this, miles_textID, wxT(""), wxDefaultPosition, wxSize(35,25));
  Connect(miles_textID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MilesChanged)); //connects changes to storage

  //Miles/Km dropdown (Units of the distance)
  const wxString UnitsOptions[] = { wxT("mi") , wxT("km") };
  miKm = new wxComboBox(this, miKmID, wxT("mi"), wxDefaultPosition, wxSize(65, 25), 2, UnitsOptions, wxCB_DROPDOWN | wxCB_READONLY);
  Connect(miKmID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::MiKmChanged)); //connects changes to storage

  //spaces the text box (for distance) and the dropdown (for units)
  wxBoxSizer *DistanceSizer = new wxBoxSizer(wxHORIZONTAL);
  DistanceSizer->Add(miles_text,0);
  DistanceSizer->Add(miKm, 0);
  
  //Time in hours:minutes:seconds 
  time_label = new wxStaticText(this, -1, wxT("Time (h:m:s):"), wxDefaultPosition);
  hours = new wxTextCtrl(this, hoursID, wxT(""), wxDefaultPosition, wxSize(20,25));
  minutes = new wxTextCtrl(this, minutesID, wxT(""), wxDefaultPosition, wxSize(28,25));
  seconds = new wxTextCtrl(this, secondsID, wxT(""), wxDefaultPosition, wxSize(28,25));
  Connect(hoursID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  Connect(minutesID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  Connect(secondsID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MilesPanel::TimeChanged));
  
  //colons in between the distance 
  wxStaticText *colon = new wxStaticText(this, -1, wxT(":"),wxDefaultPosition);
  wxStaticText *colon2 = new wxStaticText(this, -1, wxT(":"),wxDefaultPosition);
  wxFont font = colon->GetFont(); //setting the colons to be bold
  font.SetPointSize(15);
  font.SetWeight(wxFONTWEIGHT_BOLD);
  colon->SetFont(font);
  colon2->SetFont(font);
  
  //spaces the hours, minutes, seconds and the colons in between
  wxBoxSizer *RunTimeSizer = new wxBoxSizer(wxHORIZONTAL);
  RunTimeSizer->Add(hours, 0);
  RunTimeSizer->Add(colon,0);
  RunTimeSizer->Add(minutes, 0);
  RunTimeSizer->Add(colon2,0);
  RunTimeSizer->Add(seconds, 0);
  
  //spaces all of the above vertically
  wxBoxSizer *vsize = new wxBoxSizer(wxVERTICAL);
  vsize->Add(mileage_label, 0);
  vsize->Add(DistanceSizer, 0);
  vsize->Add(time_label, 0);
  vsize->Add(RunTimeSizer, 0, wxEXPAND);
  this->SetSizer(vsize);
  }
 
void MilesPanel::MilesChanged(wxCommandEvent & WXUNUSED(event))
  {
  std::string v = std::string(miles_text->GetValue().mb_str());
    //get the # of miles, and change it from a wxString to a std::string
  m_parent->ChangeDistance(Dates::stringToDouble(v));
    //change # of miles from std::string to double and call the ChangeDistance from the parent object, which will continue sending the change until it reaches the storage
  }

void MilesPanel::MiKmChanged(wxCommandEvent & WXUNUSED(event))
  {
  //send the unit as a bool to the parent so it eventually reaches the storage
  if(std::string(miKm->GetValue().mb_str()) == "km")
    m_parent->ChangeType(false);
  else
    m_parent->ChangeType(true);
  }
void MilesPanel::TimeChanged(wxCommandEvent & WXUNUSED(event))
  {
  int h = int(Dates::stringToDouble(std::string(hours->GetValue().mb_str())));
  int m = int(Dates::stringToDouble(std::string(minutes->GetValue().mb_str())));
  double s = Dates::stringToDouble(std::string(seconds->GetValue().mb_str())); 
    //those 3 change the wxString from the text boxes to ints or doubles
  if(s >= 60) //if there are more than 60 seconds, it automatically subtracts 60 seconds and adds 1 minute
    {
    double ns = s-60;
    int nm = m+1;
    seconds->SetValue(wxString(Dates::doubleToString(ns).c_str(), wxConvUTF8));
    minutes->SetValue(wxString(Dates::doubleToString(nm).c_str(), wxConvUTF8));
    }
  if(m >= 60) //if there are more than 60 minutes, it automatically subtracts 60 minutes and adds 1 hour
    {
    double nm = m-60;
    int nh = h+1;
    minutes->SetValue(wxString(Dates::doubleToString(nm).c_str(), wxConvUTF8));
    hours->SetValue(wxString(Dates::doubleToString(nh).c_str(), wxConvUTF8));
    }
  s+=m*60;
  s+=h*60*60; //converts everything to a number of seconds
  m_parent->ChangeTime(s); //sends # of seconds to parent to eventually reach the storage
  }

void MilesPanel::onKeyDown(wxNavigationKeyEvent &event) //tabbing between miles_text, miKm, hours, minutes, seconds
  {
  if(event.IsFromTab())
    {
    int currentFocusId = FindFocus()->GetId(); //finds the id of the object currently focused on
    int nextFocusId = IdManage->next(ID,currentFocusId); //finds what the id of the next object to focus on is
    if(nextFocusId != -1) 
      FindWindow(nextFocusId)->SetFocus(); 
    }
  }
