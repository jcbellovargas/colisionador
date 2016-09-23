#include "Bola.h"
#include "Vector2.h"

Bola::Bola(int x, int y, int r, int vx, int vy)
{
	this->posicion = new Vector2(x, y);
	this->radio = r;
	this->velocidad = new Vector2(vx, vy);
}

Bola::~Bola()
{
}

int Bola::GetRadio()
{
	return this->radio;
}

Vector2* Bola::GetVelocidad()
{
	return this->velocidad;
}

Vector2* Bola::GetPosicion()
{
	return this->posicion;
}

int Bola::Renderizar(SDL_Renderer* renderer)
{
	return filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio(), 0xFF0000FF);
}