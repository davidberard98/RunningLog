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
  int groupsize =0;
  for(int i=0;i<correspondingGroup.size();++i) //finds the next available order number.
    {
    if(correspondingGroup[i] == group)
      ++groupsize;
    }
  ids.push_back(current); 
  correspondingGroup.push_back(group);
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

void rlIds::removeGroup(int group)
  {
  for(int i=0;i<ids.size();++i)
    {
    if(group == correspondingGroup[i])
      {
      ids[i] = -1;
      correspondingGroup[i] = -1;
      order[i] = -1;
      }
    }
  }

int rlIds::incr(int group, int currentId, int direction)
  {
  int IdLocation = getLocation(currentId); 
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
  if(direction > 0)
    {
    if(groupsize -1 == currentOrder) //if the current element is the last element, go back to element 0
      nextOrder =0;
    else
      nextOrder=currentOrder+1;
    }
  else if(direction <= 0)
    {
    if(currentOrder == 0)
      nextOrder=groupsize-1;
    else
      nextOrder=currentOrder-1;
    }
  for(int i=0;i<correspondingGroup.size();++i) //find the ID of the element with the specified order and group
    {
    if(correspondingGroup[i] == group && order[i] == nextOrder)
      return ids[i];
    }
  return -1;
  }

int rlIds::next(int group, int currentId)
  {
  return incr(group, currentId, 1);
  }

int rlIds::last(int group, int currentId)
  {
  return incr(group, currentId, -1);
  }

int rlIds::OrderOfId(int group, int id) const
  {
  for(int i=0;i<ids.size();++i)
    {
    if(correspondingGroup[i] == group && ids[i] == id)
      return order[i];
    }
  return -1;
  }

int rlIds::IdOfOrder(int group, int ord) const
  {
  for(int i=0;i<ids.size();++i)
    {
    if(correspondingGroup[i] == group && order[i] == ord)
      return ids[i];
    }
  return -1;
  }

int rlIds::size(int group) const
  {
  int s = 0;
  for(int i=0;i<correspondingGroup.size();++i)
    {
    if(correspondingGroup[i] == group)
      ++s;
    }
  return s;
  }

int rlIds::getLocation(int id) const
  {
  int idloc = -1;
  for(int i=0;i<ids.size();++i) // ids[IdLocation] == currentId - find what element of ids is equal to the id.
    {
    if(id == ids[i])
      {
      idloc=i;
      break;
      }
    }
  return idloc;
  }
