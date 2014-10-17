#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Header.h"
#include <SDL.h>
#include <SDL_image.h>

CGame::CGame(){
	estado=ESTADO_INICIANDO;///ACT3 MAL: Debes de indicar cual es tu estado inicial.
	//Iniciando();///ACT3 MAL: Este codigo no va aqui, para esto tienes el estado iniciando.
	//delete nave;
}


void CGame::Iniciando(){

	if (SDL_Init(SDL_INIT_VIDEO)<0)
	{
		printf("No se pudo iniciar SDL:Error %s\n",SDL_GetError());
		getchar();
		exit(EXIT_FAILURE);
	}

	screen= SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_SWSURFACE );
	if (screen==NULL)
	{
		printf("No se puede inicializar el modo grafico: \n", SDL_GetError());
		getchar();
		exit(1); 
	}
	SDL_WM_SetCaption( "Mi primer Juego", NULL );
	atexit(SDL_Quit);

	nave=new Nave(screen,"../Data/MiNave.bmp");

	//estado = ESTADO_INICIANDO;// ACT3: MAL Va en el constructor.
}
// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;

	while (salirJuego == false){

		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			Iniciando();//ACT3: Bien.
			estado= ESTADO_MENU;

			break;
		case Estado:: ESTADO_MENU:
			//nave->PintarModulo(0,0,0,64,64);
			//nave->PintarModulo(0,0,0);
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));//Limpia la imagen
			keys=SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				nave->Mover(1);
			}

			if (keys[SDLK_LEFT])
			{
				nave->Mover(-1);
			}
			nave->Pintar();
			break;
		case Estado::ESTADO_JUGANDO:
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO: //SALIR
			salirJuego = true;
			break;
		};
		while (SDL_PollEvent(&event))//Aqui SDL creara una lista de eventos ocurridos
		{
			if (event.type==SDL_QUIT) {salirJuego=true;}//Si se detecta una salida de SDL o...
			if(event.type==SDL_KEYDOWN){ }

		}
		SDL_Flip(screen);
	}
	return true;
}
