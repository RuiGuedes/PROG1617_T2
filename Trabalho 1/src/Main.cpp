#include <iostream>
#include <windows.h>
#include "MyTypes.h"

using namespace std;

//Declaração de prótotipo da função relativa à INTERFACE
void OpenFiles_Interface();

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	OpenFiles_Interface();

	return 0;
}