#include "rlIds.h"

rlIds::rlIds()
{
current=wxID_HIGHEST;
}

int rlIds::get()
{
++current;
ids.push_back(current);
correspondingGroup.push_back(-1);
order.push_back(-1);
return current;
}
int rlIds::get(int group)
{
++current;
ids.push_back(current);
correspondingGroup.push_back(group);
int groupsize =0;
for(int i=0;i<correspondingGroup.size();++i)
  {
  if(correspondingGroup[i] == group)
    ++groupsize;
  }
order.push_back(groupsize);
return current;
}
int rlIds::get(int group, int ord)
{
++current;
ids.push_back(current);
correspondingGroup.push_back(group);
order.push_back(ord);
return current;
}

int rlIds::next(int group, int inId)
  {
  int IdLocation =-1;
  for(int i=0;i<ids.size();++i)
    {
    if(inId == ids[i])
      {
      IdLocation=i;
      break;
      }
    }
  std::cout << IdLocation << std::endl;
  if(IdLocation == -1)
    return -1;
  int currentOrder=order[IdLocation];
  int nextOrder=-1;
  if(currentOrder == -1)
    {
    return -1;
    }
  int groupsize=0;
  for(int i=0;i<correspondingGroup.size();++i)
    {
    if(correspondingGroup[i] == group)
      ++groupsize;
    }
  if(groupsize -1 == currentOrder)
    nextOrder =0;
  else
    nextOrder=currentOrder+1;
  for(int i=0;i<correspondingGroup.size();++i)
    {
    if(correspondingGroup[i] == group && order[i] == nextOrder)
      return ids[i];
    }
  return -1;
  }
