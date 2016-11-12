#pragma once
#include "Archivo.h"
#include <iostream>
#include "Timer.h"
class FPS
{
public:
	FPS();
	~FPS();
	Timer timer;
	Archivo archivo;
	unsigned int cuadrosTotal = 0;
	unsigned int cuadrosContados = 0;
	float cps = 0;
	void FinCuadro(int bolas);
	unsigned int deltaTime = 0;
};

