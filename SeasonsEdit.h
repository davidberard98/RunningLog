#ifndef SeasonsEdit_h_wxWidgets_RunningLog
#define SeasonsEdit_h_wxWidgets_RunningLog

#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <string>
#include <iostream>

#include "main.h"
#include "rlIds.h"
#include "WeekInfo.h"
#include "MyFrame.h"
#include "Dates.h"

class RLog;
class WeekInfo;
class MyFrame;

/******************************

Currently this has a single control box and dates.  Eventually it might be updated to have a button for [edit another season].  In which case:

  std::vector<int> SeasonBoxID;
  std::vector<wxComboBox *> SeasonBox;
  ...etc.

ALSO..  In Connect(okayButtonID, wxEVT_COMMAND_BUTTON_CLICKED, ..) etc, change it to this"
 
  //SeasonBoxID[i] corresponds to SeasonBox[i]
  Connect(okayButtonID[number], wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SeasonsEdit::wxOkayClicked));
  ..

*******************************/

class SeasonsEdit : public wxFrame
{
public:
  SeasonsEdit(MyFrame *parent, rlIds *idm, int iid, const wxChar *title, int xpos, int ypos, int width, int height);
  ~SeasonsEdit();

  int ID;
  MyFrame *m_parent;
  rlIds *IdManage;
  wxScrolledWindow *scrollparent;

  wxStaticText *SeasonLabel;
  int SeasonsBoxID;
  wxComboBox *SeasonsBox;
  wxStaticText *BeginsLabel;
  wxComboBox *BeginsMonth;
  wxComboBox *BeginsDay;
  wxComboBox *BeginsYear;
  int BeginsMonthID, BeginsDayID, BeginsYearID;
  wxBoxSizer *BeginsSizer;
  wxStaticText *EndsLabel;
  wxComboBox *EndsMonth;
  wxComboBox *EndsDay;
  wxComboBox *EndsYear;
  wxBoxSizer *EndsSizer;
  wxBoxSizer *vsize;
  int EndsMonthID, EndsDayID, EndsYearID;
  wxBoxSizer *sizer;
  

};

#endif
