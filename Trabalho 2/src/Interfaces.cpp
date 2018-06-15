#include <iostream>
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
#include "Prototipos.h"

using namespace std;

unsigned int start_time = 480;  //Trabalho comeca as 8:00 (SEGUNDA-FEIRA)
unsigned int end_time = 7140;	//Trabalho termina as 23:00 (SEXTA-FEIRA)

// Interface inicial
// Abre os ficheiros, se existirem, referentes as linhas e aos condutores
// Le a informação dos dois ficheiros e guarda-a
void OpenFiles_Interface()
{
	string file_name_lines, file_name_drivers;
	ifstream f1_file, f2_file;
	vector<string> line_file_info, drivers_file_info;
	vector<Line> line_info;		   //Informação do ficheiro das linhas
	vector<Driver> drivers_info;   //Informação do ficheiro das linhas

	
	//Informacao inicial apresentadada ao utilizador
	cout << "######################################" << endl;
	cout << "######      SEMPREARROLAR       ######" << endl;
	cout << "######################################" << endl;

	cout << endl << "Acesso aos ficheiros necessários." << endl;

	//////////////////////////////////
	// Nome do ficheiro das linhas ///
	//////////////////////////////////

	cout << endl << "Nome do ficheiro referente às linhas (.txt): ";
	cin >> file_name_lines;
	f1_file.open(file_name_lines);
	if (!(f1_file.is_open()))
	{
		cout << "-> Ficheiro inexistente." << endl;
		exit(1);
	}
	cout << "O ficheiro foi aberto com sucesso." << endl;

	f1_file.close();

	//////////////////////////////////////////////////////////
	// Leitura e armazenamento dos dados do ficheiro linhas //
	//////////////////////////////////////////////////////////

	read_info(line_file_info, file_name_lines);

	store_info_line(line_info, line_file_info);

	cout << "Ficheiro lido com sucesso.";


	//////////////////////////////////////
	// Nome do ficheiro dos condutores ///
	//////////////////////////////////////

	cout << endl << endl << "Nome do ficheiro referente aos condutores (.txt): ";
	cin >> file_name_drivers;
	f2_file.open(file_name_drivers);
	if (!(f2_file.is_open()))
	{
		cout << "-> Ficheiro inexistente." << endl;
		exit(1);
	}
	cout << "O ficheiro foi aberto com sucesso..." << endl;	
	f2_file.close();

	//////////////////////////////////////////////////////////////
	// Leitura e armazenamento dos dados do ficheiro condutores //
	//////////////////////////////////////////////////////////////

	read_info(drivers_file_info, file_name_drivers);

	store_info_driver(drivers_info, drivers_file_info);

	cout << "Ficheiro lido com sucesso." << endl << endl;

	Company SR ("SEMPREARROLAR", file_name_drivers, file_name_lines);

	SR.setLines(line_info);
	SR.setDrivers(drivers_info);

	store_info_Bus(SR, line_info);  //Guarda a informação relativa aos autocarros
	
	system("pause");
	system("CLS");
	Main_Interface(SR);
}

//Interface principal 
void Main_Interface(Company &SR)
{
	int option;
	do 
	{
		char value[10];

		//Informacao inicial apresentadada ao utilizador
		cout << "######################################" << endl;
		cout << "######      SEMPREARROLAR       ######" << endl;
		cout << "######################################" << endl;


		cout << endl << "Funcionalidades disponiveis: " << endl << endl;

		cout << "1 - Gestao de condutores" << endl;
		cout << "2 - Visualizacao de informacao" << endl;
		cout << "3 - Sair" << endl;
		cout << endl << "Introduza uma opcao (1-3): ";        //Opção returnada pelo utilizador
		
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		//Executa este ciclo até receber um valor válido
		while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 3))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Opcao invalida ! Tente novamente. " << endl;
			cout << "Introduza uma opcao (1-3): ";
			cin.get(value, 10);
		}

		option = atoi(value);

		//Opcões possiveis apresentadas no menu 
		switch (option)
		{
		case 1:
			gestao_condutores(SR);
			break;
		case 2:
			visu_info(SR);
			break;
		case 3:
			cout << endl;
			break;
		}
	} while (option != 3);
}

