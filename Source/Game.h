#pragma once
#include <SDL.h>
#include "Objeto.h"
#include "Nave.h"
#include "Stage.h"

class CGame
{
public:
	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_PRE_JUGANDO,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};

	bool Start();
	static CGame instanceGame;

	CGame();
	void Finalize();

private:
	void Menu();
	void Iniciando();
	void MoverEnemigo();
	bool EsLimitePantalla(Objeto * objeto,int bandera);

	int opcionSeleccionada;
	Uint8*keys;//Esta variable sirve para ver si determinadas teclas estan o no pulsadas
	SDL_Event event;//La variabe event es un tipo de evento de SDL para monitorizar el teclado
	SDL_Surface * screen;

	Nave * nave;
	//Nave *enemigo;
	Nave *enemigoArreglo[10];

	Stage nivel[4];
	void InicializandoStage();
	int nivelActual;

	Objeto*menu;//Fondo del menu
	Objeto*textos;//Textos deljuego
	Objeto*fondo;//Fondo del juego



	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	Estado estado;

	int Vida;
	int enemigosEliminados;

};