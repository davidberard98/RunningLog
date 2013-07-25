#include "DailyPanel.h"

DailyPanel::DailyPanel(wxWindow *parent, MyFrame *rparent, const Dates tday)
  :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), today(tday)
{
wnid=150;
awnid=151;
m_parent=rparent;
mp = new MilesPanel(this, this);
wn = new WorkoutNotes(this, wnid, 300, wxT("Notes on Workout:"));
awn = new WorkoutNotes(this, awnid, 200, wxT("Additional activities:"));
dow = new DayOfWeek(this, wxString(today.dow().c_str(), wxConvUTF8).wc_str());

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
