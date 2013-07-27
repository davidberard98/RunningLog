#ifndef main_h_wxWidgets_RunningLog
#define main_h_wxWidgets_RunningLog

#include <wx/wx.h>
#include <wx/panel.h>

#include "MyFrame.h"
#include "MilesPanel.h"
#include "WorkoutNotes.h"
#include "StoreRun.h"
#include "rlIds.h"
#include "SeasonsEdit.h"

class MyFrame;
class SeasonsEdit;

class RLog : public wxApp
{
public:
  virtual bool OnInit();
  
  MyFrame *frame;
};

#endif
