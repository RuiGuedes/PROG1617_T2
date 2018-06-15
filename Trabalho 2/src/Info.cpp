#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Prototipos.h"

//Verifica se a paragem existe na linha
//Devolve TRUE quando existe
//Devolve FALSE quando não existe  
bool exist_stop_linha(vector<Line> lines_info, const int ID, const string stop)
{
	int indicator;
	vector<string> busStopList;

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (lines_info.at(i).getId() == ID)
		{
			indicator = i;
			break;
		}
	}

	busStopList = lines_info.at(indicator).getBusStops();

	for (int i = 0; i < busStopList.size(); i++)
	{
		if (busStopList.at(i) == stop)
		{
			return true;
		}
	}
	return false;
}

//Escreve o horario de uma paragem para as varias linhas a que pertence
void horario_stop(Company &SR)
{
	system("CLS");

	string stop;
	bool state = false;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<string> busStopList;

	cout << "Horário de uma paragem " << endl << endl;

	cout << "Nome da paragem da qual pretende visualizar o horário: ";
	cin.ignore(1000, '\n');
	getline(cin, stop);

	do
	{
		int i = 0;
		while (i < lines_info.size() && state != true)
		{
			busStopList = lines_info.at(i).getBusStops();
			for (int z = 0; z < busStopList.size(); z++)
			{
				if (busStopList.at(z) == stop)
				{
					state = true;
					break;
				}
			}
			i++;
		}
		if (state == false)
		{
			cout << "Paragem inexistente." << endl << "Tente novamente." << endl << endl;
			cout << "Paragem: ";
			getline(cin, stop);
		}
	} while (state == false);  //Verifica se a paragem existe

	cout << setw(12) << left << "Linha";
	cout << setw(30) << left << "Paragem";
	cout << "Horas" << endl;

	for (int i = 0; i < lines_info.size(); i++)
	{
		if (exist_stop_linha(lines_info, lines_info.at(i).getId(), stop) == true)
		{
			cout << setw(12);
			cout << left << lines_info.at(i).getId();
			cout << setw(30);
			cout << left << stop;
			write_time_stops(lines_info, i, stop);
			cout << endl;
		}
	}
	cout << endl;

	cout << "Press any key to continue . . .";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();
	system("CLS");
	return;
}

//Escreve horarios formatadamente
void write_time_stops(vector<Line> lines_info, const int indicator, const string stop)
{
	vector<string> busStopList = lines_info.at(indicator).getBusStops();
	vector<int> time_stops = lines_info.at(indicator).getTimings();
	vector<unsigned int> tempos;

	int freq_circ = lines_info.at(indicator).getFreq_circ(), tempoIdaVolta = 0;
	int limit, time_to_stop = 0, count = 0;
	unsigned int work_start, work_end;

	
	work_start = 480; //8:00H 
	work_end = 1380;  //23:00H

	//Indicador da posicao da paragem
	for (int i = 0; i < busStopList.size(); i++)
	{
		if (busStopList.at(i) == stop)
			limit = i;
	}

	//Tempo até chegar à paragem
	for (int i = 0; i < limit; i++)
		time_to_stop += time_stops.at(i);

	work_start += time_to_stop;

	for (int i = 0; i < time_stops.size(); i++)
		tempoIdaVolta += time_stops.at(i);

	tempoIdaVolta = tempoIdaVolta * 2;

	//Tempo de retorno à paragem
	tempoIdaVolta -= time_to_stop * 2;

	while (work_start < work_end) {
		tempos.push_back(work_start);
		work_start += freq_circ;
	}

	vector <unsigned int> tempos2;

	for (int i = 0; i < tempos.size(); i++)
		tempos2.push_back(tempos.at(i) + tempoIdaVolta);

	cout << busStopList.at(0) << " --> " << busStopList.at(busStopList.size() - 1) << endl;
	cout << setw(42) << " ";

	for (int i = 0; i < tempos.size(); i++)
	{
		unsigned int hh, min;
		min = tempos.at(i);
		hh = min / 60;
		min = min % 60;

		if (hh >= 24)
			hh = hh - 24;

		if (count >= 6) {
			cout << '\b' << '\b' << '\b' << '\b' << "      " << endl;
			cout << setw(42) << " ";
			count = 0;
		}
		if (hh < 10)
		{
			if (min < 10)
				cout << "0" << hh << ":0" << min << "  --  ";
			else
				cout << "0" << hh << ":" << min << "  --  ";
		}
		else
		{
			if (min < 10)
				cout << hh << ":0" << min << "  --  ";
			else
				cout << hh << ":" << min << "  --  ";
		}
		count++;
	}
	cout << '\b' << '\b' << '\b' << '\b' << "      " << endl << endl;

	count = 0;
	cout << setw(42) << " ";
	cout << busStopList.at(busStopList.size() - 1) << " --> " << busStopList.at(0) << endl;
	cout << setw(42) << " ";

	for (int i = 0; i < tempos2.size(); i++)
	{
		unsigned int hh, min;
		min = tempos2.at(i);
		hh = min / 60;
		min = min % 60;

		if (hh >= 24)
			hh = hh - 24;

		if (count >= 6) {
			cout << '\b' << '\b' << '\b' << '\b' << "      " << endl;
			cout << setw(42) << " ";
			count = 0;
		}
		if (hh < 10)
		{
			if (min < 10)
				cout << "0" << hh << ":0" << min << "  --  ";
			else
				cout << "0" << hh << ":" << min << "  --  ";
		}
		else
		{
			if (min < 10)
				cout << hh << ":0" << min << "  --  ";
			else
				cout << hh << ":" << min << "  --  ";
		}
		count++;
	}
	cout << '\b' << '\b' << '\b' << '\b' << "      " << endl;
}

