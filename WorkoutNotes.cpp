#include "WorkoutNotes.h"

WorkoutNotes::WorkoutNotes(DailyPanel *parent, rlIds *idm, int tid, int min_width, const wxChar* message)
  :wxPanel(parent, tid, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE), ID(tid)
{
IdManage=idm;
m_parent=parent;

notesID = IdManage->get();
notes= new wxTextCtrl(this, notesID, message, wxDefaultPosition, wxSize(min_width, 80), wxTE_MULTILINE);
Connect(notesID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(WorkoutNotes::onChange));

wxBoxSizer *TextSize = new wxBoxSizer(wxHORIZONTAL);
TextSize->Add(notes, 1, wxALL, 10);
this->SetSizer(TextSize);
this->Centre();
}

void WorkoutNotes::onChange(wxCommandEvent & WXUNUSED(event))
{
m_parent->ChangeComments(notes->GetValue(), ID);
//std::cout << "----WorkoutNotes::onChange " << std::string(notes->GetValue().mb_str()) << std::endl;
//std::cout << "O" << std::endl;
}
