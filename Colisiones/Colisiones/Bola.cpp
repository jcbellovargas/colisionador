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

void Bola::SetPosicion(Vector2 *pos)
{
	this->posicion = pos;
}

void Bola::SetVelocidad(Vector2 *vel)
{
	this->velocidad = vel;
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
	filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio(), 0xFF000000);

	return filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio()*0.97, 0xFF0000FF);
}