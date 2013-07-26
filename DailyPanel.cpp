#include "DailyPanel.h"

DailyPanel::DailyPanel(wxWindow *parent, rlIds *idm, MyFrame *rparent, int iid, const Dates tday)
  :wxPanel(parent, iid, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS), today(tday)
{
ID=iid;
IdManage=idm;
wnid=IdManage->get(ID, 1);
awnid=IdManage->get(ID, 2);
dowid=IdManage->get(ID, 0);
mpid=IdManage->get(ID, 3);
m_parent=rparent;
mp = new MilesPanel(this, IdManage, mpid);
wn = new WorkoutNotes(this, IdManage, wnid, 300, wxT("Notes on Workout:"));
awn = new WorkoutNotes(this, IdManage, awnid, 200, wxT("Additional activities:"));
dow = new DayOfWeek(this, IdManage, dowid, wxString(today.dow().c_str(), wxConvUTF8).wc_str());

wxBoxSizer *hs = new wxBoxSizer(wxHORIZONTAL);
hs->Add(dow, 0, wxALL, 10);
hs->Add(wn, 1, wxALL, 10);
hs->Add(awn, 0, wxALL, 10);
hs->Add(mp, 0, /*wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL |*/ wxALL, 10);
this->SetSizer(hs);

}

void DailyPanel::ChangeComments(const wxChar* comm, int inid)
{
if(inid == wnid)
  m_parent->ChangeComments(comm, today);
if(inid == awnid)
  m_parent->ChangeMoreComments(comm, today);
}

void DailyPanel::ChangeDistance(const double d)
  {
  m_parent->ChangeDistance(d, today);
  }

void DailyPanel::ChangeType(bool t)
  {
  m_parent->ChangeType(t, today);
  }

void DailyPanel::ChangeTime(double t)
  {
  m_parent->ChangeTime(t, today);
  }

void DailyPanel::ChangeFeeling(int f)
  {
  m_parent->ChangeFeeling(f, today);
  }
