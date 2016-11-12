#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
	ticks = 0;
	ticksPausado = 0;

	pausado = false;
	andando = false;
}

void Timer::Empezar()
{
	andando = true;
	pausado = false;

	ticks = SDL_GetTicks();
}

void Timer::Detener()
{
	pausado = true;
	andando = false;

	ticks = 0;
	ticksPausado = 0;
}

void Timer::Pausar()
{
	if (andando && !pausado)
	{
		pausado = true;

		ticksPausado = SDL_GetTicks() - ticks;

		ticks = 0;

		
	}


}


void Timer::Despausar()
{	
	if (andando && pausado)
	{
		pausado = false;

		ticks = SDL_GetTicks() - ticksPausado;

		ticksPausado = 0;
	}

}

unsigned int Timer::GetTicks()
{
	unsigned int tiempo = 0;

	if (andando)
	{
		if (pausado)
		{
			tiempo = ticksPausado;
		}
		else
		{
			tiempo = SDL_GetTicks() - ticks;
		}
	}

	return tiempo;
}

bool Timer::Andando()
{
	return andando;
}

bool Timer::Pausado()
{
	return pausado;
}

