
#pragma once
#include "Vector2.h"
#include "Bola.h"
//Clase "Estatica" para detectar y calcular colisiones
class Fisica
{
public:
	static bool DetectarColisionBolas(Bola bola1, Bola bola2);
	static void CalcularColisionBolas(Bola* bola1, Bola* bola2);
	static Vector2 PuntoCercanoEnLinea( Vector2 posicion,  Vector2 velocidad,  Vector2 punto);
	static bool DetectarColisionPared(Bola bola, int alto, int ancho);
	static bool CalcularColisionPared(Bola* bola, int alto, int ancho);
private:
	Fisica();
};