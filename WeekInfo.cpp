#include "WeekInfo.h"

WeekInfo::WeekInfo(wxWindow *parent, int weekNo, const wxChar *season, int beginDay, int beginMonth, int beginYear)
  :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
wxBoxSizer *hs = new wxBoxSizer(wxHORIZONTAL);
if(weekNo > 0)
  wxWeekNo = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%d"), weekNo), wxDefaultPosition);
else
  wxWeekNo = new wxStaticText(this, wxID_ANY, wxT("Unspecified"), wxDefaultPosition);
wxFont font = wxWeekNo->GetFont();
font.SetPointSize(15);
font.SetWeight(wxFONTWEIGHT_BOLD);
wxWeekNo->SetFont(font);

std::string ads =month(beginMonth) + " " + its(beginDay) + " " + its(beginYear);
wxString wxads(ads.c_str(), wxConvUTF8);
wxStaticText *ActualDate = new wxStaticText(this, wxID_ANY, wxads, wxDefaultPosition);
ActualDate->SetFont(font);

wxStaticText *SeasonFormatted = new wxStaticText(this, wxID_ANY, season, wxDefaultPosition);
SeasonFormatted->SetFont(font);

editID = wxID_ANY;
editButton = new wxButton(this, editID, wxT("Edit"), wxDefaultPosition);
Connect(editID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WeekInfo::Edit));

hs->Add(new wxStaticText(this, wxID_ANY, wxT("Week No. "), wxDefaultPosition), 0, wxLEFT | wxTOP | wxBOTTOM, 9);
hs->Add(wxWeekNo, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
hs->AddStretchSpacer(3);
hs->Add(new wxStaticText(this, wxID_ANY, wxT("Season "), wxDefaultPosition), 0, wxLEFT | wxTOP | wxBOTTOM, 9);
hs->Add(SeasonFormatted, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
hs->AddStretchSpacer(3);
hs->Add(new wxStaticText(this, wxID_ANY, wxT("Week of "), wxDefaultPosition), 0, wxLEFT | wxTOP | wxBOTTOM, 9);
hs->Add(ActualDate, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
hs->AddSpacer(20);
hs->Add(editButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);

this->SetSizer(hs);

}

void WeekInfo::Edit(wxCommandEvent & WXUNUSED(event))
{
std::cout << "EDITING" << std::endl;
}

std::string WeekInfo::its(int tc)
{
std::string to;
while(tc != 0)
  {
  int dig = tc%10;
  int md = tc - dig;
  tc = md/10;
  to = iits(dig)+to;
  }
return to;
}

std::string WeekInfo::iits(int tc)
{
switch(tc)
{
case 0: return "0"; break;
case 1: return "1"; break;
case 2: return "2"; break;
case 3: return "3"; break;
case 4: return "4"; break;
case 5: return "5"; break;
case 6: return "6"; break;
case 7: return "7"; break;
case 8: return "8"; break;
case 9: return "9"; break;
default:return ""; break;
}
return "";
}

std::string WeekInfo::month(int mtc)
{
switch(mtc)
{
case 0: return "January"; break;
case 1: return "February"; break;
case 2: return "March"; break;
case 3: return "April"; break;
case 4: return "May"; break;
case 5: return "June"; break;
case 6: return "July"; break;
case 7: return "August"; break;
case 8: return "September"; break;
case 9: return "October"; break;
case 10: return "November"; break;
case 11: return "December"; break;
default: return "";break;
}
return "";
}
