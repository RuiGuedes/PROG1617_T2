#include "Driver.h"
#include "Line.h"
#include "Shift.h"
#include "Company.h"
#include "Prototipos.h"
#include <conio.h>



//-------------------------//
//-------CLASS DRIVER------//
//-------------------------//

Driver::Driver(){
	id = 0;
	name = "unknown";
	maxHours = 0;
	maxWeekWorkingTime = 0;
	minRestTime = 0;
	spare = true;
	totalTime = 0;
} //Default constructor

Driver::Driver(string textLine){

	istringstream text(textLine);
	vector<Shift> vec;

	text >> id; text.ignore(10, ';'); text.ignore(10, ' ');
	getline(text, name, ';');
	text >> maxHours; text.ignore(10, ';');
	text >> maxWeekWorkingTime; text.ignore(10, ';');
	text >> minRestTime;
	shifts = vec;
	spare = true;
	totalTime = 0;
}

/////////////////
// Get methods //
/////////////////

unsigned int Driver::getId() const {
	return id;
}
string Driver::getName() const{
	return name;
}
unsigned int Driver::getShiftMaxDuration() const{
	return maxHours;
}
unsigned int Driver::getMaxWeekWorkingTime() const{
	return maxWeekWorkingTime;
}
unsigned int Driver::getMinRestTime() const{
	return minRestTime;
}
vector<Shift> Driver::getShifts() const{
	return shifts;
}
bool Driver::getspare() const{
	return spare;
}
unsigned int Driver::getTotalTime() const {
	return totalTime;
}

/////////////////
// Set methods //
/////////////////

void Driver::setId(unsigned int newId) {
	id = newId;
}
void Driver::setName(string newName) {
	name = newName;
}
void Driver::setMaxHours(unsigned int newMaxHours) {
	maxHours = newMaxHours;
}
void Driver::setMaxWeekWorkingTime(unsigned int newMaxWeekWorkingTime) {
	maxWeekWorkingTime = newMaxWeekWorkingTime;
}
void Driver::setMinRestTime(unsigned int newMinRestTime) {
	minRestTime = newMinRestTime;
}
void Driver::setShifts(vector<Shift> newShifts) {
	shifts = newShifts;

	int duracaoShift, tempTotal = 0;

	for (int i = 0; i < shifts.size(); i++)
	{
		duracaoShift = shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
		tempTotal += duracaoShift;
	}

	totalTime = tempTotal;
}
void Driver::setspare()
{
	this->spare = false;
}


//-----------------------------//
//-------DRIVER FUNCTIONS------//
//-----------------------------//

//Cria condutor novo
void cria_condutor(Company &SR)
{
	int ID, hours_day, maxWeekWorkingTime, rest_time;
	char value[10];
	Driver variavel;
	string temp, var;
	vector<Driver> drivers_info = SR.getVecDriver();

	// Verifica se o ID é possivel e quando o for, estabelece o novo ID
	do
	{
		cout << "Identificador numérico unico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (exist_ID_driver(drivers_info, ID))
			cout << "Este identificador único já se encontra utilizado." << endl << "Tente novamente." << endl << endl;

	} while (exist_ID_driver(drivers_info, ID));

	variavel.setId(ID);

	do
	{
		cout << "\nNome do condutor: ";
		cin.ignore(1000, '\n');
		getline(cin, temp);

		if (temp == "")
		{
			cout << "Nome inválido." << endl << "Para sair prima (S), para tentar novamente prima (ENTER): ";
			cin.get(value, 1);
			cin.ignore(1000, '\n');
			cin.clear();
			var = atoi(value);
			if (var == "S")
				return;
			else
				continue;
		}
	}
	while (temp == "");

	cout << endl;
	cout << "Prima (ENTER) para agora definir o horário do condutor: ";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();

	variavel.setName(temp);

	cout << "\nHoras do turno diário: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Horas do turno diário: ";
		cin.get(value, 10);
	}

	hours_day = atoi(value);
	variavel.setMaxHours(hours_day);

	cout << "\nNúmero máximo de horas de trabalho por semana: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();
	while (valid_number(value) == false || (atoi(value) >= 120) || (atoi(value) < hours_day))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Número máximo de horas de trabalho por semana: ";
		cin.get(value, 10);
	}

	maxWeekWorkingTime = atoi(value);
	variavel.setMaxWeekWorkingTime(maxWeekWorkingTime);

	cout << "\nNúmero de horas de descanso por turno: ";

	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();
	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Número de horas de descanso por turno: ";
		cin.get(value, 10);
	}

	rest_time = atoi(value);
	variavel.setMinRestTime(rest_time);

	drivers_info.push_back(variavel);

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "\nCondutor criado com sucesso." << endl << endl;

	cout << "Press any key to continue . . .";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();
	system("CLS");
	return;
}

