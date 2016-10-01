#include <SDL2_gfxPrimitives.h>

//El Renderizable es para tipificar a todos los objetos que se pueden autorenderizar
//Sirve en caso de que querramos renderizar otros tipos de objetos además de bolas
//Ya que agrupamos todos en una colección de Renderizable y lo recorremos llamando Renderizar()
class Renderizable
{
public:

	//Define como se debe renderizar el objeto
	virtual int Renderizar(SDL_Renderer* renderer) = 0;
};