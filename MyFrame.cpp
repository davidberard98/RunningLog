#include "MyFrame.h"

MyFrame::MyFrame(RLog *parent, rlIds *idm, const wxChar *title, int xpos, int ypos, int width, int height)
    :wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height), wxDEFAULT_FRAME_STYLE | wxWANTS_CHARS)
    ,IdManage(idm), r_parent(parent), tabdirection(true)
  {
  ID=IdManage->get();
  m_parent = new wxScrolledWindow(this, wxID_ANY); //all vectors will

  ConfigMenuBar();

  //Initializing dates to determine what days are opened to when program opens
  today = today.weekBegin();
  
  //Assigning valid Ids. Ids don't need to be put in a group, but at some point they might be
  int wiid = IdManage->get(); //isn't part of tab sequence so it doesn't need to be part of group(ID)
  int wbid = IdManage->get(ID);
  std::vector < int > dpid;
  for(int i=0;i<7;++i)
    {
    dpid.push_back(IdManage->get(ID));
    std::cout << "  " <<dpid[i] << "  " << IdManage->IdOfOrder(ID, i) << std::endl;
    }
  std::cout << "  " <<wbid << "  " << IdManage->IdOfOrder(ID, 7) <<  std::endl;
  std::cout << IdManage->size(ID) << std::endl;

  //Panel at the top with date, season, week#
  weekinfo = new WeekInfo(m_parent, this, IdManage, wiid, storage.WeekNumber(today), storage.season(today), today);

  weekbottom = new WeekBottom(m_parent, this, IdManage, wbid, today);
  
  //Day of week, workout notes, miles, time, etc.  Inserting pointers to vector for storage & easier access
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[0], today));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[1], today.setNew(1)));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[2], today.setNew(2)));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[3], today.setNew(3)));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[4], today.setNew(4)));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[5], today.setNew(5)));
  days.push_back(new DailyPanel(m_parent, this, IdManage, dpid[6], today.setNew(6)));

  //spacing the weekinfo and DailyPanels horizontally
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(weekinfo, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
  sizer->Add(weekbottom, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
  for(int i=0;i<days.size();++i)
    {
    sizer->Add(days[i], 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    }
  m_parent->SetSizer(sizer);
  
  // this part makes the scrollbars show up
  m_parent->FitInside(); // ask the sizer about the needed size
  m_parent->SetScrollRate(20, 20);
  storage.open();
  UpdateDailyPanels();
  }

MyFrame::~MyFrame()
  {}

void MyFrame::ConfigMenuBar()
  {
  menubar = new wxMenuBar;
  filemenu = new wxMenu;

  filemenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"));
  filemenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"));
  filemenu->Append(wxID_EXIT, wxT("&Quit\tCtrl+Q"));

  Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::SavePressed ));
  Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::OpenPressed ));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::QuitPressed ));

  menubar->Append(filemenu, wxT("&File"));
  SetMenuBar(menubar);
  }

void MyFrame::SavePressed(wxCommandEvent & WXUNUSED(event))
  {
  storage.save();
  }

void MyFrame::OpenPressed(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "OPEN" << std::endl;
  storage.open();
  UpdateDailyPanels();
  }

void MyFrame::QuitPressed(wxCommandEvent & WXUNUSED(event))
  {
  std::cout << "QUIT" << std::endl;
  Close(true);
  Destroy();
  }

//All of these update the storage
void MyFrame::ChangeComments(const wxChar* comm, const Dates day)
  {
  storage.AddComments(comm, day);
  }

void MyFrame::ChangeMoreComments(const wxChar* comm, const Dates day)
  {
  storage.AddMoreComments(comm, day);
  }

void MyFrame::ChangeDistance(const double d, const Dates day)
  {
  storage.AddDistance(d, day);
  UpdateWeeklyDistance();
  }

void MyFrame::ChangeType(bool t, const Dates day)
  {
  storage.AddType(t, day);
  }

void MyFrame::ChangeTime(double t, const Dates day)
  {
  storage.AddTime(t, day);
  }

void MyFrame::ChangeFeeling(int f, const Dates day)
  {
  storage.AddFeeling(f, day);
  }

std::vector<std::string> MyFrame::ListSeasons() const
  {
  return storage.ListSeasons();
  }

void MyFrame::UpdateWeekInfo()
  {
  weekinfo->update();
  }

void MyFrame::UpdateWeeklyDistance()
  {
  weekbottom->update();
  }

void MyFrame::SwitchTabPanel(int currentID)
  {
  int nextID;
  if(tabdirection == true)
    nextID = IdManage->next(ID, currentID);
  else
    nextID = IdManage->last(ID, currentID); 

  std::cout << "    nextID: "<< nextID << std::endl;

  if(nextID != -1)
    FindWindow(nextID)->SetFocusFromKbd();
  }

void MyFrame::UpdateDailyPanels(Dates day)
  {
  today.set(day.weekBegin());
  UpdateDailyPanels();
  }

void MyFrame::UpdateDailyPanels()
  {
  std::cout << "UpdateDailyPanels" << std::endl;
  for(int i=0;i<days.size();++i)
    {
    days[i]->update(today.setNew(i));
    }
  weekbottom->update(today);
  weekinfo->update(today);
  }
