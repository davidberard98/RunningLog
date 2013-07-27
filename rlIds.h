#ifndef RunningLog_IDs_rlIds_h_wxWidgets_Running_Log
#define RunningLog_IDs_rlIds_h_wxWidgets_Running_Log

#include <wx/string.h> // to include wxID_HIGHEST
#include <vector>
#include <string>
#include <iostream>

/********************************
 *when an wxID is needed in the program (for example, a wxTextCtrl or wxPanel), it will return a valid id which hasn't been used
 *it also stores info about tabbing order
 *There must be ONE instance of rlIds, started in main.cpp, and a pointer to it is passed to every function that needs it.

 *A tabbing group is a group of IDs.  When you want to tab to the next element, it will look for the next ID in the same group as the current element
********************************/

class rlIds
{
public:
  rlIds();
  int get(); //group and order set to -1
  int get(int);
//      group (order assigned automatically)
  int get(int, int);
//      group, order
  int next(int, int); //returns ID
//      group, current Id
//int removeGroup(int);

private:
  int current;
  //these three vector<int> act like "class tabstorage; std::vector<tabstorage>" for storing tabbing groups and orders
  std::vector < int > ids;
  std::vector < int > correspondingGroup; // -1 is none assigned
  //order starts at 0; and -1 is none assigned
  std::vector < int > order; // for example, id[2] == 6004; id[3] == 6007; correspondingGroup[2] == 6000; correspondingGroup[3] == 6000; order[2] == 0; order[3] ==1; so 6004 and 6007 are both part of group 6000; 6004 is first, and 6007 is second in that group;
  
};


#endif
