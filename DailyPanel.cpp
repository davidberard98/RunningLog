#include "DailyPanel.h"

  //parent and rparent are different because the real parent is rparent, but parent is actually a wxScrolledWindow
DailyPanel::DailyPanel(wxWindow *parent, MyFrame *rparent, rlIds *idm, int iid, const Dates tday)
    :wxPanel(parent, iid, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS), today(tday)
    , ID(iid), IdManage(idm), m_parent(rparent)
  {
  //sets IDs with group=int(ID) and tabbing order [0-3], in case tabbing bewteen panels is ever enabled
  dowid=IdManage->get(ID, 0);
  wnid=IdManage->get(ID, 1);
  awnid=IdManage->get(ID, 2);
  mpid=IdManage->get(ID, 3);

  //inintializing the different panels
  dow = new DayOfWeek(this, IdManage, dowid, wxString(today.dow().c_str(), wxConvUTF8).wc_str());
  wn = new WorkoutNotes(this, IdManage, wnid, 300, wxT("Notes on Workout:"));
  awn = new WorkoutNotes(this, IdManage, awnid, 200, wxT("Additional activities:"));
  mp = new MilesPanel(this, IdManage, mpid);
  
  //spacing the panels horizontally
  wxBoxSizer *hs = new wxBoxSizer(wxHORIZONTAL);
  hs->Add(dow, 0, wxALL, 10);
  hs->Add(wn, 1, wxALL, 10);
  hs->Add(awn, 0, wxALL, 10);
  hs->Add(mp, 0, /*wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL |*/ wxALL, 10);
  this->SetSizer(hs);
  }

//void DailyPanel::Change[Something] passes something to the parent (MyFrame) to store in a StoreRun
void DailyPanel::ChangeComments(const wxChar* comm, int inid) //inid is used because ChangeComments could come from wn or awn, but an ID makes it clear
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

void DailyPanel::SwitchTabPanel()
  {
  m_parent->SwitchTabPanel(ID); // to let it know which panel is currently focused on
  }

void DailyPanel::SetFocusFromKbd()
  {
  mp->SetFocusFromKbd();
  }
