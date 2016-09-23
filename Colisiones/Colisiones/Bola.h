
#pragma once
#include "IRenderizable.h"
#include "Vector2.h"
//El IRenderizable es para tipificar a todos los objetos que se pueden autorenderizar
class Bola : IRenderizable
{
public:
	Bola(int x, int y, int r);
	~Bola();

	//Define como se renderiza esta Bola
	int Renderizar(SDL_Renderer* renderer);
	int GetRadio();
private:
	Vector2* posicion;
	int radio;
};

