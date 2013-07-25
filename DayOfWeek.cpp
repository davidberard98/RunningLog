#include "DayOfWeek.h"
#include <string>

DayOfWeek::DayOfWeek(DailyPanel *parent, const wxChar* day)
  :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100,80), wxBORDER_NONE)
{
m_parent = parent;
wxStaticText *st = new wxStaticText(this, -1, day);
wxFont font = st->GetFont();
font.SetPointSize(10);
font.SetWeight(wxFONTWEIGHT_BOLD);
st->SetFont(font);

const wxString ratings[] = { wxT("Great"), wxT("Good"), wxT("Okay"), wxT("Bad"), wxT("Awful") };

cbid = int(wxID_ANY);
cb_feeling = new wxComboBox(this, cbid, wxT("Great"), wxDefaultPosition, wxSize(80,25), 5, ratings, wxCB_DROPDOWN);
Connect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(DayOfWeek::feeling));
fval = 5;

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
std::string cbf = std::string(cb_feeling->GetValue().mb_str());
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
m_parent->ChangeFeeling(fval);
}
