
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Bola.h"
#include "Fisica.h"
#include <cmath>
#include <vector>
#include <time.h>
#include "FPS.h"

using namespace std;

const int ANCHO_PANTALLA = 800;
const int ALTURA_PANTALLA = 650;
Uint32 COLOR_VERDE = 0xff00ff00;
Uint32 COLOR_ROJO = 0xFF0000FF; 
SDL_Window* window;
SDL_Renderer* renderer;
vector<Bola*> bolas;
Archivo archivo;

void init();
//int renderBola();
//int renderBola(int x, int y, int r);
void close();
void inline nuevaBola();
void inline actualizarPosiciones();
void inline renderizarTodo();
void inline refreshRenderer();
void colisionesPared();
void inline colisionesBolas();

int main(int argc, char* args[])
{
	init();
	srand(time(NULL));
	bool salir = false;
	SDL_Event evento;
	int contadorBolas = 0;
	FPS fps;

	while (!salir)
	{
		while (SDL_PollEvent(&evento) != 0)
		{
			if (evento.type == SDL_QUIT)
			{
				salir = true;
			}
			else if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_SPACE)
			{
				nuevaBola();
				contadorBolas++;
			}
		}
		colisionesBolas();
		actualizarPosiciones();
		renderizarTodo();
		fps.FinCuadro(contadorBolas);
		
	}
	close();
	
	return 0;
}



void init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout << "SDL no pudo inicializar. SDL_Error: " << SDL_GetError() << endl;
		exit;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Colisionador", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTURA_PANTALLA, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "SDL no pudo crear la ventana. SDL_Error: " << SDL_GetError() << endl;
			exit;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			refreshRenderer();
		}
	}

}

void nuevaBola()
{
	int r = rand() % (25 - 15 + 1) + 15;
	// hay que tener en cuenta el radio para los limites de posibles valores de x e y
	// random entre min y max ==> rand()%(max-min + 1) + min 
	int x = rand() % (ANCHO_PANTALLA - 2 * r + 1) + r;
	int y = rand() % (ALTURA_PANTALLA - 2 * r + 1) + r;
	int vx = ((rand() % 5 - 1 + 1) + 1) * pow(-1, rand());
	int vy = ((rand() % 5 - 1 + 1) + 1) * pow(-1, rand());

	Bola* bola = new Bola(x, y, r, vx, vy, COLOR_ROJO);
	bolas.push_back(bola);
}

void actualizarPosiciones()
{
	for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
	{
		Bola* b = *it;
		int nuevoPosX = b->GetPosicion()->GetX() + b->GetVelocidad()->GetX();
		int nuevoPosY = b->GetPosicion()->GetY() + b->GetVelocidad()->GetY();
		b->GetPosicion()->SetX(nuevoPosX);
		b->GetPosicion()->SetY(nuevoPosY);
	}
}

void renderizarTodo()
{
	refreshRenderer();
	for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
	{
		Bola* bol = *it;
		if(bol->Renderizar(renderer) != 0)
		{
			cout << "SDL no pudo dibujar la bola. SDL_Error: " << SDL_GetError() << endl;
			exit;
		}
	}
	SDL_RenderPresent(renderer);
}

void refreshRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}
void close()
{
	for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
	{
		delete (*it);
	}
	bolas.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void colisionesPared()
{
	for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
	{
		Bola* b = *it;
		Fisica::CalcularColisionPared(b, ALTURA_PANTALLA, ANCHO_PANTALLA);
	}
}

void colisionesBolas()
{
	for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
	{
		Bola* bolaActual = *it;
		bolaActual->SetColor(COLOR_ROJO);
		Fisica::CalcularColisionPared(bolaActual, ALTURA_PANTALLA, ANCHO_PANTALLA);
		for (std::vector<Bola*>::iterator it = bolas.begin(); it != bolas.end(); ++it)
		{
			Bola* bola = *it;
			if (bolaActual != bola && Fisica::DetectarColisionBolas(bolaActual, bola))
			{
				if (bolaActual->GetColor() != COLOR_VERDE && bola->GetColor() != COLOR_VERDE)
				{
					bolaActual->SetColor(COLOR_VERDE);
					bola->SetColor(COLOR_VERDE);
					Fisica::CalcularColisionBolas(bolaActual, bola);
				}
			}
		}
	}

}
