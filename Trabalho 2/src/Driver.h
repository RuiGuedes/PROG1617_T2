#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Shift.h"


using namespace std;

class Driver{
 private:
  unsigned int id;
  string name;
  unsigned int maxHours;            // Maximum duration of a shift
  unsigned int maxWeekWorkingTime;  // Maximum number of hours of work in a week
  unsigned int minRestTime;         // Minimum number of rest hours between shifts
  vector<Shift> shifts;			    // Assigned shifts
  bool spare;						// Disponibilidade do condutor  //True = Livre //False = Indisponivel
  unsigned int totalTime;

 public:
  Driver();
  Driver(string textLine);

  // Get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getShiftMaxDuration() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  vector<Shift> getShifts() const;
  bool getspare() const;
  unsigned int getTotalTime() const;

  // Set methods
  void setId(unsigned int newId);
  void setName(string newName);
  void setMaxHours(unsigned int newMaxHours);
  void setMaxWeekWorkingTime(unsigned int newMaxWeekWorkingTime);
  void setMinRestTime(unsigned int newMinRestTime);
  void setShifts(vector<Shift> newShifts);
  void setspare();


};