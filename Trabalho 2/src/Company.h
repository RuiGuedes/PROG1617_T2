#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"
#include "Bus.h"


using namespace std;

class Company{
	friend void info_bus(Company &SR);
	friend void BusWithoutDriver(Company &SR);
	friend void atribuir_trabalho(Company &SR);

 private:
	 string name;
	 string fichDrivers;
	 string fichLines;
	 vector<Driver> drivers;
	 vector<Line> lines;
	 multimap<unsigned int, vector<Bus>> LineBusData;		//Multimap com o ID da linha e um vector com os respetivos autocarros para essa linha
 public:
	 Company(string name, string fichDrivers, string fichLines);
	
	 // Get methods
		string getName() const;
		string getFichDrivers() const;
		string getFichLines() const;
		vector<Driver> getVecDriver() const;
		vector<Line> getVecLines() const;

	// Set methods
		void setName(string name);
		void setDrivers(vector<Driver> drivers);
		void setLines(vector<Line> lines);

	// Other methods
		void addLineBusData(unsigned int LineID, vector<Bus> busData);
};
