#include "WeekInfo.h"

//Parent and realparent because the actual parent is a wxScrolledWindow, but most functions we want are from the 'realparent', a MyFrame
WeekInfo::WeekInfo(wxWindow *parent, MyFrame *realparent, rlIds *idm, int iid, int weekNo, std::string season, Dates beginDate)
    :wxPanel(parent, iid, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
    ,IdManage(idm), begin(beginDate), ID(iid), m_parent(realparent)
  {
  wxWeekNoLabel = new wxStaticText(this, wxID_ANY, wxT("Week No. "), wxDefaultPosition);
  //sets the week number 
  if(weekNo > 0)
    wxWeekNo = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%d"), weekNo), wxDefaultPosition);
  else
    wxWeekNo = new wxStaticText(this, wxID_ANY, wxT("None"), wxDefaultPosition);
  //make a bold BoldFont
  wxFont BoldFont = wxWeekNo->GetFont();
  BoldFont.SetPointSize(15);
  BoldFont.SetWeight(wxFONTWEIGHT_BOLD);
  //set the week number to bold;
  wxWeekNo->SetFont(BoldFont);
  
  // changes the date to text
  ActualDateLabel = new wxStaticText(this, wxID_ANY, wxT("Week of "), wxDefaultPosition);
  std::string DateString = begin.FullDate();
  wxString wxDateString(DateString.c_str(), wxConvUTF8);
  ActualDate = new wxStaticText(this, wxID_ANY, wxDateString, wxDefaultPosition);
  ActualDate->SetFont(BoldFont); //sets it to bold
  
  //makes the season a bold static text
  SeasonFormattedLabel = new wxStaticText(this, wxID_ANY, wxT("Season "), wxDefaultPosition);
  if(season != "")
    SeasonFormatted = new wxStaticText(this, wxID_ANY, wxString(season.c_str(), wxConvUTF8), wxDefaultPosition);
  else
    SeasonFormatted = new wxStaticText(this, wxID_ANY, wxT("None"), wxDefaultPosition);
  SeasonFormatted->SetFont(BoldFont);
  
  //assigns ID to edit button
  editID = IdManage->get();
  editButton = new wxButton(this, editID, wxT("Edit"), wxDefaultPosition);
  Connect(editID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WeekInfo::Edit));
  
  //sizer will position all of the above horizontally
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(wxWeekNoLabel, 0, wxLEFT | wxTOP | wxBOTTOM, 9);
  sizer->Add(wxWeekNo, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
  sizer->AddStretchSpacer(1); // stretch spacer on both sides centers
  sizer->Add(SeasonFormattedLabel, 0, wxLEFT | wxTOP | wxBOTTOM, 9);
  sizer->Add(SeasonFormatted, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
  sizer->AddStretchSpacer(1);
  sizer->Add(ActualDateLabel, 0, wxLEFT | wxTOP | wxBOTTOM, 9);
  sizer->Add(ActualDate, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
  sizer->AddSpacer(20);
  sizer->Add(editButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
  this->SetSizer(sizer);
  }

void WeekInfo::Edit(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "EDITING" << std::endl;
  int seid = IdManage->get(ID);
  SeasonsEdit *se = new SeasonsEdit(m_parent, IdManage, seid, wxT("Running Log: Manage Training Seasons"), 150, 150, 600, 200);
  se->Show(true);
  }

void WeekInfo::update()
  {
  int weekNo = m_parent->storage.WeekNumber(begin);
  wxString wxStr;
  if(weekNo > 0)
    wxStr = wxString::Format(wxT("%d"), weekNo);
  else
    wxStr = wxString("None", wxConvUTF8);
  wxWeekNo->SetLabel(wxStr);
 
  std::string seas = m_parent->storage.season(begin);
  if(seas != "")
    wxStr = wxString(seas.c_str(), wxConvUTF8);
  else
    wxStr = wxT("None");
  SeasonFormatted->SetLabel(wxStr);
  
  sizer->Layout();
  }

/*
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
*/
