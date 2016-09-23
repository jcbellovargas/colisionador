#include "Bola.h"
#include "Vector2.h"

Bola::Bola(int x, int y, int r)
{

	Vector2* pos = new Vector2(x,y);
	this->posicion = pos;
	this->radio = r;
}

Bola::~Bola()
{
}

int Bola::GetRadio()
{
	return this->radio;
}

int Bola::Renderizar(SDL_Renderer* renderer)
{
	return filledCircleColor(renderer, this->posicion->GetX(), this->posicion->GetY(), this->GetRadio(), 0xFF0000FF);
}