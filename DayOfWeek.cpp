#include "DayOfWeek.h"
#include <string>

DayOfWeek::DayOfWeek(DailyPanel *parent, rlIds *idm, int iid, Dates day)
    :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100,80), wxBORDER_NONE | wxWANTS_CHARS)
    ,ID(iid), IdManage(idm), m_parent(parent), today(day)
  {
  //labels date
  dowText = new wxStaticText(this, -1, wxString(today.dow().c_str(), wxConvUTF8), wxDefaultPosition);
  wxFont BoldFont = dowText->GetFont();
  BoldFont.SetPointSize(10);
  BoldFont.SetWeight(wxFONTWEIGHT_BOLD);
  dowText->SetFont(BoldFont); //sets the date to bold

  //displays the short date, like '7/28'
  ShortDateText = new wxStaticText(this, -1, wxString(today.ShortDate().c_str(), wxConvUTF8), wxDefaultPosition);
  ShortDateText->SetFont(BoldFont); //makes it bold
  
  //makes dropdown box for how you felt on the run
  cbid = IdManage->get(ID, 0); //gets valid ID
  const wxString ratings[] = { wxT("Great"), wxT("Good"), wxT("Okay"), wxT("Bad"), wxT("Awful") }; // dropdown options
  cb_feeling = new wxComboBox(this, cbid, wxT("Great"), wxDefaultPosition, wxSize(80,25), 5, ratings, wxCB_DROPDOWN); //makes the dropdown
  Connect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(DayOfWeek::feeling)); //when option is chosen, it calls the function feeling()
  fval = 5;
  
  //sizer 
  wxBoxSizer *setwidth = new wxBoxSizer(wxVERTICAL);
  if(std::string(dowText->GetLabel().mb_str()).length() < 8)
    setwidth->Add(dowText, 1, wxTOP | wxLEFT , 10);
  else
    setwidth->Add(dowText, 1, wxTOP , 10);
  setwidth->Add(ShortDateText, 0, wxLEFT, 20);
  setwidth->Add(cb_feeling, 0);
  this->SetSizer(setwidth);
  }

void DayOfWeek::feeling(wxCommandEvent & WXUNUSED(event))
  {
  std::string cbf = std::string(cb_feeling->GetValue().mb_str()); // get the chosen dropdown option and converts it from wxString to std::string
  if(cbf == "Great")
    fval=5;
  else if(cbf == "Good")
    fval=4;
  else if(cbf == "Okay")
    fval=3;
  else if(cbf == "Bad")
    fval=2;
  else if(cbf == "Awful")
    fval=1;
  m_parent->ChangeFeeling(fval); // passes feeling value to parent to store
  }

void DayOfWeek::SetFeeling(int tc)
  {
  switch(tc)
    {
    case 1: cb_feeling->SetValue(wxT("Awful")); break;
    case 2: cb_feeling->SetValue(wxT("Bad")); break;
    case 3: cb_feeling->SetValue(wxT("Okay")); break;
    case 4: cb_feeling->SetValue(wxT("Good")); break;
    case 5: cb_feeling->SetValue(wxT("Great")); break;
    }
  }

void DayOfWeek::SetDate(Dates day)
  {
  today = day;
  ShortDateText->SetLabel(wxString(today.ShortDate().c_str(), wxConvUTF8));
  }
