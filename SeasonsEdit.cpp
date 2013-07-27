#include "SeasonsEdit.h"

SeasonsEdit::SeasonsEdit(MyFrame *parent, rlIds *idm, int iid, const wxChar *title, int xpos, int ypos, int width, int height)
    :wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height)
      , wxCLOSE_BOX | wxSYSTEM_MENU | wxCAPTION | wxRESIZE_BORDER)
    ,m_parent(parent), IdManage(idm), ID(iid)
  {
  //wxScrolledWindow will allow scrolling instead of cutting off things that are too big.
  scrollparent = new wxScrolledWindow(this, IdManage->get());

  //assigning IDs
  SeasonsBoxID = IdManage->get(ID, 0);
  BeginsMonthID = IdManage->get(ID, 1);
  BeginsDayID = IdManage->get(ID, 2);
  BeginsYearID = IdManage->get(ID, 3);
  EndsMonthID = IdManage->get(ID, 4);
  EndsDayID = IdManage->get(ID, 5);
  EndsYearID = IdManage->get(ID, 6);

  //finding the pre-defined seasons
  SeasonLabel = new wxStaticText(scrollparent, wxID_ANY, wxT("Season:"), wxDefaultPosition); //label (wxStaticText) that says 'Season:'
  std::vector<std::string> CurrentSeasons = m_parent->ListSeasons();
  wxString SeasonsOptions[CurrentSeasons.size()];
  for(int i=0;i<CurrentSeasons.size();++i) //changing to an array of wxStrings
    SeasonsOptions[i] = wxString(CurrentSeasons[i].c_str(), wxConvUTF8);
  SeasonsBox = new wxComboBox(scrollparent, SeasonsBoxID, wxT(""), wxDefaultPosition, wxDefaultSize, CurrentSeasons.size(), SeasonsOptions, wxCB_DROPDOWN); 
    //make the box

  // Make an array of day options [1-31]
  wxString DayOptions[31];
  for(int i=0;i<31;++i)
    {
    DayOptions[i] = wxString(Dates::its(i+1).c_str(), wxConvUTF8);
    }

  // Make an array of month options [Jan-Dec]
  wxString MonthOptions[12];
  for(int i=0;i<12;++i)
    {
    MonthOptions[i] = wxString(Dates::intToShortMonth(i).c_str(), wxConvUTF8);
    }

  // Make an array of years [last year, this year, next year], which will be editable
  Dates today;
  int thisyear = today.year();
  wxString YearOptions[3];
  YearOptions[0] = wxString(Dates::its(thisyear-1).c_str(), wxConvUTF8);
  YearOptions[1] = wxString(Dates::its(thisyear).c_str(), wxConvUTF8);
  YearOptions[2] = wxString(Dates::its(thisyear+1).c_str(), wxConvUTF8);

  //Date that it begins
  BeginsLabel = new wxStaticText(scrollparent, wxID_ANY, wxT("Begins:"), wxDefaultPosition);
  BeginsMonth = new wxComboBox(scrollparent, BeginsMonthID, wxString(Dates::intToShortMonth(today.month()).c_str(), wxConvUTF8)
    ,wxDefaultPosition, wxSize(65, 30), 12, MonthOptions, wxCB_DROPDOWN | wxCB_READONLY);
  BeginsDay = new wxComboBox(scrollparent, BeginsDayID, wxString(Dates::its(today.day()).c_str(), wxConvUTF8), wxDefaultPosition, wxSize(55, 30), 31, DayOptions, wxCB_DROPDOWN | wxCB_READONLY);
  BeginsYear = new wxComboBox(scrollparent, BeginsYearID, wxT(""), wxDefaultPosition, wxSize(75, 30), 3, YearOptions, wxCB_DROPDOWN);

  //Date that it ends
  EndsLabel = new wxStaticText(scrollparent, wxID_ANY, wxT("Ends:"), wxDefaultPosition);
  EndsMonth = new wxComboBox(scrollparent, EndsMonthID, wxString(Dates::intToShortMonth(today.month()).c_str(), wxConvUTF8)
    ,wxDefaultPosition, wxSize(65, 30), 12, MonthOptions, wxCB_DROPDOWN | wxCB_READONLY);
  EndsDay = new wxComboBox(scrollparent, EndsDayID, wxString(Dates::its(today.day()).c_str(), wxConvUTF8), wxDefaultPosition, wxSize(55, 30), 31, DayOptions, wxCB_DROPDOWN | wxCB_READONLY);
  EndsYear = new wxComboBox(scrollparent, EndsYearID, wxT(""), wxDefaultPosition, wxSize(75, 30), 3, YearOptions, wxCB_DROPDOWN);

  BeginsSizer = new wxBoxSizer(wxHORIZONTAL);
  BeginsSizer->Add(BeginsLabel, 0, wxTOP, 5);
  BeginsSizer->Add(BeginsMonth, 0);
  BeginsSizer->Add(BeginsDay, 0);
  BeginsSizer->Add(BeginsYear, 0);
 
  EndsSizer = new wxBoxSizer(wxHORIZONTAL);
  EndsSizer->Add(EndsLabel, 0, wxTOP, 5);
  EndsSizer->Add(EndsMonth, 0);
  EndsSizer->Add(EndsDay, 0);
  EndsSizer->Add(EndsYear, 0);

  vsize = new wxBoxSizer(wxVERTICAL);
  vsize->Add(BeginsSizer);
  vsize->AddSpacer(5);
  vsize->Add(EndsSizer);
 
  std::cout << "HI" << std::endl;
  //spaces the different elements horizontally
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->AddSpacer(10);
  sizer->Add(SeasonLabel, 0, wxTOP, 13);
  sizer->Add(SeasonsBox, 0, wxTOP , 10);
  sizer->AddSpacer(20);
  sizer->Add(vsize, 0, wxTOP, 15);
/*  sizer->Add(BeginsLabel , 0, wxTOP, 13);
  sizer->Add(BeginsMonth , 0, wxTOP, 10);
  sizer->Add(BeginsDay , 0, wxTOP, 10);
  sizer->Add(BeginsYear , 0, wxTOP, 10);
  sizer->Add(EndsLabel , 0, wxTOP, 13);
  sizer->Add(EndsMonth , 0, wxTOP, 10);
  sizer->Add(EndsDay , 0, wxTOP, 10);
  sizer->Add(EndsYear , 0, wxTOP, 10);*/

  scrollparent->SetSizer(sizer);

  scrollparent->FitInside(); // ask the sizer about the needed size
  scrollparent->SetScrollRate(5, 5);
  }

SeasonsEdit::~SeasonsEdit()
  {
  IdManage->removeGroup(ID);
  }

