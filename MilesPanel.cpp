#include "MilesPanel.h"
#include <string>

MilesPanel::MilesPanel(wxWindow *parent)
  :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
wxBoxSizer *vspace = new wxBoxSizer(wxVERTICAL);

wxPanel *hms = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
wxPanel *distance = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

mt_label = new wxStaticText(this, -1, wxT("Mileage:"), wxDefaultPosition);
time_label = new wxStaticText(this, -1, wxT("Time (h:m:s):"), wxDefaultPosition);

const wxString dop[] = { wxT("mi") , wxT("km") };

miles_text = new wxTextCtrl(distance, -1, wxT(""), wxDefaultPosition, wxSize(35,25));
miKm = new wxComboBox(distance, -1, wxT("mi"), wxDefaultPosition, wxSize(65, 25), 2, dop, wxCB_DROPDOWN);

wxBoxSizer *dspace = new wxBoxSizer(wxHORIZONTAL);
dspace->Add(miles_text,0);
dspace->Add(miKm, 0);

distance->SetSizer(dspace);

hours = new wxTextCtrl(hms, -1, wxT(""), wxDefaultPosition, wxSize(20,25));
minutes = new wxTextCtrl(hms, -1, wxT(""), wxDefaultPosition, wxSize(28,25));
seconds = new wxTextCtrl(hms, -1, wxT(""), wxDefaultPosition, wxSize(28,25));

wxStaticText *colon = new wxStaticText(hms, -1, wxT(":"),wxDefaultPosition);
wxStaticText *colon2 = new wxStaticText(hms, -1, wxT(":"),wxDefaultPosition);

wxFont font = colon->GetFont();
font.SetPointSize(15);
font.SetWeight(wxFONTWEIGHT_BOLD);
colon->SetFont(font);
colon2->SetFont(font);

wxBoxSizer *hspace = new wxBoxSizer(wxHORIZONTAL);
hspace->Add(hours, 0);
hspace->Add(colon,0);
hspace->Add(minutes, 0);
hspace->Add(colon2,0);
hspace->Add(seconds, 0);

hms->SetSizer(hspace);

vspace->Add(mt_label, 0);
//vspace->Add(miles_text, 0);
vspace->Add(distance, 0);
vspace->Add(time_label, 0);
vspace->Add(hms, 0, wxEXPAND);

this->SetSizer(vspace);
}
