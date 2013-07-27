#include "main.h"

DECLARE_APP(RLog);

IMPLEMENT_APP(RLog); //makes a int main()

bool RLog::OnInit()
  {
  static rlIds IdManage;
  frame = new MyFrame(this, &IdManage, wxT("Running Log"), 100, 100, 850, 600);
  frame->Show(true); 
  SetTopWindow(frame); //not sure
  return true;
  }
