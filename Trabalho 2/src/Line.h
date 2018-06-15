#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Line{
 private:
	 unsigned int id;
	 unsigned int freq_circ;
	 vector<string> busStopList;
	 vector<int> timesList;
 public:
	 Line();
	 Line(string textLine);	// Usado para ler do ficheiro
	
	 // Get methods
	 unsigned int getId() const;
	 unsigned int getFreq_circ() const;
	 vector<string> getBusStops() const;
	 vector<int> getTimings() const;
};
