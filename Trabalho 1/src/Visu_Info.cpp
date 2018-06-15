#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "MyTypes.h"
#include<stdio.h> 
#include <iomanip>

int work_start_hour = 6;  //O trabalho começa as 6:00h da manha
int work_end_hour = 20;	//O trabalho termina as 20:00h da tarde
int work_start_min = 0;  //O trabalho começa as 6:00h da manha
int work_end_min = 0;	//O trabalho termina as 20:00h da tarde

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Declaração de Prótotipos relativos às opções possiveis referentes ás linhas
bool valid_number(string number);
bool exist_ID_linha(vector<Line> lines_info, const int ID);
void horarios(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void existe_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void stop_to_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void show_avai_all_drivers(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void horario_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
bool exist_stop_linha(vector<Line> lines_info, const int ID, const string stop);
void horario_line(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void write_time_stops(vector<Line> lines_info, int indicator, string stop);
void write_space(int tamanho,int number);
int number_chars(int number);
void visu_info(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void Main_Interface(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Mostra os condutores disponiveis  
void show_avai_all_drivers(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	for (int i = 0; i < drivers_info.size(); i++)
	{
		drivers_info.at(i).available = true;
	}

	cout << "Condutores disponiveis: " << endl << endl;

	for (int i = 0; i < drivers_info.size(); i++)
	{
		if (drivers_info.at(i).available == true)
		{
			cout << drivers_info.at(i).ID << " -- " << drivers_info.at(i).name << endl;
		}
	}

	cout << endl << "Condutores disponiveis mostrados com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

//Horarios Interface 
void horarios(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Horários" << endl << endl;

	int option;
	char value[10];

	cout << "Funcionalidades disponiveis" << endl << endl;
	cout << "1 - Horário de uma paragem" << endl;
	cout << "2 - Horário de uma linha" << endl;
	cout << "3 - Voltar" << endl;
	cout << endl << "Introduza uma opcao (1-3): ";        //Opção returnada pelo utilizador

	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 3))
	{
		cin.clear();
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-3): ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	option = atoi(value);

	//Variantes para as diferentes opções tomadas pelo utilizador
	switch (option)
	{
	case 1:
		system("CLS");
		horario_stop(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		horario_line(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		visu_info(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se existe a paragem  
void existe_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	vector<int> ID_stops;
	string stop;

	cout << "Verificar se existe uma paragem para uma dada linha" << endl << endl;

	cout << "Digite o nome da paragem a verificar: ";
	cin.ignore(1000, '\n');
	getline(cin, stop);

	for (int i = 0; i < lines_info.size(); i++)
	{
		for (int z = 0; z < lines_info.at(i).stops.size(); z++)
		{
			if (lines_info.at(i).stops.at(z) == stop)
			{
				ID_stops.push_back(lines_info.at(i).ID);
				break;
			}
		}
	}

	if (ID_stops.size() == 0)
	{
		cout << "Nenhuma linha contem a paragem mencionada" << endl;
	}
	else
	{
		cout << "As linhas que contêm a paragem mencionada são: " << endl << endl;

		for (int i = 0; i < ID_stops.size(); i++)
		{
			cout << "-> Linha " << ID_stops.at(i) << endl;
		}

		cout << endl;
		cin.ignore(1000, '\n');
	}

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Calcula o tempo e percurso de uma dada linha 
void stop_to_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{

	int ID, p_line, p_stop_1, p_stop_2, p_stop_1_copy, p_stop_2_copy;
	int time_between_stops = 0;
	string stop_1, stop_2;
	char value[10];

	cout << "Calcular o percurso e o tempo entre duas paragens para uma dada linha" << endl << endl;

	//Recebe o valor da linha para verificar a condição e verifica se é valida
	do
	{
		cout << "Identificador unico da linha pretendida: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha pretendida: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Esse identificador não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel

	cout << endl;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Recebe duas paragens validas e diferentes pertencentes à linha mencionaa
	cout << "Paragens: " << endl;

	cout << "1ª Paragem: ";
	cin.ignore(1000, '\n');
	getline(cin, stop_1);

	do
	{
		exist_stop_linha(lines_info, ID, stop_1);

		if (exist_stop_linha(lines_info, ID, stop_1) == true)
		{
			break;
		}
		else
		{
			cout << "Paragem inexistente." << endl << "Tente novamente." << endl << endl;
			cout << "1ª Paragem: ";
			getline(cin, stop_1);
		}

	} while (exist_stop_linha(lines_info, ID, stop_1) == false);

	cout << "2ª Paragem: ";
	getline(cin, stop_2);

	do
	{
		exist_stop_linha(lines_info, ID, stop_2);

		if (exist_stop_linha(lines_info, ID, stop_2) == true)
		{
			if (stop_1 != stop_2)
				break;
			else
			{
				cout << "Paragem igual à anterior." << endl << "Tente novamente." << endl << endl;
				cout << "2ª Paragem: ";
				getline(cin, stop_2);
			}	
		}
		else
		{
			cout << "Paragem inexistente." << endl << "Tente novamente." << endl << endl;
			cout << "2ª Paragem: ";
			getline(cin, stop_2);
		}
	} while ((exist_stop_linha(lines_info, ID, stop_2) == false) || (stop_1 == stop_2));

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Retorna em p_line a linha a verificar as paragens e tempo;
	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			p_line = i;
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Retorna os indicadores para as posicoes das paragens
	for (int i = 0; i < lines_info.at(p_line).stops.size(); i++)
	{
		if (lines_info.at(p_line).stops.at(i) == stop_1)
		{
			p_stop_1 = i;
		}
		else if (lines_info.at(p_line).stops.at(i) == stop_2)
		{
			p_stop_2 = i;
		}

	}

	p_stop_1_copy = p_stop_1;
	p_stop_2_copy = p_stop_2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Calcula o tempo entre as paragens
	if (p_stop_1 < p_stop_2)
	{
		if ((p_stop_2 - p_stop_1) == 1)
		{
			time_between_stops = lines_info.at(p_line).time_stops.at(p_stop_1);
		}
		else
		{
			for(p_stop_1; p_stop_1 < p_stop_2; p_stop_1++)
			{
				time_between_stops = time_between_stops + lines_info.at(p_line).time_stops.at(p_stop_1);
			}
		}
	}
	else
	{
		if ((p_stop_1 - p_stop_2) == 1)
		{
			time_between_stops = lines_info.at(p_line).time_stops.at(p_stop_2);
		}
		else
		{
			for (p_stop_2; p_stop_2 < p_stop_1; p_stop_2++)
			{
				time_between_stops = time_between_stops + lines_info.at(p_line).time_stops.at(p_stop_2);
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Percurso entre paragens: " << endl;

	if (p_stop_1_copy < p_stop_2_copy)
	{
		for (p_stop_1_copy; p_stop_1_copy < p_stop_2_copy; p_stop_1_copy++)
		{
			cout << lines_info.at(p_line).stops.at(p_stop_1_copy) << " -> ";
		}
		cout << lines_info.at(p_line).stops.at(p_stop_2_copy) << endl;
		cout << "Tempo do respetivo percurso: " << time_between_stops << endl << endl;
	}
	else
	{
		for (p_stop_2_copy; p_stop_2_copy < p_stop_1_copy; p_stop_2_copy++)
		{
			cout << lines_info.at(p_line).stops.at(p_stop_2_copy) << " -> ";
		}
		cout << lines_info.at(p_line).stops.at(p_stop_1_copy) << endl;
		cout << "Tempo do respetivo percurso: " << time_between_stops << endl << endl;
	}

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se a paragem existe na linha
//Devolve TRUE quando existe
//Devolve FALSE quando não existe  
bool exist_stop_linha(vector<Line> lines_info, const int ID, const string stop)
{
	int indicator;

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			indicator = i;
		}
	}

	for (int i = 0; i < lines_info.at(indicator).stops.size(); i++)
	{
		if (lines_info.at(indicator).stops.at(i) == stop)
		{
			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void horario_stop(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{

	cout << "Horário de uma paragem " << endl << endl;

	string stop;
	bool state = false;

	cout << "Nome da paragem da qual pretende visualizar o horário: ";
	cin.ignore(1000, '\n');
	getline(cin, stop);

	do
	{

		for (int i = 0; i < lines_info.size(); i++)
		{

			for (int z = 0; z < lines_info.at(i).stops.size(); z++)
			{

				if (lines_info.at(i).stops.at(z) == stop)
				{
					state = true;
					break;
				}

			}

			if (state == true)
			{
				break;
			}


		}

		if (state == false)
		{
			cout << "Paragem inexistente." << endl << "Tente novamente." << endl << endl;
			cout << "Paragem: ";
			getline(cin, stop);

		}

	} while (state == false);  //Verifica se a paragem existe

	cout << "Linha" << "           " << "Paragem" << "                  " << " Horas " << endl;

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (exist_stop_linha(lines_info, lines_info.at(i).ID, stop) == true)
		{
			int number;
			
			number = number_chars(lines_info.at(i).ID);

			cout << lines_info.at(i).ID;
			write_space(number, 16);
			cout << stop;
			write_space(stop.length()-1, 25);

			write_time_stops(lines_info, i, stop);

		}
	}

	cout << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void horario_line(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Horário de uma linha " << endl << endl;
	
	int ID, indicator;
	char value[10];

	do
	{
		cout << "Identificador unico da linha a verificar o horário: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha a verificar o horário: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID));

	cout << endl << "Linha: " << ID << endl;

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			indicator = i;
		}
	}

	cout << "Paragem" << "                  " << "Horas" << endl;

	for (int i = 0; i < lines_info.at(indicator).stops.size(); i++)
	{
		
		cout << lines_info.at(indicator).stops.at(i);
		write_space(lines_info.at(indicator).stops.at(i).length(), 25);
		write_time_stops(lines_info, indicator, lines_info.at(indicator).stops.at(i));

	}

	cout << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_time_stops(vector<Line> lines_info, int indicator, string stop)
{
	int freq_circ, time_after, limit, horas, min;
	int work_start_hour_copy, work_start_min_copy, work_end_hour_copy, work_end_min_copy;

	work_start_hour_copy = work_start_hour;
	work_start_min_copy = work_start_min;
	work_end_hour_copy = work_end_hour;
	work_end_min_copy = work_end_min;

	horas = work_start_hour;
	min = work_start_min;

	freq_circ = 0;
	time_after = 0;

	//Indicador da posicao da paragem
	for (int i = 0; i < lines_info.at(indicator).stops.size(); i++)
	{
		if (lines_info.at(indicator).stops.at(i) == stop)
		{
			limit = i;
		}
	}

	//Tempo até chegar à paragem
	for (int i = 0; i < limit; i++)
	{
		freq_circ = freq_circ + lines_info.at(indicator).time_stops.at(i);
	}

	work_start_min = work_start_min + freq_circ;

	//Escreve as horas da paragem
	while ((work_start_hour < work_end_hour) || ((work_start_min < work_end_min) && (work_start_hour = work_end_hour)))
	{
		double var_2;

		//Organiza a informação do horário para ser escrita

		if (work_start_min >= 60)
		{
			var_2 = work_start_min / 60.0;

			work_start_hour = work_start_hour + int(var_2);
			work_start_min = (60 * (var_2 - int(var_2)));

		}

		//Escreve a informação das horas
		if ((work_start_hour > work_end_hour) || ((work_start_min > work_end_min) && (work_start_hour == work_end_hour)))
		{
			break;
		}

		if (work_start_hour < 10)
		{
			if (work_start_min == 0)
			{
				cout << "0" << work_start_hour << ":" << work_start_min << "0" << "  --  ";
			}
			else if (work_start_min < 10)
			{
				cout << "0" << work_start_hour << ":0" << work_start_min << "  --  ";
			}
			else
			{
				cout << "0" << work_start_hour << ":" << work_start_min << "  --  ";
			}
		}
		else
		{
			if (work_start_min == 0)
			{
				cout << work_start_hour << ":" << work_start_min << "0" << "  --  ";
			}
			else if (work_start_min < 10)
			{
				cout << work_start_hour << ":0" << work_start_min << "  --  ";
			}
			else
			{
				cout << work_start_hour << ":" << work_start_min << "  --  ";
			}
		}

		work_start_min = work_start_min + lines_info.at(indicator).freq_circ;

	}

	cout << '\b' << '\b' << '\b' << '\b' << "    " << endl;

	work_start_hour = work_start_hour_copy;
	work_start_min = work_start_min_copy;
	work_end_hour = work_end_hour_copy;
	work_end_min = work_end_min_copy;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int number_chars(int number)
{
	int i = 0;
	
	do
	{
		i++;
		number = number / 10;
	} while (number != 0);

	return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_space(int tamanho, int number)
{
	number = number - tamanho;

	for (number; number > 0; number--)
	{
		cout << " ";
	}

}

