#include "Bola.h"
#include "Vector2.h"

Bola::Bola(int x, int y, int r, int vx, int vy, Uint32 color)
{
	this->posicion = new Vector2(x, y);
	this->radio = r;
	this->masa = r;
	this->velocidad = new Vector2(vx, vy);
	this->color = color;
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

Uint32 Bola::GetColor()
{
	return this->color;
}

void Bola::SetColor(Uint32 color)
{
	this->color = color;
}

int Bola::GetMasa()
{
	return this->masa;
}

int Bola::Renderizar(SDL_Renderer* renderer)
{
	filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio(), 0xFF000000);

	return filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio()*0.97, this->GetColor());
}