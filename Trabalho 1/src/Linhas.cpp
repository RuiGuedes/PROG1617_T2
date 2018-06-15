#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "MyTypes.h"
#include<stdio.h> 


using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Declaração de Prótotipos relativos às opções possiveis referentes ás linhas
void cria_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void remove_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void gestao_linhas(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
bool valid_number(string number);
bool exist_ID_linha(vector<Line> lines_info,const int ID);
void write_data_line(vector<Line> &lines_info, string const file_name_lines);
void modifica_linha_ID(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_linha_freq_circ(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_linha_add(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
void modifica_linha_del(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);
bool exist_stop_variavel(vector<string> variavel_stops, const string stop);
bool exist_stop_linha(vector<Line> lines_info, const int ID, const string stop);
void Main_Interface(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Cria uma nova linha  
void cria_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int ID, freq_circ, check, time;
	string temp;
	char value[10];
	Line variavel;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Identificador unico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}
		
		ID = atoi(value);

		if (exist_ID_linha(lines_info, ID))
			cout << "Este identificador único já se encontra utilizado." << endl << "Tente novamente." << endl << endl;
	
	}
	while(exist_ID_linha(lines_info,ID)); //Verifica se o ID é possivel

	variavel.ID = ID;

	system("CLS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	cout << "Frequência de circulação" << endl << endl;

	cout << "Frequência de circulação (minutos): ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
	{
		cin.clear();
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Frequência de circulação (minutos): ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	freq_circ = atoi(value);

	variavel.freq_circ = freq_circ;

	system("CLS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	cout << "Lista de paragens" << endl << endl;

	cout << "Lista de paragens: " << endl << "Numero de paragens: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
	{
		cin.clear();
		cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
		cout << "Numero de paragens: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}
	check = atoi(value);
	
	cin.clear();
	cin.ignore(1000, '\n');
	
	for (int i = 1; i <= check; i++)
	{
		cout << i << "ª Paragem: ";
		getline(cin, temp);
		if (i == 1)
		{
			variavel.stops.push_back(temp);
		}
		else if (exist_stop_variavel(variavel.stops, temp) == false)
		{
			variavel.stops.push_back(temp);
		}
		else
		{
			i--;
			cout << "Paragem já existente." << endl << "Tente Novamente." << endl << endl;
		}
	}

	system("CLS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	cout << "Tempos entre as respetivas paragens" << endl << endl;

	cout << "Tempos entre as respetivas paragens: " << endl;

	for (int i = 1; (i+1) <= check; i++)
	{
		cout << "Tempo entre a " << i << " paragem e a " << i + 1 << " paragem: ";
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Dados inválidos." << endl << "Tente novamente." << endl << endl;
			cout << "Tempo entre a " << i << " paragem e a " << i + 1 << " paragem: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
			
		}

		time = atoi(value);
		cin.ignore(1000, '\n');
		variavel.time_stops.push_back(time);

	}

	//Escreve a linha no ficheiro

	lines_info.push_back(variavel);

	write_data_line(lines_info, file_name_lines);

	cout << "Linha criada com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica uma linha ja existente 
void modifica_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int option;
	char value[10];

	cout << "Modificar uma linha." << endl << endl;

	cout << "Funcionalidades disponiveis" << endl << endl;
	cout << "1 - Modificar identificar unico" << endl;
	cout << "2 - Modificar tempo de circulação" << endl;
	cout << "3 - Adicionar uma paragem" << endl;
	cout << "4 - Remover uma paragem" << endl;
	cout << "5 - Voltar" << endl;
	cout << endl << "Introduza uma opcao (1-5): ";
	
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	//Verifica se existe erro na introdução da opção.
	while ((valid_number(value) == false) || (atoi(value) < 1) || (atoi(value) > 5))
	{
		cin.clear();
		cout << "Opcao invalida ! Tente novamente. " << endl;
		cout << "Introduza uma opcao (1-5): ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	option = atoi(value);

	//Variantes para as diferentes opções tomadas pelo utilizador
	switch (option)
	{
	case 1:
		system("CLS");
		modifica_linha_ID(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 2:
		system("CLS");
		modifica_linha_freq_circ(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 3:
		system("CLS");
		modifica_linha_add(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 4:
		system("CLS");
		modifica_linha_del(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	case 5:
		gestao_linhas(lines_info, file_name_lines, drivers_info, file_name_drivers);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Remova uma linha já existente  
void remove_linha(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	int ID;
	char value[10];

	//Condicões necessarias para que seja possivel remover uma linha

	do
	{
		cout << "Identificador unico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Esse identificador não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel
	
	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			lines_info.erase(lines_info.begin()+ i);
		}
	}

	//Atualiza conteudo do ficheiro

	write_data_line(lines_info, file_name_lines);

	cout << "Linha Removida com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se o identificador unico já se encontra ocupado.
//Devolve TRUE quando já está ocupado
//Devolve FALSE quando não está ocupado 
bool exist_ID_linha(vector<Line> lines_info, const int ID)
{
	vector<int> id_off;

	for (int i = 0; i < lines_info.size(); i++)
	{
		id_off.push_back(lines_info.at(i).ID);
	}

	for (int i = 0; i < id_off.size(); i++)
	{
		if (ID == id_off.at(i))
		{
			return true;
		}
	}

	return false;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Atualiza o ficheiro, escrevendo o conteudo necessário 
void write_data_line(vector<Line> &lines_info, string const file_name_lines)
{
	ofstream output_file;

	output_file.open(file_name_lines);

	for (int i = 0; i < lines_info.size(); i++)
	{
		output_file << lines_info.at(i).ID << " ; " << lines_info.at(i).freq_circ << " ; ";

		for (int j = 0; j < (lines_info.at(i).stops.size() - 1) ; j++)
		{
			output_file << lines_info.at(i).stops.at(j) << ", ";
		}
		output_file << lines_info.at(i).stops.at(lines_info.at(i).stops.size() - 1) << "; ";

		for (int z = 0; z < (lines_info.at(i).time_stops.size() - 1); z++)
		{
			output_file << lines_info.at(i).time_stops.at(z) << ", ";
		}
		output_file << lines_info.at(i).time_stops.at(lines_info.at(i).time_stops.size() - 1) << endl;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica o ID da linha 
void modifica_linha_ID(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Modificar identificar unico" << endl << endl;

	int ID, new_ID;
	char value[10];

	do
	{
		cout << "Identificador unico da linha a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha a modificar: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel e se existe


	do
	{
		cout << "Digite o novo identificador unico: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da nova linha: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		new_ID = atoi(value);

		if (exist_ID_linha(lines_info, new_ID))
			cout << "Este identificador único já existe." << endl << "Tente novamente." << endl << endl;
		else
			break;

	} while (exist_ID_linha(lines_info, ID));

	//Altera os valores de ID
	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			lines_info.at(i).ID = new_ID;
		}
	}

	write_data_line(lines_info, file_name_lines);

	cout << "Identificador único alterado com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Modifica a frequencia de circulação da linha 
void modifica_linha_freq_circ(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Modificar frequência de circulação" << endl << endl;

	int ID, new_freq;
	char value[10];

	do
	{
		cout << "Identificador unico da linha a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha a modificar: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;

	} 
	while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel e se existe

	cout << "Digite a nova frequência de circulação: ";
	cin.ignore(1000, '\n');
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
	{
		cin.clear();
		cout << "Frequência de circulação inválida." << endl << "Tente novamente." << endl << endl;
		cout << "Nova frequência de circulação: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	new_freq = atoi(value);

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			lines_info.at(i).freq_circ = new_freq;
		}
	}

	write_data_line(lines_info, file_name_lines);

	cout << "Frequência de circulação alterada com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Adiciona uma paragem à linha 
void modifica_linha_add(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Adicionar uma paragem" << endl << endl;

	int ID, new_time;
	char value[10];
	string new_stop;

	do
	{
		cout << "Identificador unico da linha a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha a modificar: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel e se existe

	cin.ignore(1000, '\n');

	do
	{
		cout << "Digite o nome da nova paragem: ";
		getline(cin,new_stop);

		if (exist_stop_linha(lines_info, ID, new_stop) == true)
		{
			cout << "Paragem já existente." << endl << "Tente novamente." << endl << endl;
		}

	} while (exist_stop_linha(lines_info, ID, new_stop) == true);

	cout << "Digite o tempo entre a última e a nova paragem: ";
	cin.get(value, 10);

	while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
	{
		cin.clear();
		cout << "Tempo inválido." << endl << "Tente novamente." << endl << endl;
		cout << "Tempo entre a última e a nova paragem: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
	}

	new_time = atoi(value);

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).ID == ID)
		{
			lines_info.at(i).stops.push_back(new_stop); 
			lines_info.at(i).time_stops.push_back(new_time);
		}
	}

	write_data_line(lines_info, file_name_lines);

	cout << "Paragem adicionada com sucesso." << endl << endl;

	system("pause");
	system("CLS");
	Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Remove uma paragem à linha 
void modifica_linha_del(vector<Line> &lines_info, string const file_name_lines, vector<Driver> &drivers_info, string const file_name_drivers)
{
	cout << "Remover uma paragem" << endl << endl;

	int ID, indicator_1, indicator_2;
	string stop;
	char value[10];
	bool state = false;

	indicator_1 = -1;
	indicator_2 = -1;

	do
	{
		cout << "Identificador unico da linha a modificar: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da linha a modificar: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_linha(lines_info, ID)); //Verifica se o ID é possivel e se existe


	cout << "Paragem a remover: ";
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


//Verifica em que local se encontra a paragem
//indicator_1 => corresponde à posicao em lines_info
//indicator_2 => corresponde à posicao em lines_info.stops
		for (int i = 0; i < lines_info.size(); i++)
		{
			for (int z = 0; z < lines_info.at(i).stops.size(); z++)
			{
				if (lines_info.at(i).stops.at(z) == stop)
				{
					indicator_1 = i;
					indicator_2 = z;
					break;
				}
			}

			if ((indicator_1 != -1) || (indicator_2 != -1))
			{
				break;
			}
		}

		if (indicator_2 == 0)
		{
			lines_info.at(indicator_1).stops.erase(lines_info.at(indicator_1).stops.begin() + 0);
			lines_info.at(indicator_1).time_stops.erase(lines_info.at(indicator_1).time_stops.begin());

		}
		else if (indicator_2 == ((lines_info.at(indicator_1).stops.size()) - 1))
		{
			lines_info.at(indicator_1).stops.erase(lines_info.at(indicator_1).stops.begin() + ((lines_info.at(indicator_1).stops.size()) - 1));
			lines_info.at(indicator_1).time_stops.erase(lines_info.at(indicator_1).time_stops.begin() + ((lines_info.at(indicator_1).time_stops.size()) - 1));
		}
		else
		{
			lines_info.at(indicator_1).time_stops.at(indicator_2) = lines_info.at(indicator_1).time_stops.at(indicator_2) + lines_info.at(indicator_1).time_stops.at(indicator_2 - 1);
			lines_info.at(indicator_1).stops.erase(lines_info.at(indicator_1).stops.begin() + indicator_2);
			lines_info.at(indicator_1).time_stops.erase(lines_info.at(indicator_1).time_stops.begin() + (indicator_2 - 1));
		}

		write_data_line(lines_info, file_name_lines);

		cout << "Paragem removida com sucesso." << endl << endl;

		system("pause");
		system("CLS");
		Main_Interface(lines_info, file_name_lines, drivers_info, file_name_drivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se existe a paragem 
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