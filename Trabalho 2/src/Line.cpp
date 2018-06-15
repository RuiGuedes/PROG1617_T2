#include "Line.h"
#include <vector>
#include <iostream>
#include "Prototipos.h"

//-------------------------//
//-------CLASS LINE--------//
//-------------------------//

Line::Line() {

}

Line::Line(string textLine){

	string line = textLine, temp, mult;
	int limit;

	//Identificador unico                              
	limit = line.find_first_of(';');
	temp = line.substr(0, limit);
	id = stoi(temp);

	//Frequencia de circulação
	limit = limit + 2;
	line = line.substr(limit, line.size());
	limit = line.find_first_of(';');
	temp = line.substr(0, limit);
	freq_circ = stoi(temp);

	//Paragens
	line = line.substr((limit + 2), line.size());
	limit = line.find_first_of(';');
	mult = line.substr(0, limit);
	while (mult.find_first_of(',') != std::string::npos)
	{
		int z;
		z = mult.find_first_of(',');
		temp = mult.substr(0, z);
		busStopList.push_back(temp);
		mult = mult.substr(z + 2, mult.size());
		}
	busStopList.push_back(mult);

	//Tempo entre paragens
	line = line.substr((limit + 2), line.size());
	while (line.find_first_of(',') != std::string::npos)
	{
		int z, time;
		z = line.find_first_of(',');
		temp = line.substr(0, z);
		time = stoi(temp);
		timesList.push_back(time);
		line = line.substr(z + 1, line.size());
		}
	timesList.push_back(stoi(line));

}


/////////////////
// Get methods //
/////////////////

unsigned int Line::getId() const {
	return id;
}

unsigned int Line::getFreq_circ() const {
	return freq_circ;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}




