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
    wxBoxSizer *sz;
    wxTextCtrl *uselesstext;
    wxComboBox *cb;
    wxStaticText *st;
    wxTextCtrl *tc;
    wxButton *change;
    //wxWindowId *cbid;
    int cbid, tcid, utid, chid;
    void onChangeCombo(wxCommandEvent & event);
    void onKeyDown(wxNavigationKeyEvent &event);
    void changeButton(wxCommandEvent & event);
  
    DECLARE_EVENT_TABLE()
  };


BEGIN_EVENT_TABLE(myFrame, wxFrame)
  EVT_NAVIGATION_KEY( myFrame::onKeyDown )
END_EVENT_TABLE()


myFrame::myFrame()
  :wxFrame((wxFrame *) NULL, -1, wxT("wxComboBox Test"), wxPoint(150,150), wxSize(600,100),
    wxSYSTEM_MENU| wxTAB_TRAVERSAL | wxWANTS_CHARS |wxMINIMIZE_BOX |wxMAXIMIZE_BOX |wxCLOSE_BOX |wxRESIZE_BORDER)
  {
  sz = new wxBoxSizer(wxHORIZONTAL);
  const wxString options[] = { wxT("0"), wxT("1"), wxT("2") };
  
  cbid = 158;
  cb = new wxComboBox(this, cbid, wxT("0"), wxDefaultPosition, wxSize(70, 30), 3, options, wxCB_DROPDOWN | wxCB_READONLY);
  Connect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(myFrame::onChangeCombo));
  
  st = new wxStaticText(this, -1, wxT("0"), wxDefaultPosition);
  
  utid=160;
  chid=161;
  
  uselesstext = new wxTextCtrl(this, utid, wxT("bonjour!"), wxDefaultPosition, wxDefaultSize);
  change = new wxButton(this, chid, wxT("Change:"), wxDefaultPosition);
  Connect(chid, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(myFrame::changeButton));
  
  tcid=159;
  tc = new wxTextCtrl(this, tcid, wxT("To use:\n/*const*/ int id=wxID_ANY\ncb = new wxComboBox(this, id, ...)\nConnect(cbid, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(myClass::myFunction)\n\n where myFunction is myFunction(wxCommandEvent & event)"), wxDefaultPosition, wxSize(200,25), wxTE_READONLY);
  cb->SetFocus();
  tc->SetFocus();
  
  sz->Add(cb, 0, wxALL, 10);
  sz->Add(st, 0, wxALL, 10);
  sz->Add(uselesstext, 0, wxALL, 10);
  sz->Add(tc, 0, wxALL, 10);
  sz->Add(change, 0, wxALL, 10);
  this->SetSizer(sz);
  }

void myFrame::changeButton(wxCommandEvent & WXUNUSED(event))
  {
  if(sz->IsShown(uselesstext))
    {
    sz->Hide(uselesstext);
    }
  else
    {
    sz->Show(uselesstext);
    }
  sz->Layout();
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
myFrame *frameb = new myFrame();
frameb->Show(true);
return true;
}
