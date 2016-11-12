#pragma once
class Timer
{
public:
	Timer();
	void Empezar();
	void Detener();
	void Pausar();
	void Despausar();
	unsigned int GetTicks();

	bool Andando();
	bool Pausado();

private:
	unsigned int ticks;
	unsigned int ticksPausado;

	bool andando;
	bool pausado;
};