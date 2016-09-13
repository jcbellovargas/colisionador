
#pragma once
#include "IRenderizable.h"
//El IRenderizable es para tipificar a todos los objetos que se pueden autorenderizar
class Bola : IRenderizable
{
public:
	Bola();
	~Bola();

	//Define como se renderiza esta Bola
	void Renderizar();

private:
	Vector2 posicion;
};