//Remove condutor 
void remove_condutor(Company &SR)
{
	int ID;
	char value[10];
	vector<Driver> vec_driver = SR.getVecDriver();

	do
	{
		cout << "Identificador numérico unico do condutora a remover: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(vec_driver, ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(vec_driver, ID)); //Verifica se o ID existe


	// Apaga o condutor com o ID indicado
	for (int i = 0; i < vec_driver.size(); i++)
	{
		if (vec_driver.at(i).getId() == ID)
		{
			vec_driver.erase(vec_driver.begin() + i);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(vec_driver);
	write_data_driver(vec_driver, SR.getFichDrivers());

	cout << "Condutor removido com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	return;
}

//Modifica condutor - Interface 
void modifica_condutor(Company &SR)
{
	int option;

	do
	{
		
		char value[10];

		cout << "Modifica condutor" << endl << endl;

		cout << "Funcionalidades disponiveis" << endl << endl;
		cout << "1 - Modificar identificar numérico unico" << endl;
		cout << "2 - Modificar nome do condutor" << endl;
		cout << "3 - Modifica o número de horas consecutivas de condução diária" << endl;
		cout << "4 - Modifica o número máximo de horas que pode conduzir por semana" << endl;
		cout << "5 - Modifica o número mínimo de horas de descanso obrigatório entre turnos." << endl;
		cout << "6 - Voltar" << endl;

		cout << endl << "Introduza uma opcao (1-6): ";
		cin.ignore(1000,'\n');
		cin.get(value, 10);
		cin.clear();
	
		//Verifica se existe erro na introdução da opção.
		while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 6))
		{
			cin.clear();
			
			cout << "Opcao invalida ! Tente novamente. " << endl;
			cout << "Introduza uma opcao (1-6): ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		option = atoi(value);

		//Variantes para as diferentes opções tomadas pelo utilizador
		switch (option)
		{
		case 1:
			system("CLS");
			modifica_driver_ID(SR);
			break;
		case 2:
			system("CLS");
			modifica_driver_name(SR);
			break;
		case 3:
			system("CLS");
			modifica_driver_HoursDay(SR);
			break;
		case 4:
			system("CLS");
			modifica_driver_MaxHours(SR);
			break;
		case 5:
			system("CLS");
			modifica_driver_RestTime(SR);
			break;
		case 6:
			system("CLS");
			break;
		}
	} while (option != 6);
	return;
}

//Modifica o identificador numérico do condutor 
void modifica_driver_ID(Company &SR)
{
	int ID, old_ID;
	char value[10];
	vector<Driver> drivers_info = SR.getVecDriver();

	system("CLS");

	cout << "Modificar identificar numérico unico" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe ." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	//Recebe novo ID
	do
	{
		cout << "Novo Identificador numérico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico já existe" << endl << "Tente novamente." << endl << endl;

	} while (exist_ID_driver(drivers_info, ID));

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == old_ID)
		{
			drivers_info.at(i).setId(ID);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "Identificador numérico modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	return;
}

//Modifica o nome do condutor 
void modifica_driver_name(Company &SR)
{
	int old_ID;
	string new_name, var;
	char value[10];
	vector<Driver> drivers_info = SR.getVecDriver();

	system("CLS");

	cout << "Modificar nome do condutor" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	do
	{
		cout << "\nNome do condutor: ";
		cin.ignore(1000, '\n');
		getline(cin, new_name);

		if (new_name == "")
		{
			cout << "Nome inválido." << endl << "Para sair prima (S), para tentar novamente prima (ENTER): ";
			cin.get(value, 1);
			cin.ignore(1000, '\n');
			cin.clear();
			var = atoi(value);
			if (var == "S")
				return;
			else
				continue;
		}
	} while (new_name == "");


	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == old_ID)
		{
			drivers_info.at(i).setName(new_name);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "Nome modificado com sucesso." << endl << endl;

	cout << "Press any key to continue . . .";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();
	system("CLS");
	return;
}

//Modifica o turno diário do condutor 
void modifica_driver_HoursDay(Company &SR)
{
	int hours_day, ID;
	char value[10];
	vector<Driver> drivers_info = SR.getVecDriver();

	system("CLS");

	cout << "Modifica o número de horas consecutivas de condução diária" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, ID)); //Verifica se o ID é possivel

	cout << "Número de horas consecutivas de condução diária: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();
	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Número de horas consecutivas de condução diária inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número de horas consecutivas de condução diária: ";
		cin.get(value, 10);
	}

	hours_day = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == ID)
		{
			drivers_info.at(i).setMaxHours(hours_day);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "Turno diário modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	return;
}

