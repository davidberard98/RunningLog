#include "MyFrame.h"

MyFrame::MyFrame(const wxChar *title, rlIds *idm, int xpos, int ypos, int width, int height)
  :wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height), wxDEFAULT_FRAME_STYLE | wxWANTS_CHARS)
{
IdManage=idm;
ID=IdManage->get();
wxBoxSizer *hs = new wxBoxSizer(wxVERTICAL);
m_parent = new wxScrolledWindow(this, wxID_ANY);

Dates today;
today = today.weekBegin();

std::vector < int > dpid;
for(int i=0;i<7;++i)
  {
  dpid.push_back(IdManage->get(ID));
  }

days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[0], today));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[1], today.setNew(1)));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[2], today.setNew(2)));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[3], today.setNew(3)));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[4], today.setNew(4)));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[5], today.setNew(5)));
days.push_back(new DailyPanel(m_parent, IdManage, this, dpid[6], today.setNew(6)));

/*
days[0] = new DailyPanel(m_parent, wxT("Monday"));
days[1] = new DailyPanel(m_parent, wxT("Tuesday"));
days[2] = new DailyPanel(m_parent, wxT("Wednesday"));
days[3] = new DailyPanel(m_parent, wxT("Thursday"));
days[4] = new DailyPanel(m_parent, wxT("Friday"));
days[5] = new DailyPanel(m_parent, wxT("Saturday"));
days[6] = new DailyPanel(m_parent, wxT("Sunday"));*/

weekinfo = new WeekInfo(m_parent, IdManage, 5, wxT("Summer Training"), 1, 1, 2013);

hs->Add(weekinfo, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

for(int i=0;i<days.size();++i)
  {
  hs->Add(days[i], 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
  }
m_parent->SetSizer(hs);
m_parent->Centre();

// this part makes the scrollbars show up
m_parent->FitInside(); // ask the sizer about the needed size
m_parent->SetScrollRate(5, 5);

this->Centre();
}

MyFrame::~MyFrame()
{}

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
