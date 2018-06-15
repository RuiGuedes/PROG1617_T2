#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Prototipos.h"

Company::Company(string name, string fichDrivers, string fichLines) {
	this->name = name;
	this->fichDrivers = fichDrivers;
	this->fichLines = fichLines;
}

/////////////////
// Get methods //
/////////////////

string Company::getName() const {
	return name;
}
string Company::getFichDrivers() const {
	return fichDrivers;
}
string Company::getFichLines() const {
	return fichLines;
}
vector<Driver> Company::getVecDriver() const {
	return drivers;
}
vector<Line> Company::getVecLines() const {
	return lines;
}


/////////////////
// Set methods //
/////////////////

void Company::setName(string name) {
	this->name = name;
}
void Company::setDrivers(vector<Driver> drivers) {
	this->drivers = drivers;
}
void Company::setLines(vector<Line> lines) {
	this->lines = lines;
}

////////////////////
//  Other methods //
////////////////////

void Company::addLineBusData(unsigned int LineID, vector<Bus> busData)
{
	LineBusData.insert(pair<int, vector<Bus>>(LineID, busData));
}

//Informa��o de um autocarro
void info_bus(Company &SR)
{
	system("CLS");

	int ID, num_ordem, max_ordem;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<Bus> bus;

	cout << "Informa��o de um autocarro\n\n";

	do
	{
		cout << "Identificador da linha a que pertence o autocarro: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador inv�lido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador da linha a que pertence o autocarro: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador n�o existe." << endl << "Tente novamente." << endl << endl;
	} while (!exist_ID_linha(lines_info, ID));

	multimap<unsigned int, vector<Bus>>::iterator p = SR.LineBusData.find(ID);
	for (auto p : SR.LineBusData)
	{
		if (p.first == ID) {
			bus = p.second;
			break;
		}
	}
	max_ordem = bus.size();

	do
	{
		cout << "N�mero de ordem do autocarro (1-" << max_ordem << ") : ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "N�mero inv�lido." << endl << "Tente novamente." << endl << endl;
			cout << "N�mero de ordem do autocarro: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		num_ordem = atoi(value);

		if (max_ordem < num_ordem || num_ordem <= 0)
			cout << "Este n�mero de ordem n�o existe." << endl << "Tente novamente." << endl << endl;
	} while (max_ordem < num_ordem || num_ordem <= 0);


	for (int i = 0; i < max_ordem; i++)
	{
		if (bus.at(i).getBusOrderInLine() == num_ordem)
		{
			cout << bus.at(i);
			break;
		}
	}

	system("pause");
	system("CLS");
	return;
}

