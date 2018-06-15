#pragma once

#include <iostream>
#include <vector>
#include <ostream>
#include "Shift.h"

using namespace std;

class Bus{
 private:
  unsigned int orderInLine;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int newOrderInLine, unsigned int Line);
 
  // Get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
 
  // Set methods
  void setSchedule(vector<Shift> newSchedule);
};

ostream& operator<<(ostream& out, const Bus &bus);