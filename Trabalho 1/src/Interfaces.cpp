#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "MyTypes.h"
#include <climits>

using namespace std;

//Declaração de Prótotipos relativos à interface
void Main_Interface(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void gestao_linhas(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void gestao_condutores(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void visu_info(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void cria_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void remove_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers); void read_info(vector<string> &vetor_info, const string filename);
void store_info_line(vector<Line> &lines_info, vector<string> vetor);
void store_info_driver(vector<Driver> &drivers_info, vector<string> vetor);
void cria_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void remove_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_condutor(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
bool valid_number(string number);
void horarios(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void existe_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void stop_to_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void show_avai_all_drivers(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);

// Interface inicial
// Abre os ficheiros, se existirem, referentes as linhas e aos condutores
// Le a informação dos dois ficheiros e guarda-a
void OpenFiles_Interface()
{
	int option;
	
	string file_name_lines, file_name_drivers;
	ifstream f1_file, f2_file;
	vector<string> line_file_info, drivers_file_info;
	vector<Line> lines_info;   //Informação do ficheiro das linhas
	vector<Driver> drivers_info;   //Informação do ficheiro das linhas

	
	//Informacao inicial apresentadada ao utilizador
	cout << "######################################" << endl;
	cout << "######      SEMPREARROLAR       ######" << endl;
	cout << "######################################" << endl;

	cout << endl << "Acesso aos ficheiros necessários." << endl;

	cout << endl << "Nome do ficheiro referente às linhas (.txt): ";
	cin >> file_name_lines; 
	f1_file.open(file_name_lines);
	if(!(f1_file.is_open()))
	{
		cout << "-> Ficheiro inexistente." << endl << endl;
		exit(1);  // O ficheiro nao existe
	}
	cout << "O ficheiro foi aberto com sucesso..." << endl;

	f1_file.close();

	read_info(line_file_info, file_name_lines);

	store_info_line(lines_info, line_file_info);

	cout << "Ficheiro lido com sucesso.";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	cout << endl << endl << "Nome do ficheiro referente aos condutores (.txt): ";
	cin >> file_name_drivers;
	f2_file.open(file_name_drivers);
	if (!(f2_file.is_open()))
	{
		cout << "-> Ficheiro inexistente." << endl << endl;
		exit(1);
	}
	cout << "O ficheiro foi aberto com sucesso..." << endl;	
	f2_file.close();

	read_info(drivers_file_info, file_name_drivers);

	store_info_driver(drivers_info, drivers_file_info);

	cout << "Ficheiro lido com sucesso." << endl << endl;
	
	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info ,file_name_drivers);
}

//Interface principal 
void Main_Interface(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)

{
	int option;
	char value[10];

	//Informacao inicial apresentadada ao utilizador
	cout << "######################################" << endl;
	cout << "######      SEMPREARROLAR       ######" << endl;
	cout << "######################################" << endl;


	cout << endl << "Funcionalidades disponiveis: " << endl << endl;

	cout << "1 - Gestao de linhas" << endl;
	cout << "2 - Gestao de condutores" << endl;
	cout << "3 - Visualizacao de informacao" << endl;
	cout << "4 - Sair" << endl;
	cout << endl << "Introduza uma opcao (1-4): ";        //Opção returnada pelo utilizador
	
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 4))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-4): ";
		cin.get(value, 10);
	}

	option = atoi(value);

	switch (option)
	{
	case 1:
		gestao_linhas(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		gestao_condutores(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		visu_info(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 4:
		break;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Interface linhas 
void gestao_linhas(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	system("CLS");       //Limpa a informação até então apresentada no ecrã

	int option; 
	char value[10];

	cout << "Funcionalidades disponiveis" << endl << endl;
	cout << "1 - Criar uma nova linha" << endl;
	cout << "2 - Modificar uma linha" << endl;
	cout << "3 - Remover uma linha" << endl;
	cout << "4 - Voltar" << endl;
	cout << endl << "Introduza uma opcao (1-4): ";        //Opção returnada pelo utilizador
	
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 4))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-4): ";
		cin.get(value, 10);
	}

	option = atoi(value);

	//Variantes para as diferentes opções tomadas pelo utilizador
	switch (option)
	{
	case 1:
		system("CLS");
		cout << "Criação de uma nova linha" << endl << endl;
		cria_linha(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		modifica_linha(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		system("CLS");
		cout << "Remove linha" << endl << endl;
		remove_linha(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 4:                               
		system("CLS");     
		Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);       //Volta ao ecrã principal
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Interface condutores 
void gestao_condutores(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	system("CLS");      
	int option;
	char value[10];

	cout << "Funcionalidades disponiveis" << endl << endl;
	cout << "1 - Criar um novo condutor" << endl;
	cout << "2 - Modifica condutor" << endl;
	cout << "3 - Remover um condutor " << endl;
	cout << "4 - Voltar" << endl;
	cout << endl << "Introduza uma opcao (1-4): ";        //Opção returnada pelo utilizador
	
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 4))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-4): ";
		cin.get(value, 10);
	}

	option = atoi(value);

	//Variantes para as diferentes opções tomadas pelo utilizador
	switch (option)
	{
	case 1:
		system("CLS");
		cout << "Criação de um novo condutor" << endl << endl;
		cria_condutor(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		modifica_condutor(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		system("CLS");
		cout << "Remover condutor" << endl << endl;
		remove_condutor(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 4:
		system("CLS");
		Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);       //Volta ao ecrã principal
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Interface visualiza informação
void visu_info(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	system("CLS");       //Limpa a informação até então apresentada no ecrã
	int option;
	char value[10];

	cout << "Funcionalidades disponiveis" << endl << endl;
	cout << "1 - Horarios" << endl;
	cout << "2 - Condutores disponiveis" << endl;
	cout << "3 - Trabalho atribuido a um condutor" << endl;
	cout << "4 - Verificar se existe uma paragem para uma dada linha" << endl;
	cout << "5 - Calcular o percurso e o tempo entre duas paragens para uma dada linha" << endl;
	cout << "6 - Calcular para uma dada linha o numero de condutores necessários" << endl;
	cout << "7 - Voltar" << endl;
	cout << endl << "Introduza uma opcao (1-7): ";        //Opção returnada pelo utilizador
	
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 7))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-7): ";
		cin.get(value, 10);
	}

	option = atoi(value);

	//Variantes para as diferentes opções tomadas pelo utilizador
	switch (option)
	{
	case 1:
		system("CLS");
		horarios(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		show_avai_all_drivers(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		//Trabalho atribuido a um condutor - 2ª Parte do trabalho
		system("CLS");
		cout << "Disponivel apenas após a segunda parte do trabalho" << endl << endl;
		break;
	case 4:
		system("CLS");
		existe_stop(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 5:
		system("CLS");
		stop_to_stop(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 6:
		//Calcular para uma dada linha o numero de condutores necessários - 2ª Parte do trabalho
		system("CLS");
		cout << "Disponivel apenas após a segunda parte do trabalho" << endl << endl;
		break;
	case 7:
		system("CLS");
		Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);       //Volta ao ecrã principal
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Lê informacão dos ficheiros
void read_info(vector<string> &vetor_info, const string filename)
{
	ifstream f_file;
	string line;

	f_file.open(filename);

	while (getline(f_file, line))
	{
		vetor_info.push_back(line);
	}

	f_file.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Guarda informação das linhas
void store_info_line(vector<Line> &lines_info, vector<string> vetor)
{
	string line, temp, mult;
	int indicator;
	int limit, number;
	Line variavel;

	for (int i = 0; i < vetor.size(); i++)
	{
		indicator = 0;
		line = vetor.at(i);

		//Identificador unico                              
		limit = line.find_first_of(';');
		temp = line.substr(0, limit);
		number = stoi(temp);
		variavel.ID = number;

		//Frequencia de circulação
		limit = limit + 2;
		line = line.substr(limit, line.size());
		limit = line.find_first_of(';');
		temp = line.substr(0, limit);
		number = stoi(temp);
		variavel.freq_circ = number;

		//Paragens
		line = line.substr((limit + 2), line.size());
		limit = line.find_first_of(';');
		mult = line.substr(0, limit);
		while (mult.find_first_of(',') != std::string::npos)
		{
			int z;
			z = mult.find_first_of(',');
			temp = mult.substr(0, z);
			variavel.stops.push_back(temp);
			mult = mult.substr(z + 2, mult.size());
		}
		variavel.stops.push_back(mult);

		//Tempo entre paragens
		indicator = indicator + (limit + 2);
		line = line.substr((limit + 2), line.size());
		while (line.find_first_of(',') != std::string::npos)
		{
			int z, time;
			z = line.find_first_of(',');
			temp = line.substr(0, z);
			time = stoi(temp);
			variavel.time_stops.push_back(time);
			line = line.substr(z + 1, line.size());
		}
		variavel.time_stops.push_back(stoi(line));
		

		lines_info.push_back(variavel);
		variavel.stops.clear();
		variavel.time_stops.clear();
	}


}  

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Guarda informação dos condutores 
void store_info_driver(vector<Driver> &drivers_info, vector<string> vetor)
{
	string driver, name, temp;
	int indicator, limit, number;
	Driver variavel;

	for (int i = 0; i < vetor.size(); i++)
	{
		driver = vetor.at(i);

		//Identificador numerico unico
		limit = driver.find_first_of(';');
		temp = driver.substr(0, limit);
		number = stoi(temp);
		variavel.ID = number;

		//Nome
		driver = driver.substr((limit + 2), driver.size());
		limit = driver.find_first_of(';');
		temp = driver.substr(0, (limit-1));
		variavel.name = temp;

		//Numero de horas por dia
		driver = driver.substr((limit + 2), driver.size());
		limit = driver.find_first_of(';');
		temp = driver.substr(0, limit);
		number = stoi(temp);
		variavel.hours_day = number;

		//Numero de horas maximo por semana
		driver = driver.substr((limit + 2), driver.size());
		limit = driver.find_first_of(';');
		temp = driver.substr(0, limit);
		number = stoi(temp);
		variavel.max_hours = number;

		//Numero minimo de horas de descanso
		driver = driver.substr((limit + 2), driver.size());
		limit = driver.find_first_of(';');
		temp = driver.substr(0, limit);
		number = stoi(temp);
		variavel.rest_time = number;

		drivers_info.push_back(variavel);

	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se o número é valido
bool valid_number(string number)
{
	for (int i = 0; i < number.size(); i++)
	{
		if (!(isdigit(number.at(i))))
		{
			return false;
		}
	}

	return true;
}
