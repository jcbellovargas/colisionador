#pragma once
#include <fstream>
#include <iostream>
class Archivo
{
public:
	Archivo();
	~Archivo();
	void AbrirArchivo();
	void EscribirArchivo(std::string);
	std::ofstream salida;
};

