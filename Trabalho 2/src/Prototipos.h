#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <climits>
#include <vector>
#include "Driver.h"
#include "Line.h"
#include "Company.h"


//Protótipos Interface 
void OpenFiles_Interface();
void Main_Interface(Company &SR);
void gestao_condutores(Company &SR);
void visu_info(Company &SR);
void read_info(vector<string> &vetor_info, string filename);
void store_info_line(vector<Line> &line_vector, vector<string> vetor);
void store_info_driver(vector<Driver> &driver_vector, vector<string> vetor);
void store_info_Bus(Company &SR, vector<Line> line_info);

bool valid_number(string number);
bool exist_ID_linha(vector<Line> line_vector, const int ID);
bool exist_stop_variavel(vector<string> variavel_stops, const string stop);
bool exist_ID_driver(vector<Driver> drivers_info, const int ID);


//Protótipos Driver
void cria_condutor(Company &SR);
void remove_condutor(Company &SR);
void modifica_condutor(Company &SR);
void modifica_driver_ID(Company &SR);
void modifica_driver_name(Company &SR);
void modifica_driver_HoursDay(Company &SR);
void modifica_driver_MaxHours(Company &SR);
void modifica_driver_RestTime(Company &SR);

void write_data_driver(vector<Driver> &drivers_info, string const file_name_drivers);


//Protótipos Info

void horario_stop(Company &SR);
bool exist_stop_linha(vector<Line> lines_info, const int ID, const string stop);
void write_time_stops(vector<Line> lines_info, const int indicator, const string stop);
void existe_stop(Company &SR);
void stop_to_stop(Company &SR);
void info_bus(Company &SR);
void info_line(Company &SR);
bool existeStop(Company &SR, string paragem);
void limitOptionsFinal(vector<Line> &newAdjustedVector, Company &SR, string paragem);
void limitOptionsCommon(vector<Line> &newAdjustedVector, Company &SR, unsigned int indicator, string paragem1, string paragem2, unsigned int ID);
bool existeStopOnLine(string paragem, vector<string> busStops, string condition1, string condition2);
void findStoreStops(vector<string> &CommonStops, vector<string> newAdjustedVector, vector<string> MainLine, string paragem1, string paragem2);
void writeInfoStops(multimap<unsigned int, vector<string>> &Information, string paragem);
bool RepeatInfo(vector<string> VarStops);
void DriverWork(Company SR);
void TimeConverter(unsigned int inico_min, unsigned int fim_min, unsigned int &startWorkHour, unsigned int &startWorkMin, unsigned int &endWorkHour, unsigned int &endWorkMin, string &dia);
void TimeWriter(unsigned int startWorkHour, unsigned int startWorkMin, unsigned int endWorkHour, unsigned int endWorkMin);
void TimeWriterBus(unsigned int WorkHour, unsigned int WorkMin);
void BusWithoutDriver(Company &SR);
void DriversAvailable(Company &SR);
bool RestTime(vector<Shift> turnos_driver, unsigned int inicio_min, unsigned int fim_min, unsigned int descanso);
bool is_occupied(vector<Shift> turnos_driver, Shift turno);