#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "MyTypes.h"
#include<stdio.h> 


using namespace std;

//Declaração de Prótotipos relativos à interface
void store_info_driver(vector<Driver> &drivers_info, vector<string> vetor);
void cria_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void remove_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void write_data_driver(vector<Driver> &drivers_info, string const file_name_drivers);
bool valid_number(string number);
bool exist_ID_driver(vector<Driver> drivers_info, const int ID);
void modifica_driver_ID(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_driver_name(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_driver_HoursDay(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_driver_MaxHours(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_driver_RestTime(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void Main_Interface(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void gestao_condutores(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Cria condutor novo 
void cria_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int ID, hours_day, max_hours, rest_time;
	char value[10];
	Driver variavel;
	string temp;

	do
	{
		cout << "Identificador numérico unico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (exist_ID_driver(drivers_info, ID))
			cout << "Este identificador único já se encontra utilizado." << endl << "Tente novamente." << endl << endl;

	} while (exist_ID_driver(drivers_info, ID)); //Verifica se o ID é possivel

	variavel.ID = ID;

	system("CLS");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Criação de um novo condutor" << endl << endl;

	cout << "Nome do condutor: ";
	cin.ignore(1000, '\n');
	getline(cin, temp);

	variavel.name = temp;
	system("CLS");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Criação de um novo condutor" << endl << endl;

	cout << "Horas do turno diário: ";
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Horas do turno diário: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	hours_day = atoi(value);
	variavel.hours_day = hours_day;
	system("CLS");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Criação de um novo condutor" << endl << endl;

	cout << "Número máximo de horas de trabalho por semana: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= (hours_day * 7)) || (atoi(value) >= 168))
	{
		cin.clear();
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Número máximo de horas de trabalho por semana: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	max_hours = atoi(value);
	variavel.max_hours = max_hours;
	system("CLS");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	cout << "Criação de um novo condutor" << endl << endl;

	cout << "Número de horas de descanso por turno: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Número de horas de descanso por turno: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	rest_time = atoi(value);
	variavel.rest_time = rest_time;

	drivers_info.push_back(variavel);

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Condutor criado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Remove condutor novo 
void remove_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int ID;
	char value[10];

	do
	{
		cout << "Identificador numérico unico do condutora a remover: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, ID)); //Verifica se o ID é possivel

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == ID)
		{
			drivers_info.erase(drivers_info.begin() + i);
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Condutor removido com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica condutor - Interface 
void modifica_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int option;
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
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (stoi(value) < 1) || (stoi(value) > 6))
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
		modifica_driver_ID(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		modifica_driver_name(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		system("CLS");
		modifica_driver_HoursDay(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 4:
		system("CLS");
		modifica_driver_MaxHours(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 5:
		system("CLS");
		modifica_driver_RestTime(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 6:
		gestao_condutores(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Escreve a informação dos condutores no ficheiro
void write_data_driver(vector<Driver> &drivers_info, string const file_name_drivers)
{
	ofstream output_file;

	output_file.open(file_name_drivers);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		output_file << drivers_info.at(i).ID << " ; " << drivers_info.at(i).name << " ; " << drivers_info.at(i).hours_day << " ; " << drivers_info.at(i).max_hours << " ; " << drivers_info.at(i).rest_time << endl;
	}

}

//Verifica se o identificador unico já se encontra ocupado.
//Devolve TRUE quando já está ocupado
//Devolve FALSE quando não está ocupado 
bool exist_ID_driver(vector<Driver> drivers_info, const int ID)
{
	vector<int> ID_off;

	for(int i = 0; i < drivers_info.size(); i++)
	{
		ID_off.push_back(drivers_info.at(i).ID);
	}

	for (int i = 0; i < ID_off.size(); i++)
	{
		if(ID_off.at(i) == ID)
		{
			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o identificador numérico do condutor 
void modifica_driver_ID(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int ID, old_ID;
	char value[10];

	system("CLS");

	cout << "Modificar identificar numérico unico" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
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

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (exist_ID_driver(drivers_info, ID))
			cout << "Este identificador numérico já existe" << endl << "Tente novamente." << endl << endl;

	} while (exist_ID_driver(drivers_info, ID));


	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == old_ID)
		{
			drivers_info.at(i).ID = ID;
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Identificador numérico modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o nome do condutor 
void modifica_driver_name(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int old_ID;
	string new_name;
	char value[10];

	system("CLS");

	cout << "Modificar nome do condutor" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	cout << "Nome do novo condutor: ";
	cin.ignore(1000, '\n');
	getline(cin, new_name);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == old_ID)
		{
			drivers_info.at(i).name = new_name;
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Nome modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o turno diário do condutor 
void modifica_driver_HoursDay(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int hours_day,old_ID;
	char value[10];

	system("CLS");

	cout << "Modifica o número de horas consecutivas de condução diária" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	cout << "Número de horas consecutivas de condução diária: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cout << "Número de horas consecutivas de condução diária inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número de horas consecutivas de condução diária: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	hours_day = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == old_ID)
		{
			drivers_info.at(i).hours_day = hours_day;
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Turno diário modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o numero max de horas de trabalho por semana do condutor 
void modifica_driver_MaxHours(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int max_hours, old_ID;
	char value[10];

	system("CLS");

	cout << "Modifica o número máximo de horas que pode conduzir por semana" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	cout << "Número máximo de horas que pode conduzir por semana: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 168))
	{
		cin.clear();
		cout << "Número máximo de horas que pode conduzir por semana inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número máximo de horas que pode conduzir por semana: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	max_hours = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == old_ID)
		{
			drivers_info.at(i).max_hours = max_hours;
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Número máximo de horas que pode conduzir por semana modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o tempo de descanso do condutor 
void modifica_driver_RestTime(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int rest_time, old_ID;
	char value[10];

	system("CLS");

	cout << "Modifica o número mínimo de horas de descanso obrigatório entre turnos" << endl << endl;

	do
	{
		cout << "Identificador numérico unico a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador numérico unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador numérico unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		old_ID = atoi(value);

		if (!exist_ID_driver(drivers_info, old_ID))
			cout << "Este identificador numérico único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(drivers_info, old_ID)); //Verifica se o ID é possivel

	cout << "Número mínimo de horas de descanso obrigatório entre turnos: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) <= 0) || (atoi(value) >= 24))
	{
		cin.clear();
		cout << "Número mínimo de horas de descanso obrigatório entre turnos inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Número mínimo de horas de descanso obrigatório entre turnos: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	rest_time = atoi(value);

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).ID == old_ID)
		{
			drivers_info.at(i).rest_time = rest_time;
		}
	}

	write_data_driver(drivers_info, file_name_drivers);

	cout << "Número mínimo de horas de descanso obrigatório entre turnos modificado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}