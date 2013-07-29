#include "WeekBottom.h"

WeekBottom::WeekBottom(wxWindow *parent, MyFrame *realparent, rlIds *idm, int iid, Dates day)
    :wxPanel(parent, iid, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
    , ID(iid), IdManage(idm), begin(day), m_parent(realparent)
  {
  //set IDs
  LastWeekID = IdManage->get(ID);
  NextWeekID = IdManage->get(ID);
  SkipToMonthID = IdManage->get(ID);
  SkipToYearID = IdManage->get(ID);
  SkipToGoID = IdManage->get(ID);
  
  //
  LastWeekButton = new wxButton(this, LastWeekID, wxT("< Last Week"), wxDefaultPosition);
  Connect(LastWeekID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WeekBottom::clickLastWeek));

  NextWeekButton = new wxButton(this, NextWeekID, wxT("Next Week >"), wxDefaultPosition);
  Connect(NextWeekID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WeekBottom::clickNextWeek));

  // Make an array of month options [Jan-Dec]
  wxString MonthOptions[12];
  for(int i=0;i<12;++i)
    {
    MonthOptions[i] = wxString(Dates::intToShortMonth(i).c_str(), wxConvUTF8);
    }

  // Make an array of years [last year, this year, next year], which will be editable
  Dates today;
  int thisyear = today.year();
  wxString YearOptions[4];
  YearOptions[0] = wxString(Dates::its(thisyear-1).c_str(), wxConvUTF8);
  YearOptions[1] = wxString(Dates::its(thisyear).c_str(), wxConvUTF8);
  YearOptions[2] = wxString(Dates::its(thisyear+1).c_str(), wxConvUTF8);
  YearOptions[3] = wxString("", wxConvUTF8);

  //Month and year to skip to
  wxStaticText *SkipToLabel = new wxStaticText(this, wxID_ANY, wxT("Skip to:"), wxDefaultPosition);
  SkipToMonth = new wxComboBox(this, SkipToMonthID, wxString(Dates::intToShortMonth(today.month()).c_str(), wxConvUTF8)
    ,wxDefaultPosition, wxSize(65, 30), 12, MonthOptions, wxCB_DROPDOWN | wxCB_READONLY);
  SkipToYear = new wxComboBox(this, SkipToYearID, wxT("2013"), wxDefaultPosition, wxSize(75, 30), 4, YearOptions, wxCB_DROPDOWN); 

  //'go' button for skipping to a different date
  SkipToGo = new wxButton(this, SkipToGoID, wxT("Go"), wxDefaultPosition, wxSize(50,30));
  Connect(SkipToGoID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WeekBottom::clickSkipTo));
 
  //make static text for total mileage
  wxStaticText *TotalMileageLabel = new wxStaticText(this, wxID_ANY, wxT("Week's Total Mileage:"));
  TotalMileage = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition); //no mileage set since update() does that
  //Make total weekly mileage bold
  wxFont Bold = TotalMileage->GetFont();
  Bold.SetPointSize(15);
  Bold.SetWeight(wxFONTWEIGHT_BOLD);
  TotalMileage->SetFont(Bold);

  //spacing everything horizontally
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(LastWeekButton);
  sizer->Add(NextWeekButton);
  sizer->AddSpacer(15);
  sizer->Add(SkipToLabel, 0, wxTOP, 5);
  sizer->Add(SkipToMonth);
  sizer->Add(SkipToYear);
  sizer->Add(SkipToGo);
  sizer->AddStretchSpacer(1);
  sizer->Add(TotalMileageLabel, 0, wxTOP, 3);
  sizer->Add(TotalMileage);
  sizer->AddSpacer(10);
  this->SetSizer(sizer);

  //This actually sets a value for the weekly mileage
  update();
  }

void WeekBottom::clickLastWeek(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "Last Week" << std::endl;
  }
void WeekBottom::clickNextWeek(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "Next Week" << std::endl;
  }
void WeekBottom::clickSkipTo(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "Skip To" << std::endl;
  }

void WeekBottom::update()
  {
  Dates count(begin);
  double totaldistance=0;
  for(int i=0;i<7;++i)
    {
    double distance = m_parent->storage.GetDistance(count);
    if(distance != -1.0)
      totaldistance += distance;
    count.set(1); //like ++count;
    }
  std::cout << totaldistance << " vs " << Dates::doubleToString(totaldistance).c_str() << std::endl;
  TotalMileage->SetLabel(wxString(Dates::doubleToString(totaldistance).c_str(), wxConvUTF8));
  sizer->Layout();
  }
