#include "Shift.h"
#include <iomanip>
#include "Prototipos.h"

Shift::Shift(unsigned int linha, unsigned int condutor, unsigned int autocarro, unsigned int inicio, unsigned int fim){
	busLineId = linha;
	driverId = condutor;
	busOrderNumber = autocarro;
	startTime = inicio;
	endTime = fim;
}

Shift::Shift(unsigned int linha, unsigned int autocarro, unsigned int inicio, unsigned int fim) {
	busLineId = linha;
	busOrderNumber = autocarro;
	startTime = inicio;
	endTime = fim;
	available = true;
}

/////////////////
// Get methods //
/////////////////
unsigned int Shift::getBusLineId() const{
  return busLineId;
}

unsigned int Shift::getDriverId() const{
  return driverId;
}
unsigned int Shift::getBusOrderNumber() const{
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{
  return startTime;
}

unsigned int Shift::getEndTime() const{
  return endTime;
}

unsigned int Shift::getAvailable() const {
	return available;
}

/////////////////
// Set methods //
/////////////////

void Shift::setBusLineId(unsigned int busLineId){
  this->busLineId = busLineId;
}

void Shift::setDriverId(unsigned int driverId){
  this->driverId = driverId;
}

void Shift::setBusOrderNumber(unsigned int busOrderNumber){
  this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime){
  this->startTime = startTime;
}

void Shift::setEndTime(unsigned int endTime){
  this->endTime = endTime;
}

void Shift::setAvailable(bool condition) 
{
	available = condition;
}

ostream& operator<<(ostream& out, const Shift &shift) {
	bool condition = shift.getAvailable();

	if (condition)
	{
		int startWork = shift.getStartTime(), endWork = shift.getEndTime();
		unsigned int startWorkHour = 0, startWorkMin = 0, endWorkHour = 0, endWorkMin = 0;
		string dia;

		TimeConverter(startWork, endWork, startWorkHour, startWorkMin, endWorkHour, endWorkMin, dia);

		out << setw(30); out << left << "Identificador do condutor : "; out << endl;
		out << setw(30); out << left << "Dia : "; out << dia << endl;
		out << setw(30); out << left << "Hora de início : "; TimeWriterBus(startWorkHour, startWorkMin); out << endl;
		out << setw(30); out << left << "Hora de fim : "; TimeWriterBus(endWorkHour, endWorkMin); out << endl;
	}
	else
	{
		int startWork = shift.getStartTime(), endWork = shift.getEndTime();
		unsigned int startWorkHour = 0, startWorkMin = 0, endWorkHour = 0, endWorkMin = 0;
		string dia;

		TimeConverter(startWork, endWork, startWorkHour, startWorkMin, endWorkHour, endWorkMin, dia);

		out << setw(30); out << left << "Identificador do condutor : "; out << shift.getDriverId() << endl;
		out << setw(30); out << left << "Dia : "; out << dia << endl;
		out << setw(30); out << left << "Hora de início : "; TimeWriterBus(startWorkHour, startWorkMin); out << endl;
		out << setw(30); out << left << "Hora de fim : "; TimeWriterBus(endWorkHour, endWorkMin); out << endl;
	}
	return out;
}