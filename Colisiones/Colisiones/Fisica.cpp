
#include "Fisica.h"
#include <math.h>

//Devuelve true si las bolas se intersectan
//Las bolas se intersectan si la distancia entre sus centros es menor o igual a la suma de sus radios
bool Fisica::DetectarColisionBolas(Bola* bola1, Bola* bola2)
{
	//Vector2 pos1 = *bola1.GetPosicion();
	//Vector2 pos2 = *bola2.GetPosicion();
    //Vector2 resultado = pos1 - pos2;
	//float radios = bola1.GetRadio() + bola2.GetRadio();

	//return resultado.MagnitudCuadrada() < radios * radios;
	Vector2* p1 = bola1->GetPosicion();
	Vector2* p2 = bola2->GetPosicion();
	float distancia = DistanciaEntreDosPuntos(p1, p2);
	return distancia <= (bola1->GetRadio() + bola2->GetRadio());
}

float Fisica::DistanciaEntreDosPuntos(Vector2* p1, Vector2* p2)
{
	return sqrtf(pow(p2->GetX() - p1->GetX(), 2) + pow(p2->GetY() - p1->GetY(), 2));
}

//Modifica las velocidades de las bolas correspondiendo a la collision que se produjo
// 

void Fisica::CalcularColisionBolas(Bola* bola1, Bola* bola2)
{
	//Vector2 velocidad1 = Vector2(0, 0);
	//Vector2 velocidad2 = Vector2(0, 0);
	
	//Vector2 puntoCol = PuntoCercanoEnLinea(*bola1->GetPosicion(), *bola1->GetVelocidad(), *bola2->GetPosicion());

	//Vector2 puntoMedio = (*bola1->GetPosicion() + *bola2->GetPosicion()) / 2;

	SepararBolas(bola1, bola2);

	float distancia = DistanciaEntreDosPuntos(bola1->GetPosicion(), bola2->GetPosicion());

	// Necesitamos la norma del vector (n) que une a los dos centros(posiciones) de las bolas
	float nx = (bola2->GetPosicion()->GetX() - bola1->GetPosicion()->GetX()) / distancia;
	float ny = (bola2->GetPosicion()->GetY() - bola1->GetPosicion()->GetY()) / distancia;

	SepararBolas(bola1, bola2);
	double p = 2 * (bola1->GetVelocidad()->GetX() * nx + bola1->GetVelocidad()->GetY() * ny - bola2->GetVelocidad()->GetX() * nx - bola2->GetVelocidad()->GetY() * ny) /
		(bola1->GetMasa() + bola2->GetMasa());

	float vx1 = bola1->GetVelocidad()->GetX() - p * bola1->GetMasa() * nx;
	float vy1 = bola1->GetVelocidad()->GetY() - p * bola1->GetMasa() * ny;
	float vx2 = bola2->GetVelocidad()->GetX() + p * bola2->GetMasa() * nx;
	float vy2 = bola2->GetVelocidad()->GetY() + p * bola2->GetMasa() * ny;


	bola1->SetVelocidad(new Vector2(vx1, vy1));
	bola2->SetVelocidad(new Vector2(vx2, vy2));

}

// Una vez que se detecta la colision, se deben separar las bolas para que la colision se detecte solo una vez y haya un solo
// cambio de velocidades.
void Fisica::SepararBolas(Bola* bola1, Bola* bola2)
{
	// m es el punto medio entre los dos centros(posiciones) de las bolas

	float mx = (bola1->GetPosicion()->GetX() + bola2->GetPosicion()->GetX()) / 2;
	float my = (bola1->GetPosicion()->GetY() + bola2->GetPosicion()->GetY()) / 2;
	float distancia = DistanciaEntreDosPuntos(bola1->GetPosicion(), bola2->GetPosicion());

	float x1 = mx + bola1->GetRadio() * (bola1->GetPosicion()->GetX() - bola2->GetPosicion()->GetX()) / distancia;
	float y1 = my + bola1->GetRadio() * (bola1->GetPosicion()->GetY() - bola2->GetPosicion()->GetY()) / distancia;

	float x2 = mx + bola2->GetRadio() * (bola2->GetPosicion()->GetX() - bola1->GetPosicion()->GetX()) / distancia;
	float y2 = my + bola2->GetRadio() * (bola2->GetPosicion()->GetY() - bola1->GetPosicion()->GetY()) / distancia;
	
	bola1->SetPosicion(new Vector2(x1, y1));
	bola2->SetPosicion(new Vector2(x2, y2));

}

//Calcula el punto más cercano sobre una linea a otro punto. Necesario para calcular el lugar de collision
//de las bolas
Vector2 Fisica::PuntoCercanoEnLinea(Vector2 posicion, Vector2 velocidad, Vector2 punto)
{
	Vector2 lineaFin = posicion + velocidad;
	float a = lineaFin.GetY() - posicion.GetY();
	float b = posicion.GetX() - lineaFin.GetX();
	double c = a * posicion.GetX() + b * posicion.GetY();
	double d = -b * punto.GetX() + a * punto.GetY();
	double det = a * a - -b * -b;

	if (det != 0)
	{

		Vector2 resultado = Vector2(0, 0);

		resultado.SetX((float)((a * c - b * d) / det));
		resultado.SetY((float)((a * d - b * c) / det));

		return resultado;
	}
	else
	{
		return punto;
	}



}

//True si la pelota se fue de los bordes
//alto y ancho son de la pantalla
bool Fisica::DetectarColisionPared(Bola bola, int alto, int ancho)
{
	Vector2 pos = *bola.GetPosicion();
	int radio = bola.GetRadio();
	if (pos.GetX() < 0 + radio) return true;
	if (pos.GetY() < 0 + radio) return true;
	if (pos.GetX() > ancho - radio) return true;
	if (pos.GetY() > alto - radio) return true;

	return false;
}

// Modifica la velocidad de la bola para que se mantenga adentro del borde
// En teoría podríamos usar este para detectar colisiones ya que
// no modifica los valores a menos que haya una colision y usar
// el de arriba para crear bolas adentro de los limites?
void Fisica::CalcularColisionPared(Bola *bola, int alto, int ancho)
{
	Vector2 *pos = bola->GetPosicion();
	Vector2 *vel = bola->GetVelocidad();
	int radio = bola->GetRadio();
	if (pos->GetX() < 0 + radio)
	{
		vel->SetX(abs(vel->GetX()));
	}
	if (pos->GetY() < 0 + radio)
	{
		vel->SetY(abs(vel->GetY()));
	}
	if (pos->GetX() > ancho - radio)	
	{
		vel->SetX(-abs(vel->GetX()));
	}
	if (pos->GetY() > alto - radio)	{
		vel->SetY(-abs(vel->GetY()));
	}
}



