#include <wx/wx.h>
#include <wx/panel.h>
#include <iostream>
#include <string>

class myApp : public wxApp
{
public:
  virtual bool OnInit();
};

class myFrame : public wxFrame
{
public:
  myFrame();
  wxComboBox *cb;
  wxStaticText *st;
  wxTextCtrl *tc;
  //wxWindowId *cbid;
  int cbid, tcid;
  void onChangeCombo(wxCommandEvent & event);
  void onKeyDown(wxNavigationKeyEvent &event);

  DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(myFrame, wxFrame)
  EVT_NAVIGATION_KEY( myFrame::onKeyDown )
END_EVENT_TABLE()


myFrame::myFrame()
  :wxFrame((wxFrame *) NULL, -1, wxT("wxComboBox Test"), wxPoint(150,150), wxSize(400,300),
    wxSYSTEM_MENU| wxTAB_TRAVERSAL | wxWANTS_CHARS |wxMINIMIZE_BOX |wxMAXIMIZE_BOX |wxCLOSE_BOX |wxRESIZE_BORDER)
{
wxBoxSizer *sz = new wxBoxSizer(wxHORIZONTAL);
const wxString options[] = { wxT("0"), wxT("1"), wxT("2") };

cbid = 158;
cb = new wxComboBox(this, cbid, wxT("0"), wxDefaultPosition, wxSize(70, 30), 3, options, wxCB_DROPDOWN | wxCB_READONLY);
Connect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(myFrame::onChangeCombo));

/*BEGIN_EVENT_TABLE(myFrame, wxFrame)
  EVT_TEXT	(cbid, 	myFrame::onChangeCombo())
END_EVENT_TABLE()*/

st = new wxStaticText(this, -1, wxT("0"), wxDefaultPosition);

tcid=159;
tc = new wxTextCtrl(this, tcid, wxT("To use:\n/*const*/ int id=wxID_ANY\ncb = new wxComboBox(this, id, ...)\nConnect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(myClass::myFunction)\n\n where myFunction is myFunction(wxCommandEvent & event)"), wxDefaultPosition, wxSize(200,25), wxTE_READONLY);
cb->SetFocus();
tc->SetFocus();

sz->Add(cb);
sz->Add(st, 0, wxALL, 10);
sz->Add(tc, 0, wxALL, 10);
this->SetSizer(sz);
}

void myFrame::onChangeCombo(wxCommandEvent & WXUNUSED(event))
{
std::cout << std::string(cb->GetValue().mb_str()) << std::endl;
st->SetLabel(wxString::Format(cb->GetValue()));
}

void myFrame::onKeyDown(wxNavigationKeyEvent &event)
  {
  if(event.IsFromTab())
    {
    int foc = FindFocus()->GetId();
    if(foc == tcid)
      FindWindow(cbid)->SetFocus();
    if(foc == cbid)
      FindWindow(tcid)->SetFocus();
    std::cout << "TAB " << foc << std::endl;
    }
  }

DECLARE_APP(myApp);

IMPLEMENT_APP(myApp);

bool myApp::OnInit()
{
myFrame *frame = new myFrame();
frame->Show(true);
return true;
}
