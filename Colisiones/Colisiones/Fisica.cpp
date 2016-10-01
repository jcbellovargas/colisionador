
#include "Fisica.h"
#include <math.h>

//Devuelve true si las bolas se intersectan
bool Fisica::DetectarColisionBolas(Bola bola1, Bola bola2)
{
	Vector2 pos1 = *bola1.GetPosicion();
	Vector2 pos2 = *bola2.GetPosicion();
	Vector2 resultado = pos1 - pos2;
	float radios = bola1.GetRadio() + bola2.GetRadio();

	return resultado.MagnitudCuadrada() < radios * radios;
}

//Modifica las velocidades de las bolas correspondiendo a la collision que se produjo
//(no verifica collision)
void Fisica::CalcularColisionBolas(Bola* bola1, Bola* bola2)
{
	Vector2 velocidad1 = Vector2(0, 0);
	Vector2 velocidad2 = Vector2(0, 0);

	Vector2 puntoCol = PuntoCercanoEnLinea(*bola1->GetPosicion(), *bola1->GetVelocidad(), *bola2->GetPosicion());

	Vector2 puntoMedio = (*bola1->GetPosicion() + *bola2->GetPosicion()) / 2;
	



}

//Calcula el punto más cercano sobre una linea a otro punto. Necesario para calcular el lugar de collision
//de las bolas
Vector2 Fisica::PuntoCercanoEnLinea( Vector2 posicion,  Vector2 velocidad,  Vector2 punto)
{
	Vector2 lineaFin = posicion + velocidad;
	float a = lineaFin.GetY() - posicion.GetY();
	float b = posicion.GetX() - lineaFin.GetX();
	double c = a * posicion.GetX() + b * posicion.GetY();
	double d = -b * punto.GetX() + a * punto.GetY();
	double det = a * a - -b * -b;

	if (det != 0)
	{

		Vector2 resultado = Vector2(0, 0);

		resultado.SetX((float)((a * c - b * d) / det));
		resultado.SetY((float)((a * d - b * c) / det));

		return resultado;
	}
	else
	{
		return punto;
	}



}

//True si la pelota se fue de los bordes
//alto y ancho son de la pantalla
bool Fisica::DetectarColisionPared(Bola bola, int alto, int ancho)
{
	Vector2 pos = *bola.GetPosicion();
	int radio = bola.GetRadio();
	if (pos.GetX() < 0 + radio) return true;
	if (pos.GetY() < 0 + radio) return true;
	if (pos.GetX() > ancho - radio) return true;
	if (pos.GetY() > alto - radio) return true;

	return false;
}

// Modifica la velocidad de la bola para que se mantenga adentro del borde
// En teoría podríamos usar este para detectar colisiones ya que
// no modifica los valores a menos que haya una colision y usar
// el de arriba para crear bolas adentro de los limites?
bool Fisica::CalcularColisionPared(Bola *bola, int alto, int ancho)
{
	Vector2 pos = *bola->GetPosicion();
	Vector2 vel = *bola->GetVelocidad();
	int radio = bola->GetRadio();
	bool choque = false;
	if (pos.GetX() < 0 + radio)
	{
		choque = true;
		vel.SetX(abs(vel.GetX()));
	}
	if (pos.GetY() < 0 + radio)
	{
		choque = true;
		vel.SetY(-abs(vel.GetX()));
	}
	if (pos.GetX() > ancho - radio)	{
		choque = true;
		vel.SetX(-abs(vel.GetX()));
	}
	if (pos.GetY() > alto - radio)	{
		choque = true;
		vel.SetY(abs(vel.GetX()));
	}

	if (choque)
	{
		pos = pos + vel;
		bola->SetPosicion(pos);
		bola->SetVelocidad(vel);
		return true;
	}

	return false;
}