//Modifica o numero max de horas de trabalho por semana do condutor 
void modifica_driver_MaxHours(Company &SR)
{
	int max_hours, ID, hours_day;
	char value[10];
	vector<Driver> drivers_info = SR.getVecDriver();

	system("CLS");

	cout << "Modifica o número máximo de horas que pode conduzir por semana" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, ID)); //Verifica se o ID é possivel

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == ID)
		{
			hours_day = drivers_info.at(i).getShiftMaxDuration();
			break;
		}
	}

	cout << "Número máximo de horas que pode conduzir por semana: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();
	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 120) || (atoi(value) < hours_day))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Número máximo de horas que pode conduzir por semana inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número máximo de horas que pode conduzir por semana: ";
		cin.get(value, 10);
	}

	max_hours = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == ID)
		{
			drivers_info.at(i).setMaxWeekWorkingTime(max_hours);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "Número máximo de horas que pode conduzir por semana modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	return;
}

//Modifica o tempo de descanso do condutor 
void modifica_driver_RestTime(Company &SR)
{
	int rest_time, ID;
	char value[10];
	vector<Driver> drivers_info = SR.getVecDriver();

	system("CLS");

	cout << "Modifica o número mínimo de horas de descanso obrigatório entre turnos" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, ID)); //Verifica se o ID é possivel

	cout << "Número mínimo de horas de descanso obrigatório entre turnos: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);
	cin.clear();
	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Número mínimo de horas de descanso obrigatório entre turnos inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número mínimo de horas de descanso obrigatório entre turnos: ";
		cin.get(value, 10);
	}

	rest_time = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == ID)
		{
			drivers_info.at(i).setMinRestTime(rest_time);
		}
	}

	//Atualiza informação do ficheiro e da empresa
	SR.setDrivers(drivers_info);
	write_data_driver(drivers_info, SR.getFichDrivers());

	cout << "Número mínimo de horas de descanso obrigatório entre turnos modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	return;
}

//Escreve a informação dos condutores no ficheiro
void write_data_driver(vector<Driver> &drivers_info, string const file_name_drivers)
{
	ofstream output_file;

	output_file.open(file_name_drivers);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		output_file << drivers_info.at(i).getId() << " ; " 
			<< drivers_info.at(i).getName() << " ; " 
			<< drivers_info.at(i).getShiftMaxDuration() << " ; "
			<< drivers_info.at(i).getMaxWeekWorkingTime() << " ; " 
			<< drivers_info.at(i).getMinRestTime() << endl;
	}
}