//Apresenta as linhas que incluem uma determinada paragem 
void existe_stop(Company &SR)
{
	system("CLS");

	vector<int> ID_stops;
	string stop;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<string> busStopList;

	cout << "Verificar quais as linhas que incluem uma paragem" << endl << endl;

	cout << "Digite o nome da paragem a verificar: ";
	cin.ignore(1000, '\n');
	getline(cin, stop);

	for (int i = 0; i < lines_info.size(); i++)
	{
		busStopList = lines_info.at(i).getBusStops();

		for (int z = 0; z < busStopList.size(); z++)
		{
			if (busStopList.at(z) == stop)
			{
				ID_stops.push_back(lines_info.at(i).getId());
				break;
			}
		}
	}

	if (ID_stops.size() == 0)
	{
		cout << "Nenhuma linha contem a paragem mencionada" << endl;
	}
	else if (ID_stops.size() == 1)
		cout << endl << "A linha que contêm a paragem mencionada é: Linha" << ID_stops.at(0) << endl;
	else
	{
		cout << endl << "As linhas que contêm a paragem mencionada são: " << endl << endl;

		for (int i = 0; i < ID_stops.size(); i++)
		{
			cout << "-> Linha " << ID_stops.at(i) << endl;
		}
		cout << endl;

	}

	cout << "Press any key to continue . . .";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();
	system("CLS");
	return;
}

//Informação de uma linha e respetivo horário
void info_line(Company &SR)
{
	system("CLS");

	int ID, indicator;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<string> busStopList;

	cout << "Informação de uma linha e respetivo horário" << endl << endl;

	do
	{
		cout << "Identificador unico da linha a verificar o horário: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
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
		if (lines_info.at(i).getId() == ID)
			indicator = i;
	}
	cout << "Frequência: " << lines_info.at(indicator).getFreq_circ() << endl << endl;

	cout << setfill(' ') << setw(42);
	cout << left << "Paragem";
	cout << "Horas" << endl << endl;
	busStopList = lines_info.at(indicator).getBusStops();

	for (int i = 0; i < busStopList.size(); i++)
	{
		cout << setw(42);
		cout << left << busStopList.at(i);
		write_time_stops(lines_info, indicator, busStopList.at(i));
		cout << endl;
	}

	system("pause");
	system("CLS");
	return;
}

