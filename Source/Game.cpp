#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

CGame::CGame(){
	estado = ESTADO_INICIANDO;
	if (SDL_Init(SDL_INIT_VIDEO)<0)
	{
		printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen= SDL_SetVideoMode(640,480,24,SDL_HWSURFACE);
	if (screen==NULL)
	{
		printf("No se puede inicializar el modo grafico: \n", SDL_GetError());
		exit(1);
	}


}



// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			//Iniciando();
			{
				//nave=SDL_LoadBMP ("../data/MiNave.bmp");
				nave= IMG_LoadJPG_RW(SDL_RWFromFile("../Data/cuadro.jpg","rb"));
				SDL_Rect fuente;
				fuente.x=583;
				fuente.y=384;
				fuente.w=323;
				fuente.h=19;
				SDL_Rect destino;
				destino.x=100;
				destino.y=100;
				fuente.w=100;
				fuente.h=fuente.h;
				SDL_BlitSurface(nave,&fuente, screen, &destino);
			}//INICIALIZAR
			break;
		case Estado:: ESTADO_MENU:
			break;
		case Estado::ESTADO_JUGANDO:
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO: //SALIR
				salirJuego = true;
			break;
		};
		SDL_Flip(screen);
    }
	return true;
}
