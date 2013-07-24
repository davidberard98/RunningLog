#include "MyFrame.h"

MyFrame::MyFrame(const wxChar *title, int xpos, int ypos, int width, int height)
  :wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height)/*, wxVSCROLL | wxHSCROLL*/)
{
wxBoxSizer *hs = new wxBoxSizer(wxVERTICAL);
m_parent = new wxScrolledWindow(this, wxID_ANY);

Dates today;
today = today.weekBegin();

days.push_back(new DailyPanel(m_parent, this, today));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(1)));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(2)));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(3)));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(4)));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(5)));
days.push_back(new DailyPanel(m_parent, this, today.weekBegin(6)));
/*
days[0] = new DailyPanel(m_parent, wxT("Monday"));
days[1] = new DailyPanel(m_parent, wxT("Tuesday"));
days[2] = new DailyPanel(m_parent, wxT("Wednesday"));
days[3] = new DailyPanel(m_parent, wxT("Thursday"));
days[4] = new DailyPanel(m_parent, wxT("Friday"));
days[5] = new DailyPanel(m_parent, wxT("Saturday"));
days[6] = new DailyPanel(m_parent, wxT("Sunday"));*/

weekinfo = new WeekInfo(m_parent, 5, wxT("Summer Training"), 1, 1, 2013);

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

void MyFrame::ChangeComments(const wxChar* comm)
{
storage.AddComments(comm, 1, 1, 2013);
}
