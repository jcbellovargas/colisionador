
#pragma once
#include "Renderizable.h"
#include "Vector2.h"
//El IRenderizable es para tipificar a todos los objetos que se pueden autorenderizar
class Bola : public Renderizable
{
public:
	Bola(int x, int y, int r, int vx, int vy);
	~Bola();

	//Define como se renderiza esta Bola
	int Renderizar(SDL_Renderer* renderer);
	int GetRadio();
	Vector2* GetPosicion();
	Vector2* GetVelocidad();
	void SetPosicion(Vector2 *pos);
	void SetVelocidad(Vector2 *vel);
private:
	Vector2* posicion;
	Vector2* velocidad;
	int radio;
};