//Interface condutores 
void gestao_condutores(Company &SR)
{
	system("CLS");      
	int option;
	do
	{
		char value[10];

		cout << "Funcionalidades disponiveis" << endl << endl;
		cout << "1 - Criar um novo condutor" << endl;
		cout << "2 - Modifica condutor" << endl;
		cout << "3 - Remover um condutor " << endl;
		cout << "4 - Atribuir trabalho a um condutor " << endl;
		cout << "5 - Voltar" << endl;
		cout << endl << "Introduza uma opcao (1-5): ";        //Opção returnada pelo utilizador
		
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		//Verifica se existe erro na introdução da opção.
		while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 5))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Opcao invalida ! Tente novamente. " << endl;
			cout << "Introduza uma opcao (1-5): ";
			cin.get(value, 10);
		}

		option = atoi(value);

		//Variantes para as diferentes opções tomadas pelo utilizador
		switch (option)
		{
		case 1:
			system("CLS");
			cout << "Criação de um novo condutor" << endl << endl;
			cria_condutor(SR);
			break;
		case 2:
			system("CLS");
			modifica_condutor(SR);
			break;
		case 3:
			system("CLS");
			cout << "Remover condutor" << endl << endl;
			remove_condutor(SR);
			break;
		case 4:
			system("CLS");
			atribuir_trabalho(SR);
			break;
		case 5:
			system("CLS");
			break;
		}
	} while (option != 5);
}

//Interface visualiza informação
void visu_info(Company &SR)
{
	system("CLS");       //Limpa a informação até então apresentada no ecrã
	int option;

	do
	{
		char value[10];
	
		cout << "Funcionalidades disponiveis" << endl << endl;
		cout << "1 - Horário de uma paragem" << endl;
		cout << "2 - Trabalho atribuido a um condutor" << endl;
		cout << "3 - Informação de um autocarro" << endl;
		cout << "4 - Informação de uma linha e respetivo horário" << endl;
		cout << "5 - Linhas que incluem determinada paragem" << endl;
		cout << "6 - Visualizar o percurso e o tempo entre duas paragens" << endl;
		cout << "7 - Lista de todos os períodos de autocarros sem condutor atribuído" << endl;
		cout << "8 - Lista de todos os períodos de condutores sem o serviço completo atribuído" << endl;
		cout << "9 - Voltar" << endl;
		cout << endl << "Introduza uma opcao (1-9): ";        //Opção returnada pelo utilizador

		cin.ignore(1000, '\n');
		cin.get(value, 10);

		//Verifica se existe erro na introdução da opção.
		while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 10))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Opcao invalida ! Tente novamente. " << endl;
			cout << "Introduza uma opcao (1-9): ";
			cin.get(value, 10);
		}

		option = atoi(value);

		//Variantes para as diferentes opções tomadas pelo utilizador
		switch (option)
		{
		case 1:
			horario_stop(SR);		//Horario de uma paragem
			break;
		case 2:
			DriverWork(SR);		    //Trabalho atribuido a um condutor
			break;
		case 3:
			info_bus(SR);			//Informação de um autocarro
			break;
		case 4:
			info_line(SR);			//Informação de uma linha e respetivo horário
			break;
		case 5:
			existe_stop(SR);		//Linhas que incluem determinada paragem
			break;
		case 6:
			stop_to_stop(SR);		//Visualizar o percurso e o tempo entre duas paragens
			break;
		case 7:
			BusWithoutDriver(SR);	//Lista de todos os períodos de autocarros sem condutor atribuído
			break;
		case 8:
			DriversAvailable(SR);	//Lista de todos os períodos de condutores sem o serviço completo atribuído
			break;
		case 9:
			system("CLS");
			break;
		}
	} while (option != 9);
}

//Lê informacão dos ficheiros
void read_info(vector<string> &vetor_info, string filename)
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

//Guarda informação das linhas no vetor de linhas da empresa
void store_info_line(vector<Line> &line_vector, vector<string> vetor)
{
	for (int i = 0; i < vetor.size(); i++)
	{
		Line linha(vetor.at(i));
		line_vector.push_back(linha); 
	}
}  

//Guarda informação dos condutores no vetor de condutores da empresa
void store_info_driver(vector<Driver> &driver_vector, vector<string> vetor)
{
	for (int i = 0; i < vetor.size(); i++)
	{
		Driver condutor(vetor.at(i));
		driver_vector.push_back(condutor);
	}
}

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

