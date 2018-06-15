#pragma once

#include <iostream>
#include <vector>


using namespace std;

class Shift{
 private:
  unsigned int busLineId;
  unsigned int driverId;  
  unsigned int busOrderNumber; 
  unsigned int startTime; 
  unsigned int endTime;   
  bool available;  //True esta livre //False esta ocupado

 public:
  Shift(unsigned int busLineId, unsigned int driverId, unsigned int busNumber, unsigned int startTime, unsigned int endTime);
  Shift(unsigned int busLineId, unsigned int busNumber, unsigned int startTime, unsigned int endTime);
  
  // Get methods
  unsigned int getBusLineId() const;
  unsigned int getDriverId() const;
  unsigned int getBusOrderNumber() const; // Order of the bus within the bus line
  unsigned int getStartTime() const;
  unsigned int getEndTime() const;
  unsigned int getAvailable() const;

  //  Set methods
  void setBusLineId(unsigned int);
  void setDriverId(unsigned int);
  void setBusOrderNumber(unsigned int);
  void setStartTime(unsigned int);
  void setEndTime(unsigned int);
  void setAvailable(bool);
};

ostream& operator<<(ostream& out, const Shift &shift);