#include "Bus.h"
#include <iomanip>
#include <iostream>

Bus::  Bus(unsigned int newOrderInLine, unsigned int Line){

	orderInLine = newOrderInLine;
	lineId = Line;

	//Para o bus ficar completo falta o parametro: Shift
	//Este é dado através do método set desta classe
}

/////////////////
// Get methods //
/////////////////
unsigned int Bus::getBusOrderInLine() const{
  return orderInLine;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}


/////////////////
// Set methods //
/////////////////

void Bus::setSchedule(vector<Shift> newSchedule){
	schedule = newSchedule;
}

ostream& operator<<(ostream& out, const Bus &bus) {
	vector<Shift> shifts = bus.getSchedule();

	out << setw(30); out << left << "Identificador da linha :"; out << bus.getLineId() << endl;
	out << setw(30); out << left << "Número de ordem :"; out << bus.getBusOrderInLine() << endl;
	out << setw(30); out << left << "Turnos a realizar :" << endl << endl;
	for (unsigned int i = 0; i < shifts.size(); i++)
	{
		out << shifts.at(i) << endl;
	}
	return out;
}


