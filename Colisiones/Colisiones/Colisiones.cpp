
#include <SDL.h>
#include <stdio.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
using namespace std;

//Screen dimension constants
const int ANCHO_PANTALLA = 640;
const int ALTURA_PANTALLA = 480;
SDL_Window* window;
SDL_Renderer* renderer;
void init();
int renderBola();
int renderBola(int x, int y, int r);
void close();

int main(int argc, char* args[])
{
	init();
	bool salir = false;
	SDL_Event evento;
	while (!salir)
	{
		//renderCirculo(0, 0, 33);
		while (SDL_PollEvent(&evento) != 0)
		{
			if (evento.type == SDL_QUIT)
			{
				salir = true;
			}
			else if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_SPACE)
			{
				renderBola();
			}
		}
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
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
		}
	}

}

int renderBola()
{
	int r = rand() % (25 + 1);
	// hay que tener en cuenta el radio para los limites de posibles valores de x e y
	// random entre min y max ==> rand()%(max-min + 1) + min 
	int x = rand() % (ANCHO_PANTALLA - 2*r + 1) + r;
	int y = rand() % (ALTURA_PANTALLA - 2*r + 1) + r;

	int result = filledCircleColor(renderer, x, y, r, 0xFF0000FF);
	if (result != 0)
	{
		cout << "SDL no pudo dibujar la bola. SDL_Error: " << SDL_GetError() << endl;
	}
	SDL_RenderPresent(renderer);
	return result;
}

int renderBola(int x, int y, int r)
{
	//int r = rand() % (25 + 1);
	//int x = rand() % (ANCHO_PANTALLA + 1 - r);
	//int y = rand() % (ALTURA_PANTALLA + 1 - r);

	int result = filledCircleColor(renderer, x, y, r, 0xFF0000FF);
	if (result != 0)
	{
		cout << "SDL no pudo dibujar la bola. SDL_Error: " << SDL_GetError() << endl;
	}
	SDL_RenderPresent(renderer);
	return result;
}

void close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}