//Verifica se o ID existe na linha
bool exist_ID_linha(vector<Line> line_vector, const int ID)
{
	for (int i = 0; i < line_vector.size(); i++)
	{
		if (ID == line_vector.at(i).getId())
		{
			return true;
		}
	}
	return false;
}

//Verifica se existe a paragem 
//Devolve TRUE se já existir
//Devolve FALSE caso não exista
bool exist_stop_variavel(vector<string> variavel_stops, const string stop)
{
	for (int i = 0; i < variavel_stops.size(); i++)
	{
		if (variavel_stops.at(i) == stop)
		{
			return true;
		}
	}
	return false;
}

//Verifica se o identificador unico já se encontra ocupado.
//Devolve TRUE quando já está ocupado
//Devolve FALSE quando não está ocupado 
bool exist_ID_driver(vector<Driver> drivers_info, const int ID)
{
	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).getId() == ID)
		{
			return true;
		}
	}
	return false;
}

//Guarda toda a informação relativa aos autocarros
void store_info_Bus(Company &SR, vector<Line> line_info)
{
	for (int i = 0; i < line_info.size(); i++)
	{
		double tempoTotal = 0;
		
		unsigned int lineID;
		vector<Bus> NeededBus;


		lineID = line_info.at(i).getId();

		//Tempo que o autocarro demora a percorrer (ida) toda a linha
		for (int j = 0; j < line_info.at(i).getTimings().size(); j++)
		{
			tempoTotal += line_info.at(i).getTimings().at(j);
		}
		
		tempoTotal += tempoTotal;  //Tempo de ida e volta de um autocarro
		unsigned int const Time = tempoTotal;
		tempoTotal = tempoTotal / line_info.at(i).getFreq_circ();

		//TempoTotal passa a ser equivalente ao numero de autocarros necessários
		if (tempoTotal > int(tempoTotal))
		{
			tempoTotal = int(tempoTotal);
			tempoTotal++;
		}

		//Para cada linha, cria o numero de autocarros necessario, e os respetivos turnos
		for (int z = 1; z <= tempoTotal; z++)
		{
			Bus autocarro(z, lineID);
			vector<Shift> turnos;

			unsigned int start_time_day, start_time_copy, end_time_copy;

			start_time_copy = start_time;
			end_time_copy = end_time;

			//Cria os turnos para os autocarro semanalmente
			if (z == 1)
			{
				while (start_time_copy <= end_time_copy)
				{

					if (((start_time_copy >= 480) && (start_time_copy <= 1380)) || ((start_time_copy >= 1920) && (start_time_copy <= 2820)) || ((start_time_copy >= 3360) && (start_time_copy <= 4260)) || ((start_time_copy >= 4800) && (start_time_copy <= 5700)) || ((start_time_copy >= 6240) && (start_time_copy <= 7140)))
					{
						unsigned int temp;
						temp = start_time_copy + Time;

						turnos.push_back(Shift(lineID, z, start_time_copy, temp));

						start_time_copy = temp + (((tempoTotal*line_info.at(i).getFreq_circ()) + start_time_copy) - temp);
					}
					else
						start_time_copy++;
				}
			}
			else
			{
				start_time_copy = start_time_copy + ((z - 1)*line_info.at(i).getFreq_circ());
				start_time_day = start_time_copy;

				while (start_time_copy <= end_time_copy)
				{
					if (((start_time_copy >= 480) && (start_time_copy <= 1380)) || ((start_time_copy >= 1920) && (start_time_copy <= 2820)) || ((start_time_copy >= 3360) && (start_time_copy <= 4260)) || ((start_time_copy >= 4800) && (start_time_copy <= 5700)) || ((start_time_copy >= 6240) && (start_time_copy <= 7140)))
					{
						unsigned int temp;
						temp = start_time_copy + Time;

						turnos.push_back(Shift(lineID, z, start_time_copy, temp));

						start_time_copy = temp + (((tempoTotal*line_info.at(i).getFreq_circ()) + start_time_copy) - temp);
					}
					else
					{
						start_time_copy = start_time_day + 1440;
						start_time_day = start_time_copy;
					}
				}
			}

			autocarro.setSchedule(turnos);

 			NeededBus.push_back(autocarro);
		}

		SR.addLineBusData(lineID, NeededBus);
	}
}