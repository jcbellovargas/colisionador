#include <SDL2_gfxPrimitives.h>

//El IRenderizable es para tipificar a todos los objetos que se pueden autorenderizar
//Sirve en caso de que querramos renderizar otros tipos de objetos además de bolas
//Ya que agrupamos todos en una colección de IRenderizable y lo recorremos llamando Renderizar()
class IRenderizable
{
public:

	//Define como se debe renderizar el objeto
	virtual int Renderizar(SDL_Renderer* renderer) = 0;
};