#include <iostream>
#include <windows.h>


using namespace std;

//Declara��o de pr�totipo da fun��o relativa � INTERFACE
void OpenFiles_Interface();

//Inicio do programa
int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	OpenFiles_Interface();
	
	return 0;
}