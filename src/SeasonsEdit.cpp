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
  OkayID = IdManage->get(ID, 7);
  CancelID = IdManage->get(ID, 8);

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

  besize = new wxBoxSizer(wxVERTICAL);
  besize->Add(BeginsSizer);
  besize->AddSpacer(5);
  besize->Add(EndsSizer);
 
  //Makes error message label for future use, in case there's an error
  ErrorMessage = new wxStaticText(scrollparent, wxID_ANY, wxT(""), wxDefaultPosition);
  wxFont Bold = ErrorMessage->GetFont();
  Bold.SetWeight(wxFONTWEIGHT_BOLD);
  ErrorMessage->SetFont(Bold);

  //spaces the label and dropdown box for Seasons
  seasonsizer = new wxBoxSizer(wxHORIZONTAL);
  seasonsizer->Add(SeasonLabel, 0, wxTOP, 13);
  seasonsizer->Add(SeasonsBox, 0, wxTOP, 10);
  
  //spaces the seasons stuff and the error message
  errorsizer = new wxBoxSizer(wxVERTICAL);
  errorsizer->Add(seasonsizer);
  errorsizer->Add(ErrorMessage, 0, wxTOP | wxLEFT, 10);

  std::cout << "HI" << std::endl;
  //spaces the different elements horizontally
  hsizer = new wxBoxSizer(wxHORIZONTAL);
  hsizer->AddSpacer(10);
  hsizer->Add(errorsizer, 0);
  hsizer->AddSpacer(20);
  hsizer->Add(besize, 0, wxTOP, 15);
  
//  std::cout << "BEFORE BUTTONS" << std::endl;
  OkayButton = new wxButton(scrollparent, OkayID, wxT("Okay"), wxDefaultPosition);
  Connect(OkayID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SeasonsEdit::OkayClicked));

  CancelButton = new wxButton(scrollparent, CancelID, wxT("Cancel"), wxDefaultPosition);
  Connect(CancelID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SeasonsEdit::CancelClicked));

  OkayCancelSizer = new wxBoxSizer(wxHORIZONTAL);
//  OkayCancelSizer->AddStretchSpacer(1);
  OkayCancelSizer->Add(OkayButton, 0, wxALIGN_RIGHT);
  OkayCancelSizer->Add(CancelButton, 0, wxALIGN_RIGHT);

  //spaces the seasons at the top and the buttons at the bottom right
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(hsizer);
  sizer->AddStretchSpacer(1);
  sizer->Add(OkayCancelSizer, 1, wxALIGN_RIGHT);

  scrollparent->SetSizer(sizer);

  scrollparent->FitInside(); // ask the sizer about the needed size
  scrollparent->SetScrollRate(5, 5);
  }

SeasonsEdit::~SeasonsEdit()
  {
  IdManage->removeGroup(ID);
  }

void SeasonsEdit::OkayClicked(wxCommandEvent & WXUNUSED(event))
  {
  //check if dates are valid, and if not, return error message
  Dates begin, end;
  bool DatesCorrect = CheckDates(begin, end); //also changes the dates into Dates.
  if(DatesCorrect == false)
    ErrorMessage->SetLabel(wxT("Error: Invalid dates"));

  //check if season is set, and if not, return an error message
  std::string SeasonToSet;
  bool SeasonIsSet = CheckSeason(SeasonToSet);
  if(SeasonIsSet == false)
    ErrorMessage->SetLabel(wxT("Error: No season entered"));

  //if both are correct
  if(DatesCorrect == true && SeasonIsSet == true)
    {
    if(begin > end) //switch so that begin <= end
      {
      Dates beginc(begin);
      begin.set(end);
      end.set(begin);
      }

    // example: [ignore that numbers are offset by 1, this is just for understanding]
    // mon tue wed thu fri sat sun
    // 0a  1a  2a  3a  4a  5a  6a  
    // 0b  1b  2b  3b  4b  5b  6b   
    // begin = 1a [tuesday week 1], end=5b [saturday week 2]
    // instead, it will use both weeks in their entirety (since seasons are set by weeks)
    // so begin = 0a, and end = 0b+6 = 6b
    begin.set(begin.weekBegin());
    end.set(end.weekBegin());
    end.set(6); //add six days

    int WeekNumber=1;
    Dates CheckWeek(begin); //to check against count to see when the week changes
    Dates count(begin); 
    while(count != end) //goes through Storage and edits every day in season to add what season it's part of
      {
      std::cout << count.FullDate() << std::endl;
      if(count.weekBegin() > CheckWeek.weekBegin()) //increments the week every time the counter gets to a new week
        {
        CheckWeek.set(count);
        ++WeekNumber;
        }
      m_parent->storage.AddSeason(SeasonToSet, WeekNumber, count);
      count.set(1); //kind of like ++i
      }

    m_parent->UpdateWeekInfo();
    Close(); //close this frame
    Destroy();
    }
  }

bool SeasonsEdit::CheckDates(Dates &begin, Dates &end)
  {
  bool DatesCorrect = true;
  //get the selected dates from the dropdown boxes and change them into integers
  int beginm = Dates::ShortMonthToInt(std::string(BeginsMonth->GetValue().mb_str()));
  int begind = int(Dates::stringToDouble(std::string(BeginsDay->GetValue().mb_str())));
  int beginy = int(Dates::stringToDouble(std::string(BeginsYear->GetValue().mb_str())));
  begin.set(begind, beginm, beginy); //make a Dates object to see if the dates exist
  if(beginm != begin.month() || begind != begin.day() || beginy != begin.year()) //check to see if the dates are valid
    DatesCorrect = false;
  
  //checking the end date
  int endm = Dates::ShortMonthToInt(std::string(EndsMonth->GetValue().mb_str()));
  int endd = int(Dates::stringToDouble(std::string(EndsDay->GetValue().mb_str())));
  int endy = int(Dates::stringToDouble(std::string(EndsYear->GetValue().mb_str())));
  end.set(endd, endm, endy);
  if(endm != end.month() || endd != end.day() || endy != end.year()) //check to see if the dates are valid
    DatesCorrect = false;
  
  std::cout << begin.FullDate() << " to " << end.FullDate() << std::endl;  

  return DatesCorrect;
  }

bool SeasonsEdit::CheckSeason(std::string &val) //return the string value of the season
  {
  val =std::string(SeasonsBox->GetValue().mb_str());
  if(val == "")
    return false;
  else
    return true;
  return false;
  }

void SeasonsEdit::CancelClicked(wxCommandEvent & WXUNUSED(event))
  {
  Close();
  Destroy();
  }
