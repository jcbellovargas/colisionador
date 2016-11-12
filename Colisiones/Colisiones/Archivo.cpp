#include "Archivo.h"
#include <iostream>
#include <fstream>
#include <string>

Archivo::Archivo()
{
}


Archivo::~Archivo()
{
}

void Archivo::AbrirArchivo()
{
	salida.open("FPS.txt", std::ios::out | std::ios::trunc);//Limpia el archivo
	salida.close();
}

void Archivo::EscribirArchivo(std::string texto)
{
	salida.open("FPS.txt", std::ios::out | std::ios::app); //ios::app == append
		salida << texto;
		salida.close();

}