//Visualizar o percurso e o tempo entre duas paragens
void stop_to_stop(Company &SR)
{
	system("CLS");

	string stop_1, stop_2;
	char value[10];
	vector<Line> lines_info;
	multimap<unsigned int, vector<string>> Information;

	cout << "Visualizar o percurso e o tempo entre duas paragens" << endl << endl;

	//Recebe duas paragens validas e diferentes pertencentes à linha mencionada
	cout << "Paragens: " << endl;

	cout << "Partida: ";
	cin.ignore(1000, '\n');
	getline(cin, stop_1);

	//Recebe uma segunda paragem de destino, diferente da de partida
	do
	{
		cout << "Destino: ";
		getline(cin, stop_2);

		if (stop_2 == stop_1)
			cout << "Dados incoerentes. Tente novamente !" << endl;

	} while (stop_2 == stop_1);

	//Verifica se alguma das paragens introduzidas não existe.
	//Em caso afirmativo apresenta a mensagem e volta ao menu principal
	if ((existeStop(SR, stop_1) == false) || (existeStop(SR, stop_2) == false))
	{
		cout << "Não é possivel calcular o percurso entre as paragens mencionadas." << endl;
		cout << endl << "Press any key to continue . . .";
		cin.get(value, 1);
		cin.ignore(1000, '\n');
		cin.clear();
		system("CLS");
		return;       //Volta ao ecrã principal
	}

	for (int i = 0; i < SR.getVecLines().size(); i++)
	{

		//Se a paragem de partida existe na linha a verificar condicionada por i, verifica as possibilidades
		//Caso contrário verifica para a proxima linha
		if (exist_stop_linha(SR.getVecLines(), SR.getVecLines().at(i).getId(), stop_1) == true)
		{
			vector<Line> newAdjustedVector;
			unsigned int lineID = SR.getVecLines().at(i).getId();

			//Restringir o numero de linhas a serem verificadas
			//Apenas interessam aquelas que contêm a paragem final, e que agora se encontram em "newAdjustedVector"
			limitOptionsFinal(newAdjustedVector, SR, stop_2);


			//Restringir novamente o numero de linhas a serem verificadas
			//Apenas interessam aquelas que contêm a paragem final, e que contêm paragens em comum com a linha em questão
			limitOptionsCommon(newAdjustedVector, SR, i, stop_2, stop_1, SR.getVecLines().at(i).getId());

			//Inicia processo de separação de paragens
			for (int j = 0; j < newAdjustedVector.size(); j++)
			{
				//Se "newAdjustedVector" contem a própia linha
				if (lineID == newAdjustedVector.at(j).getId())
				{
					int TotalTime = 0, pointerStop_1, pointerStop_2;
					vector<string> VarStops;

					//Devolve indicadores para a posição da primeira e da ultima paragem 
					for (int z = 0; z < newAdjustedVector.at(j).getBusStops().size(); z++)
					{
						if (newAdjustedVector.at(j).getBusStops().at(z) == stop_1)
						{
							pointerStop_1 = z;
						}
						else if (newAdjustedVector.at(j).getBusStops().at(z) == stop_2)
						{
							pointerStop_2 = z;
						}
					}

					if (pointerStop_1 < pointerStop_2)
					{
						//Guarda o percurso no vetor VarStops no sentido inicio->fim
						for (int z = pointerStop_1; z <= pointerStop_2; z++)
						{
							VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(z));
						}

						//Guarda o tempo do percurso em TotalTime
						pointerStop_2--;
						for (int z = pointerStop_1; z <= pointerStop_2; z++)
						{
							TotalTime += newAdjustedVector.at(j).getTimings().at(z);
						}

						Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
					}
					else
					{
						//Guarda o percurso no vetor VarStops no sentido inicio->fim
						for (int z = pointerStop_1; z >= pointerStop_2; z--)
						{
							VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(z));
						}

						//Guarda o tempo do percurso em TotalTime
						pointerStop_1--;
						for (int z = pointerStop_1; z >= pointerStop_2; z--)
						{
							TotalTime += newAdjustedVector.at(j).getTimings().at(z);
						}

						Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
					}
				}
				//Assume e guarda as restantes possibilidades
				else
				{
					vector<string> CommonStops;

					//Encontra e guarda as paragens em comum
					findStoreStops(CommonStops, newAdjustedVector.at(j).getBusStops(), SR.getVecLines().at(i).getBusStops(), stop_2, stop_1);

					if (CommonStops.size() == 0)
					{
						break;
					}
					else
					{
						//Novas informaçoes
						for (int z = 0; z < CommonStops.size(); z++)
						{
							int pointerStop_1_MainLine, pointerStop_2_MainLine, pointerStop_1, pointerStop_2, TotalTime = 0;
							vector<string> VarStops;

							//Devolve indicadores para a posição da primeira e da ultima paragem (MAIN LINE)
							for (int y = 0; y < SR.getVecLines().at(i).getBusStops().size(); y++)
							{
								if (SR.getVecLines().at(i).getBusStops().at(y) == stop_1)
								{
									pointerStop_1_MainLine = y;
								}
								else if (SR.getVecLines().at(i).getBusStops().at(y) == CommonStops.at(z))
								{
									pointerStop_2_MainLine = y;
								}
							}

							//Devolve indicadores para a posição da primeira e da ultima paragem (LINE IN QUESTION)
							for (int y = 0; y < newAdjustedVector.at(j).getBusStops().size(); y++)
							{
								if (newAdjustedVector.at(j).getBusStops().at(y) == CommonStops.at(z))
								{
									pointerStop_1 = y;
								}
								else if (newAdjustedVector.at(j).getBusStops().at(y) == stop_2)
								{
									pointerStop_2 = y;
								}
							}


							if (pointerStop_1 < pointerStop_2)
							{
								pointerStop_1++;

								if (pointerStop_1_MainLine < pointerStop_2_MainLine)
								{
									//Guarda a informação do percurso
									for (int y = pointerStop_1_MainLine; y <= pointerStop_2_MainLine; y++)
									{
										VarStops.push_back(SR.getVecLines().at(i).getBusStops().at(y));
									}
									for (int y = pointerStop_1; y <= pointerStop_2; y++)
									{
										VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(y));
									}


									//Guarda o tempo total do percurso
									pointerStop_1--;
									pointerStop_2_MainLine--;
									pointerStop_2--;
									for (int y = pointerStop_1_MainLine; y <= pointerStop_2_MainLine; y++)
									{
										TotalTime += SR.getVecLines().at(i).getTimings().at(y);
									}
									for (int y = pointerStop_1; y <= pointerStop_2; y++)
									{
										TotalTime += newAdjustedVector.at(j).getTimings().at(y);
									}

									Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
								}
								else
								{
									//Guarda a informação do percurso
									for (int y = pointerStop_1_MainLine; y >= pointerStop_2_MainLine; y--)
									{
										VarStops.push_back(SR.getVecLines().at(i).getBusStops().at(y));
									}
									for (int y = pointerStop_1; y <= pointerStop_2; y++)
									{
										VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(y));
									}

									//Guarda o tempo total do percurso
									pointerStop_1--;
									pointerStop_1_MainLine--;
									pointerStop_2--;
									for (int y = pointerStop_1_MainLine; y >= pointerStop_2_MainLine; y--)
									{
										TotalTime += SR.getVecLines().at(i).getTimings().at(y);
									}
									for (int y = pointerStop_1; y <= pointerStop_2; y++)
									{
										TotalTime += newAdjustedVector.at(j).getTimings().at(y);
									}

									Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
								}
							}
							else
							{
								if (pointerStop_1_MainLine < pointerStop_2_MainLine)
								{
									pointerStop_1--;
									//Guarda a informação do percurso
									for (int y = pointerStop_1_MainLine; y <= pointerStop_2_MainLine; y++)
									{
										VarStops.push_back(SR.getVecLines().at(i).getBusStops().at(y));
									}
									for (int y = pointerStop_1; y >= pointerStop_2; y--)
									{
										VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(y));
									}

									//Guarda o tempo total do percurso
									pointerStop_2_MainLine--;
									for (int y = pointerStop_1_MainLine; y <= pointerStop_2_MainLine; y++)
									{
										TotalTime += SR.getVecLines().at(i).getTimings().at(y);
									}
									for (int y = pointerStop_1; y >= pointerStop_2; y--)
									{
										TotalTime += newAdjustedVector.at(j).getTimings().at(y);
									}

									Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
								}
								else
								{
									pointerStop_1--;
									//Guarda a informação do percurso
									for (int y = pointerStop_1_MainLine; y >= pointerStop_2_MainLine; y--)
									{
										VarStops.push_back(SR.getVecLines().at(i).getBusStops().at(y));
									}
									for (int y = pointerStop_1; y >= pointerStop_2; y--)
									{
										VarStops.push_back(newAdjustedVector.at(j).getBusStops().at(y));
									}

									//Guarda o tempo total do percurso
									pointerStop_1_MainLine--;
									for (int y = pointerStop_1_MainLine; y >= pointerStop_2_MainLine; y--)
									{
										TotalTime += SR.getVecLines().at(i).getTimings().at(y);
									}
									for (int y = pointerStop_1; y >= pointerStop_2; y--)
									{
										TotalTime += newAdjustedVector.at(j).getTimings().at(y);
									}

									Information.insert(pair<int, vector<string>>(TotalTime, VarStops));
								}
							}
						}
					}
				}
			}
		}
	}

	if (Information.size() != 0)
		writeInfoStops(Information, stop_1);
	else
		cout << "Não é possivel efetuar tal percurso tendo em conta as paragens existentes." << endl;

	cout << endl << "Press any key to continue . . .";
	cin.get(value, 1);
	cin.ignore(1000, '\n');
	cin.clear();
	system("CLS");
	return;
}

