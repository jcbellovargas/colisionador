
#pragma once
#include "Vector2.h"
#include "Bola.h"
//Clase "Estatica" para detectar y calcular colisiones
class Fisica
{
public:
	static bool DetectarColision(Bola bola1, Bola bola2);
	static void CalcularColision(Bola* bola1, Bola* bola2);
	static Vector2 PuntoCercanoEnLinea( Vector2 posicion,  Vector2 velocidad,  Vector2 punto);

private:
	Fisica();
};