//Atribui��o de trabalho a um condutor, para uma dada linha, autocarro e n�mero de ordem
void atribuir_trabalho(Company &SR)
{
	system("CLS");

	char resp;
	int Id_line, Id_driver, ind_driver, num_ordem, max_ordem, num_turno; // ind = indicador
	int duracao_turno = 0, trabalho_total_sem = 0, trabalho_total_dia;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<Driver> driver_info = SR.getVecDriver();
	vector<Bus> bus;

	cout << "Atribui��o de trabalho a um Condutor" << endl << endl;

	do //Pede e recebe o identificador v�lido do condutor a quem vai ser atribuido o trabalho
	{
		cout << "Identificador do condutor: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador inv�lido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador do condutor: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		Id_driver = atoi(value);

		for (int i = 0; i < driver_info.size(); i++)
		{
			if (driver_info.at(i).getId() == Id_driver) {
				ind_driver = i;
				break;
			}
		}

		if (!exist_ID_driver(driver_info, Id_driver))
			cout << "Este identificador n�o existe." << endl << "Tente novamente." << endl << endl;
		else if (!driver_info.at(ind_driver).getspare())
			cout << "Condutor ocupado." << "Indique outro condutor." << endl << endl;
	} while (!exist_ID_driver(driver_info, Id_driver) || !driver_info.at(ind_driver).getspare());

	do {
		if (!driver_info.at(ind_driver).getspare())
		{
			cout << "Condutor ocupado." << endl;
			system("pause");
			system("CLS");
			return;
		}

		do //Pede e recebe o identificador v�lido da linha onde o condutor vai trabalhar
		{
			cout << "Identificador da linha a atribuir ao condutor: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get(value, 10);
			cin.clear();
			while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
			{
				cin.clear();
				cout << "Identificador inv�lido." << endl << "Tente novamente." << endl << endl;
				cout << "Identificador da linha a atribuir ao condutor: ";
				cin.ignore(1000, '\n');
				cin.get(value, 10);
			}

			Id_line = atoi(value);

			if (!exist_ID_linha(lines_info, Id_line))
				cout << "Este identificador n�o existe." << endl << "Tente novamente." << endl << endl;
		} while (!exist_ID_linha(lines_info, Id_line));


		multimap<unsigned int, vector<Bus>>::iterator p = SR.LineBusData.find(Id_line);
		for (auto p : SR.LineBusData)
		{
			if (p.first == Id_line) {
				bus = p.second;
				break;
			}
		}
		max_ordem = bus.size();

		do //Pede e recebe o n�mero de ordem do autocarro que o condutor vai conduzir
		{
			cout << "N�mero de ordem do autocarro (1-" << max_ordem << ") : ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get(value, 10);
			cin.clear();
			while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
			{
				cin.clear();
				cout << "N�mero inv�lido." << endl << "Tente novamente." << endl << endl;
				cout << "N�mero de ordem do autocarro: ";
				cin.ignore(1000, '\n');
				cin.get(value, 10);
			}

			num_ordem = atoi(value);

			if (max_ordem < num_ordem || num_ordem < 0)
				cout << "Este n�mero de ordem n�o existe." << endl << "Tente novamente." << endl << endl;
		} while (max_ordem < num_ordem || num_ordem < 0);

		//Mostra os turnos_bus disponiveis
		vector<Shift> turnos_bus = bus.at(num_ordem - 1).getSchedule();

		cout << "Lista de turnos sem condutor:\n";

		for (int j = 1; j <= turnos_bus.size(); j++)
		{
			if (turnos_bus.at(j - 1).getAvailable())		// se available = true
				cout << j << " ::\n" << turnos_bus.at(j - 1) << "\n\n";
		}

		//Verifica se o turno existe ou n�o
		do //Pede e recebe o n�mero do num_turno para o condutor
		{
			cout << "N�mero do turno: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get(value, 10);
			cin.clear();
			while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
			{
				cin.clear();
				cout << "N�mero inv�lido." << endl << "Tente novamente." << endl << endl;
				cout << "N�mero do turno: ";
				cin.ignore(1000, '\n');
				cin.get(value, 10);
			}

			num_turno = atoi(value);

			if (turnos_bus.size() < num_turno || num_turno < 0 || !turnos_bus.at(num_turno - 1).getAvailable())
				cout << "Este n�mero n�o existe na lista anterior." << endl << "Tente novamente." << endl << endl;
		} while (turnos_bus.size() < num_turno || num_turno < 0 || !turnos_bus.at(num_turno - 1).getAvailable());

		//Guardas os turnos do condutor 
		vector<Shift> turnos_driver = driver_info.at(ind_driver).getShifts();
		
		trabalho_total_sem = driver_info.at(ind_driver).getTotalTime();
		duracao_turno = turnos_bus.at(num_turno - 1).getEndTime() - turnos_bus.at(num_turno - 1).getStartTime();

		if (driver_info.at(ind_driver).getShiftMaxDuration() * 60 < duracao_turno)
			cout << "O codutor excede o m�ximo de horas consecutivas que pode conduzir." << endl;

		else if (trabalho_total_sem + duracao_turno > driver_info.at(ind_driver).getMaxWeekWorkingTime() * 60)
			cout << "O codutor excede o m�ximo de horas semanais que pode conduzir." << endl;

		else if (is_occupied(turnos_driver, turnos_bus.at(num_turno - 1)))
			cout << "O condutor j� se encontra ocupado neste hor�rio." << endl;

		else if (RestTime(turnos_driver, turnos_bus.at(num_turno - 1).getStartTime(), turnos_bus.at(num_turno - 1).getEndTime(), driver_info.at(ind_driver).getMinRestTime()*60) == false)
			cout << "O n�mero m�nimo de horas de descanso n�o foi respeitado." << endl;

		else
		{
			turnos_bus.at(num_turno - 1).setDriverId(Id_driver);
			turnos_bus.at(num_turno - 1).setAvailable(false);

			bus.at(num_ordem - 1).setSchedule(turnos_bus);

			multimap<unsigned int, vector<Bus>>::iterator p = SR.LineBusData.find(Id_line);
			for (auto p : SR.LineBusData)
			{
				if (p.first == Id_line) {
					SR.LineBusData.erase(Id_line);
					SR.LineBusData.insert(pair<unsigned int, vector<Bus>>(Id_line, bus));
					break;
				}
			}

			turnos_driver.push_back(turnos_bus.at(num_turno - 1));
			driver_info.at(ind_driver).setShifts(turnos_driver);

			if (driver_info.at(ind_driver).getTotalTime() == driver_info.at(ind_driver).getMaxWeekWorkingTime()*60)	
				driver_info.at(ind_driver).setspare();	//Se atingir o maximo de horas semanais, fica indispon�vel (spare = False)

			SR.setDrivers(driver_info);
			cout << "Trabalho atribuido com sucesso." << endl;
		}
		
		cout << "Atribuir outro trabalho ao condutor ? (S ou N) : ";
		cin >> resp;

	} while (resp == 'S');

	system("pause");
	system("CLS");
	return;
}
