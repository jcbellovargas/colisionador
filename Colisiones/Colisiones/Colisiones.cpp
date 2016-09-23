
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Bola.h"
#include <vector>
using namespace std;

const int ANCHO_PANTALLA = 640;
const int ALTURA_PANTALLA = 480;
SDL_Window* window;
SDL_Renderer* renderer;
vector<Bola*> bolas;

void init();
int renderBola();
int renderBola(int x, int y, int r);
void close();
void nuevaBola();
void actualizarPosiciones();
void renderizarTodo();
void refreshRenderer();

int main(int argc, char* args[])
{
	init();
	bool salir = false;
	SDL_Event evento;
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
			}
		}
		actualizarPosiciones();
		renderizarTodo();
	}
	close();
	
	return 0;
}



void init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
	int r = rand() % (25 + 1);
	// hay que tener en cuenta el radio para los limites de posibles valores de x e y
	// random entre min y max ==> rand()%(max-min + 1) + min 
	int x = rand() % (ANCHO_PANTALLA - 2 * r + 1) + r;
	int y = rand() % (ALTURA_PANTALLA - 2 * r + 1) + r;
	int vx = rand() % (5 - -5 + 1) + -5;
	int vy = rand() % (5 - -5 + 1) + -5;
	Bola* bola = new Bola(x, y, r, vx, vy);
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