//Verifica se uma paragem existe em pelo menos uma linha
//True - Existe
//False - Não existe
bool existeStop(Company &SR, string paragem)
{
	for (int i = 0; i < SR.getVecLines().size(); i++)
	{
		for (int j = 0; j < SR.getVecLines().at(i).getBusStops().size(); j++)
		{
			if (paragem == SR.getVecLines().at(i).getBusStops().at(j))
				return true;
		}
	}
	return false;
}

//Restringir o numero de linhas a serem verificadas
//Apenas interessam aquelas que contêm a paragem final
void limitOptionsFinal(vector<Line> &newAdjustedVector, Company &SR, string paragem)
{
	for (int i = 0; i < SR.getVecLines().size(); i++)
	{
		for (int j = 0; j < SR.getVecLines().at(i).getBusStops().size(); j++)
		{
			//Encontra a paragem em questão
			if (paragem == SR.getVecLines().at(i).getBusStops().at(j))
			{
				newAdjustedVector.push_back(SR.getVecLines().at(i));
				break;
			}
		}
	}
}

//Restringir novamente o numero de linhas a serem verificadas
//Apenas interessam aquelas que contêm a paragem final, e que contêm paragens em comum com a linha em questão
void limitOptionsCommon(vector<Line> &newAdjustedVector, Company &SR, unsigned int indicator, string paragem1, string paragem2, unsigned int ID)
{
	vector<Line> newData;
	vector<string> VarStops;
	int pointer;

	//Cria vetor com as paragens que interessam apenas
	for (int i = 0; i < SR.getVecLines().at(indicator).getBusStops().size(); i++)
	{
		if ((SR.getVecLines().at(indicator).getBusStops().at(i) != paragem1) && (SR.getVecLines().at(indicator).getBusStops().at(i) != paragem2))
			VarStops.push_back(SR.getVecLines().at(indicator).getBusStops().at(i));
	}


	if (VarStops.size() != 0)
	{
		for (int j = 0; j < newAdjustedVector.size(); j++)
		{

			if (newAdjustedVector.at(j).getId() == ID)
			{
				newData.push_back(newAdjustedVector.at(j));
			}
			else
			{
				for (int z = 0; z < newAdjustedVector.at(j).getBusStops().size(); z++)
				{
					if (existeStopOnLine(newAdjustedVector.at(j).getBusStops().at(z), VarStops, paragem1, paragem2) == true)
					{
						newData.push_back(newAdjustedVector.at(j));
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < newAdjustedVector.size(); j++)
		{

			if (newAdjustedVector.at(j).getId() == ID)
			{
				newData.push_back(newAdjustedVector.at(j));
			}
		}
	}

	newAdjustedVector = newData;
}

//Verificar se existe a paragem ou não na linha em questão
//True - Existe
//False - Não existe
bool existeStopOnLine(string paragem, vector<string> busStops, string condition1, string condition2)
{
	for (int i = 0; i < busStops.size(); i++)
	{
		if (paragem == busStops.at(i) && (paragem != condition1) && (paragem != condition2))
			return true;
	}
	return false;
}

//Encontra e guarda as paragens em comum
void findStoreStops(vector<string> &CommonStops, vector<string> newAdjustedVector, vector<string> MainLine, string paragem1, string paragem2)
{
	for (int i = 0; i < newAdjustedVector.size(); i++)
	{
		for (int z = 0; z < MainLine.size(); z++)
		{
			if ((newAdjustedVector.at(i) == MainLine.at(z)) && (newAdjustedVector.at(i) != paragem1) && (newAdjustedVector.at(i) != paragem2))
			{
				CommonStops.push_back(newAdjustedVector.at(i));
				break;
			}
		}
	}
}

//Escreve as possibilidades relativas ao percurso das paragens com o respetivo tempo
void writeInfoStops(multimap<unsigned int, vector<string>> &Information, string paragem)
{
	cout << setfill(' ') << setw(15);
	cout << left << "Tempo";
	cout << "Percurso" << endl;

	for (multimap<unsigned int, vector<string>>::const_iterator MultiMapIterator = Information.begin(); MultiMapIterator != Information.end(); MultiMapIterator++)
	{
		vector<string> VarStops;
		VarStops = MultiMapIterator->second;

		if ((paragem == VarStops.at(0)) && (RepeatInfo(VarStops) == false))
		{
			cout << setw(15);
			cout << left << MultiMapIterator->first;

			for (int i = 0; i < VarStops.size(); i++)
			{
				cout << VarStops.at(i) << " --> ";
			}
			cout << "\b" << "\b" << "\b" << "\b" << "     " << endl;
		}
	}
}

//Verifica se existem paragens repetidas no percurso
//True - repete
//False - não repete
bool RepeatInfo(vector<string> VarStops)
{
	for (int i = 0; i < VarStops.size(); i++)
	{
		for (int j = i + 1; j < VarStops.size(); j++)
		{
			if (VarStops.at(i) == VarStops.at(j))
			{
				return true;
			}
		}
	}

	return false;
}

//Trabalho atribuido a um condutor
void DriverWork(Company SR)
{
	system("CLS");

	int ID, indicator;
	char value[10];
	vector<Shift> workData;

	cout << "Trabalho atribuido a um condutor" << endl << endl;

	//Verifica se o ID é possivel
	do
	{
		cout << "Identificador unico da condutor: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();
		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cin.clear();
			cout << "Identificador unico inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador unico da condutor: ";
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_driver(SR.getVecDriver(), ID))
			cout << "Este identificador numérico único não existe ." << endl << "Tente novamente." << endl << endl;

	} while (!exist_ID_driver(SR.getVecDriver(), ID));

	//Devolve o apontador para a posição do condutor em questão
	for (int i = 0; i < SR.getVecDriver().size(); i++)
	{
		if (SR.getVecDriver().at(i).getId() == ID)
			indicator = i;
	}

	//WorkData contem a informação dos turnos do condutor
	workData = SR.getVecDriver().at(indicator).getShifts();

	if (workData.size() == 0)
		cout << "O condutor ainda não tem trabalho atribuido." << endl << endl;
	else
	{
		//Apresenta o trabalho atribuido ao condutor
		cout << "Nome do condutor: " << SR.getVecDriver().at(indicator).getName() << endl;
		cout << "Trabalho atribuido:" << endl;
		cout << setw(20) << left << "ID da Linha";
		cout << setw(25) << left << "Numero de ordem";
		cout << setw(25) << left << "Dia da semana";
		cout << "Horário (Inicio - Fim) " << endl;


		for (int i = 0; i < workData.size(); i++)
		{
			int startWork, endWork;
			unsigned int startWorkHour = 0, startWorkMin = 0, endWorkHour = 0, endWorkMin = 0;
			string dia;

			//Dado em minutos
			startWork = workData.at(i).getStartTime();
			endWork = workData.at(i).getEndTime();

			TimeConverter(startWork, endWork, startWorkHour, startWorkMin, endWorkHour, endWorkMin, dia);

			cout << setw(20);
			cout << left << workData.at(i).getBusLineId();
			cout << setw(25);
			cout << left << workData.at(i).getBusOrderNumber();
			cout << setw(25);
			cout << left << dia;
			TimeWriter(startWorkHour, startWorkMin, endWorkHour, endWorkMin);
			cout << '\b' << '\b' << "  " << endl;
		}

		cout << endl;
	}

	system("pause");
	system("CLS");
	return;
}

//Converte o horário em minutos para hh:mm
void TimeConverter(unsigned int inico_min, unsigned int fim_min, unsigned int &startWorkHour, unsigned int &startWorkMin, unsigned int &endWorkHour, unsigned int &endWorkMin, string &dia)
{
	//Dia da semana
	if ((inico_min >= 0) && (inico_min <= 1439))
		dia = "Segunda-Feira";
	else if ((inico_min >= 1440) && (inico_min <= 2879))
	{
		inico_min = inico_min - 1440;
		fim_min = fim_min - 1440;
		dia = "Terça-Feira";
	}
	else if ((inico_min >= 2880) && (inico_min <= 4319))
	{
		inico_min = inico_min - 2880;
		fim_min = fim_min - 2880;
		dia = "Quarta-Feira";
	}
	else if ((inico_min >= 4320) && (inico_min <= 5759))
	{
		inico_min = inico_min - 4320;
		fim_min = fim_min - 4320;
		dia = "Quinta-Feira";
	}
	else if ((inico_min >= 5760) && (inico_min <= 7199))
	{
		inico_min = inico_min - 5760;
		fim_min = fim_min - 5760;
		dia = "Sexta-Feira";
	}


	//Converte horário [INICIO]
	int hh, min;
	min = inico_min;
	hh = min / 60;

	startWorkHour = hh;
	startWorkMin = min % 60;

	//Converte horário [FIM]
	int HH, MIN;
	MIN = fim_min;
	HH = MIN / 60;

	endWorkHour = HH;
	endWorkMin = MIN % 60;

}

//Escreve o horário para o trabalho do condutor
void TimeWriter(unsigned int startWorkHour, unsigned int startWorkMin, unsigned int endWorkHour, unsigned int endWorkMin)
{
	if (endWorkHour >= 24)
		endWorkHour = endWorkHour - 24;

	if (startWorkHour < 10)
		cout << "0" << startWorkHour << ":";
	else
		cout << startWorkHour << ":";

	if (startWorkMin < 10)
		cout << "0" << startWorkMin << " - ";
	else
		cout << startWorkMin << " - ";

	if (endWorkHour < 10)
		cout << "0" << endWorkHour << ":";
	else
		cout << endWorkHour << ":";

	if (endWorkMin < 10)
		cout << "0" << endWorkMin << " - ";
	else
		cout << endWorkMin << " - ";
}

//Escreve horários pontuais
void TimeWriterBus(unsigned int WorkHour, unsigned int WorkMin)
{
	if (WorkHour >= 24)
		WorkHour = WorkHour - 24;

	if (WorkHour < 10)
		cout << "0" << WorkHour << ":";
	else
		cout << WorkHour << ":";

	if (WorkMin < 10)
		cout << "0" << WorkMin;
	else
		cout << WorkMin;
}

//Lista de todos os períodos de autocarros sem condutor atribuído
void BusWithoutDriver(Company &SR)
{
	system("CLS");

	cout << "Lista de todos os períodos de autocarros sem condutor atribuído" << endl << endl;

	int ID, num_ordem, max_ordem;
	char value[10];
	vector<Line> lines_info = SR.getVecLines();
	vector<Bus> bus;
	vector<Shift> turnos;

	//Verifica se o ID é possivel
	do
	{
		cout << "Identificador da linha a que pertence o autocarro: ";
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cout << "Identificador inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Identificador da linha a que pertence o autocarro: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		ID = atoi(value);

		if (!exist_ID_linha(lines_info, ID))
			cout << "Este identificador único não existe." << endl << "Tente novamente." << endl << endl;
	} while (!exist_ID_linha(lines_info, ID));

	//Verifica qual o numero de ordem maximo do autocarro
	multimap<unsigned int, vector<Bus>>::iterator p = SR.LineBusData.find(ID);
	for (auto p : SR.LineBusData)
	{
		if (p.first == ID) {
			bus = p.second;
			break;
		}
	}
	max_ordem = bus.size();

	//Verifica se o numero de ordem do autocarro é valido
	do
	{
		cout << "Número de ordem do autocarro (1-" << max_ordem << ") : ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin.get(value, 10);
		cin.clear();

		while (valid_number(value) == false || (atoi(value) > 32767) || (atoi(value) < -32767))
		{
			cout << "Número inválido." << endl << "Tente novamente." << endl << endl;
			cout << "Número de ordem do autocarro: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get(value, 10);
		}

		num_ordem = atoi(value);

		if (max_ordem < num_ordem || num_ordem <= 0)
			cout << "Este número de ordem não existe." << endl << "Tente novamente." << endl << endl;
	} while (max_ordem < num_ordem || num_ordem <= 0);

	//Guarda os turnos referentes ao autocarro em questão
	for (int i = 0; i < max_ordem; i++)
	{
		if (bus.at(i).getBusOrderInLine() == num_ordem)
		{
			turnos = bus.at(i).getSchedule();
			break;
		}
	}

	//Escreve os turnos sem condutor atribuido
	cout << "Turnos sem condutor atribuíduo" << endl << endl;
	for (int i = 0; i < turnos.size(); i++)
	{
		if (turnos.at(i).getAvailable())
		{
			int startWork = turnos.at(i).getStartTime(), endWork = turnos.at(i).getEndTime();
			unsigned int startWorkHour = 0, startWorkMin = 0, endWorkHour = 0, endWorkMin = 0;
			string dia;

			TimeConverter(startWork, endWork, startWorkHour, startWorkMin, endWorkHour, endWorkMin, dia);

			cout << setw(30); cout << left << "Identificador do condutor : "; cout << endl;
			cout << setw(30); cout << left << "Dia : "; cout << dia << endl;
			cout << setw(30); cout << left << "Hora de início : "; TimeWriterBus(startWorkHour, startWorkMin); cout << endl;
			cout << setw(30); cout << left << "Hora de fim : "; TimeWriterBus(endWorkHour, endWorkMin); cout << endl << endl;
		}
	}

	system("pause");
	system("CLS");
	return;
}

//Lista de todos os períodos de condutores sem o serviço completo atribuído.
void DriversAvailable(Company &SR)
{
	system("CLS");
	vector<Driver> condutores = SR.getVecDriver();

	cout << "Lista de todos os períodos de condutores sem o serviço completo atribuído" << endl << endl;

	cout << "Condutores disponiveis: " << endl << endl;

	for (int i = 0; i < condutores.size(); i++)
	{
		if (condutores.at(i).getspare())
		{
			cout << "Identificador = " << condutores.at(i).getId() << endl;
			cout << "Nome = " << condutores.at(i).getName() << endl;
			cout << "Minutos de trabalho restantes: " << (condutores.at(i).getMaxWeekWorkingTime() * 60) - condutores.at(i).getTotalTime() << endl << endl;
		}
	}

	system("pause");
	system("CLS");
	return;

}

//Verifica se respeita as horas minimas ou não
bool RestTime(vector<Shift> turnos_driver, unsigned int inicio_min, unsigned int fim_min, unsigned int descanso)
{
	unsigned int diferenca1 = 7200, diferenca2 = 7200, intervalo_tempo;

	for (int i = 0; i < turnos_driver.size(); i++)
	{
		if (turnos_driver.at(i).getEndTime() < inicio_min)
		{
			if ((inicio_min - turnos_driver.at(i).getEndTime()) < diferenca1)
			{
				diferenca1 = inicio_min - turnos_driver.at(i).getEndTime();
			}
		}
		else if (turnos_driver.at(i).getStartTime() > fim_min)
		{
			if ((turnos_driver.at(i).getStartTime() - fim_min) < diferenca2)
			{
				diferenca2 = turnos_driver.at(i).getStartTime() - fim_min;
			}
		}

	}

	if ((diferenca1 < descanso) || (diferenca2 < descanso))
		return false;
	else
		return true;
}

//Verifica se o condutor já está ocupaddo naquele periodo de tempo
bool is_occupied(vector<Shift> turnos_driver, Shift turno)
{
	unsigned int start_time, end_time, start = turno.getStartTime(), end = turno.getEndTime();

	for (int i = 0; i < turnos_driver.size(); i++)
	{
		start_time = turnos_driver.at(i).getStartTime();
		end_time = turnos_driver.at(i).getEndTime();

		if (start >= start_time && start <= end_time)
			return true;
		else if (end >= start_time && end <= end_time)
			return true;
	}
	return false;

}