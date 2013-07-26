#include <wx/wx.h>
#include <wx/panel.h>
#include "MyFrame.h"
#include "MilesPanel.h"
#include "WorkoutNotes.h"
#include "StoreRun.h"
#include "rlIds.h"

class RLog : public wxApp
{
public:
  virtual bool OnInit();
};

DECLARE_APP(RLog);

IMPLEMENT_APP(RLog);

bool RLog::OnInit()
{
rlIds IdManage;
MyFrame *frame = new MyFrame(wxT("Running Log"), &IdManage, 100, 100, 850, 600);
frame->Show(true);
SetTopWindow(frame);
return true;
}
