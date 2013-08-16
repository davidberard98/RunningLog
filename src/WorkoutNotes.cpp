#include "WorkoutNotes.h"

WorkoutNotes::WorkoutNotes(DailyPanel *parent, rlIds *idm, int tid, int min_width, const wxChar* message)
  :wxPanel(parent, tid, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
  ,ID(tid), IdManage(idm), m_parent(parent)
  {
  //makes a text box (wxTextControl) for workout notes or additional notes
  notesID = IdManage->get();
  notes= new wxTextCtrl(this, notesID, message, wxDefaultPosition, wxSize(min_width, 80), wxTE_MULTILINE);
  Connect(notesID, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(WorkoutNotes::onChange)); 
    //whenever text is changed in the text box it calls the funciton onChage
  
  //sizer sets it in the middle
  wxBoxSizer *TextSize = new wxBoxSizer(wxHORIZONTAL);
  TextSize->Add(notes, 1, wxALL, 10);
  this->SetSizer(TextSize);
  }

void WorkoutNotes::onChange(wxCommandEvent & WXUNUSED(event))
  { // sends the contents of notes (a wxString) to parent so it can be stored in a StoreRun
  m_parent->ChangeComments(notes->GetValue(), ID);
  }

void WorkoutNotes::SetValue(const std::string in)
  {
  std::cout << "SetValue"<< std::endl;
  notes->SetValue(wxString(in.c_str(), wxConvUTF8));
  }

void WorkoutNotes::SetValue(const wxChar* in)
  {
  notes->SetValue(in);
  }

