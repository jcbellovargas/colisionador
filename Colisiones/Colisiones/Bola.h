
#pragma once
#include "Renderizable.h"
#include "Vector2.h"
//El IRenderizable es para tipificar a todos los objetos que se pueden autorenderizar
class Bola : public Renderizable
{
public:
	Bola(int x, int y, int r, int vx, int vy, Uint32 color);
	~Bola();

	//Define como se renderiza esta Bola
	int Renderizar(SDL_Renderer* renderer);
	int GetRadio();
	Vector2* GetPosicion();
	Vector2* GetVelocidad();
	void SetPosicion(Vector2 *pos);
	void SetVelocidad(Vector2 *vel);
	void SetColor(Uint32 color);
	int GetMasa();
	Uint32 GetColor();
private:
	Vector2* posicion;
	Vector2* velocidad;
	Uint32 color;
	int radio;
	int masa;
};

