#include "DayOfWeek.h"
#include <string>

DayOfWeek::DayOfWeek(DailyPanel *parent, rlIds *idm, int iid, const wxChar* day)
    :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100,80), wxBORDER_NONE | wxWANTS_CHARS)
    ,ID(iid), IdManage(idm), m_parent(parent)
  {
  //labels date
  wxStaticText *st = new wxStaticText(this, -1, day);
  wxFont BoldFont = st->GetFont();
  BoldFont.SetPointSize(10);
  BoldFont.SetWeight(wxFONTWEIGHT_BOLD);
  st->SetFont(BoldFont); //sets the date to bold
  
  //makes dropdown box for how you felt on the run
  cbid = IdManage->get(ID, 0); //gets valid ID
  const wxString ratings[] = { wxT("Great"), wxT("Good"), wxT("Okay"), wxT("Bad"), wxT("Awful") }; // dropdown options
  cb_feeling = new wxComboBox(this, cbid, wxT("Great"), wxDefaultPosition, wxSize(80,25), 5, ratings, wxCB_DROPDOWN); //makes the dropdown
  Connect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(DayOfWeek::feeling)); //when option is chosen, it calls the function feeling()
  fval = 5;
  
  //sizer 
  wxBoxSizer *setwidth = new wxBoxSizer(wxVERTICAL);
  if(std::string(st->GetLabel().mb_str()).length() < 8)
    setwidth->Add(st, 1, wxTOP | wxLEFT | wxBOTTOM, 10);
  else
    setwidth->Add(st, 1, wxTOP | wxBOTTOM, 10);
  setwidth->Add(cb_feeling, 0 );
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
