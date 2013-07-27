#include "rlIds.h"

rlIds::rlIds()
  {
  current=wxID_HIGHEST;
  }

int rlIds::get()
  {
  ++current;
  //does not need to be stored since no group and/or order is assigned
  return current; //returns a new id
  }
int rlIds::get(int group)
  { // see get(int group, int ord)
  ++current;
  ids.push_back(current); 
  correspondingGroup.push_back(group);
  int groupsize =0;
  for(int i=0;i<correspondingGroup.size();++i) //finds the next available order number.
    {
    if(correspondingGroup[i] == group)
      ++groupsize;
    }
  order.push_back(groupsize);
  return current;
  }
int rlIds::get(int group, int ord)
  {
  //when next(int group, int current) is called, it needs to have a way to connect the ID, group, and order, so all get push_back
  //so that ids[1] is part of the group correspondingGroup[1], with the order order[1]
  ++current;
  ids.push_back(current); 
  correspondingGroup.push_back(group);
  order.push_back(ord);
  return current;
  }

int rlIds::next(int group, int currentId)
  {
  int IdLocation =-1; //automatically set to -1
  for(int i=0;i<ids.size();++i) // ids[IdLocation] == currentId - find what element of ids is equal to the id.
    {
    if(currentId == ids[i])
      {
      IdLocation=i;
      break;
      }
    }
  std::cout << IdLocation << std::endl;
  if(IdLocation == -1) //don't deal with nonexistant IDs
    return -1;
  int currentOrder=order[IdLocation];
  int nextOrder=-1;
  if(currentOrder == -1) //don't deal with objects without an order
    return -1;
  int groupsize=0;
  for(int i=0;i<correspondingGroup.size();++i) //find out how many IDs are in the group
    {
    if(correspondingGroup[i] == group)
      ++groupsize;
    }
  if(groupsize -1 == currentOrder) //if the current element is the last element, go back to element 0
    nextOrder =0;
  else
    nextOrder=currentOrder+1;
  for(int i=0;i<correspondingGroup.size();++i) //find the ID of the element with the specified order and group
    {
    if(correspondingGroup[i] == group && order[i] == nextOrder)
      return ids[i];
    }
  return -1;
  }
