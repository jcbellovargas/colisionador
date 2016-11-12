#include "FPS.h"
#include <string>


FPS::FPS()
{
	timer.Empezar();
	archivo.AbrirArchivo();
}


FPS::~FPS()
{
}

void FPS::FinCuadro(int bolasActuales)
{
	//Calculo fps
	cuadrosTotal++;
	if (timer.GetTicks() - deltaTime > 1000) //Pasó un segundo desde la ultima vez?
	{
        cps = (cuadrosTotal - cuadrosContados); //Cuadros totales - menos cuadros que ya conte = Cuadros que hizo en este segundo
		if (cps > 200)
		{
			cps = 200;//Si son más de 200 cps, limitarlo (llega hasta 8000)
		}
		deltaTime += 1000; //Pasó un segundo
		cuadrosContados = cuadrosTotal;//Todos los cuadros ya fueron contados

		archivo.EscribirArchivo(std::to_string(cps) + "," + std::to_string(bolasActuales) + ";"); //Escribe cps + la cantidad de bolas que había en ese segundo
	}




	
}
