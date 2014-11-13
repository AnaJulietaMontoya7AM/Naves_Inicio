#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Header.h"
#include <SDL.h>
#include <SDL_image.h>

CGame::CGame()
{
	tiempoFrameInicial=0;
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

	screen= SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE );
	if (screen==NULL)
	{
		printf("No se puede inicializar el modo grafico: \n", SDL_GetError());
		getchar();
		exit(1); 
	}
	SDL_WM_SetCaption( "Mi primer Juego", NULL );
	atexit(SDL_Quit);


	nave=new Nave(screen,"../Data/MiNave.bmp",(WIDTH_SCREEN/2)/*-(sprite->WidthModulo(0)/2))*/,(HEIGHT_SCREEN-80)/*-(sprite->HeightModulo(0)*/);
	enemigo=new Nave(screen,"../Data/enemigo.bmp",0,0);

	for(int i=0;i<10;i++)
	{
		enemigoArreglo[i]=new Nave(screen,"../Data/enemigo.bmp",i*60,0);
		enemigoArreglo[i]->SetAutoMovimiento(false);
		enemigoArreglo[i]->SetPasoLimite(4);

	}

	tick=0;

	enemigo->SetAutoMovimiento(false);
	enemigo->SetPasoLimite(4);

	


	//estado = ESTADO_INICIANDO;// ACT3: MAL Va en el constructor.
}
// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	//delete(keys);
	delete(enemigo);
	delete *enemigoArreglo;
	SDL_FreeSurface(screen);
	SDL_Quit();
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;

          int Bandera=0;

	while (salirJuego == false){

		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:

			printf("\n1.EstadoIniciando");
			Iniciando();

			Iniciando();//ACT3: Bien.

			estado= ESTADO_MENU;
			break;
		case Estado:: ESTADO_MENU:
			if (Bandera==0)
			{
				printf("\n2.EstadoMenu");
				Bandera=1;
				estado=ESTADO_JUGANDO;
			}else
			{
				printf("\n2.EstadoMenu");
				estado=ESTADO_FINALIZANDO;
			}
			break;
		case Estado::ESTADO_JUGANDO:
			enemigo->Actualizar();
			for (int i = 0; i <10; i++)
			{
				enemigoArreglo[i]->Actualizar();
			}
			MoverEnemigo();
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));//Limpia la imagen
			keys=SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave,BORDE_DERECHO))
				nave->Mover(15);
			}

			if (keys[SDLK_LEFT])
			{
				nave->Mover(-15);
			}
			if(keys[SDLK_UP])
			{
				nave->Mover2(-15);
			}

			if(keys[SDLK_DOWN])
			{
				nave->Mover2(15);
			}
			nave->Pintar();
			enemigo->Pintar();
			for(int i=0; i<10; i++)
			{
			enemigoArreglo[i]->Pintar();
			}
			if (keys[SDLK_0])
			{
				printf("\n3.EstadoJugando");
				estado=ESTADO_TERMINANDO;
			}
			break;
		case Estado::ESTADO_TERMINANDO:
			printf("\n4.EstadoTerminando");
			estado=ESTADO_MENU;
			break;

		case Estado::ESTADO_FINALIZANDO:
			printf("\n5.EstadoFinalizando");
			getchar();
				salirJuego = true;

	

			break;
		};
		while (SDL_PollEvent(&event))//Aqui SDL creara una lista de eventos ocurridos
		{
			if (event.type==SDL_QUIT) {salirJuego=true;}//Si se detecta una salida de SDL o...
			if(event.type==SDL_KEYDOWN){ }

		}
		SDL_Flip(screen);
		tiempoFrameFinal=SDL_GetTicks();
		while(tiempoFrameFinal<(tiempoFrameInicial + FPS_DELAY))
		{
		
			tiempoFrameFinal=SDL_GetTicks();
			SDL_Delay(1);
		}
		printf("Frames:%dTiempo: %dTiempo promedio: %fTiempo por frame: %d FPS:%f\n",tick,SDL_GetTicks(),(float)SDL_GetTicks()/(float)tick,tiempoFrameFinal-tiempoFrameInicial,1000.0f/(float)(tiempoFrameFinal-tiempoFrameInicial));
		tiempoFrameInicial=tiempoFrameFinal;
		tick++;
	}
	return true;
}

bool CGame::EsLimitePantalla(Nave * objeto,int bandera)
{
	if(bandera & BORDE_IZQUIERDO)
	if (objeto->ObtenerX()<=0)
		return true;
	if(bandera&BORDE_SUPERIOR)
	if (objeto->ObtenerY()<=0)
		return true;
	if(bandera & BORDE_DERECHO)
	if (objeto->ObtenerX ()>= WIDTH_SCREEN-objeto->ObtenerW())
		return true;
	if(bandera & BORDE_INFERIOR)
	if (objeto->ObtenerY ()>= HEIGHT_SCREEN-objeto->ObtenerH())
		return true;
	return false;
	
}

void CGame::MoverEnemigo()
{
	if(enemigo->ObtenerPasoActual()==0)
	    if(!EsLimitePantalla(enemigo,BORDE_DERECHO))
		enemigo->Mover(15);//DERECHA
		else{
			enemigo->IncrementarPasoActual();
	        enemigo->IncrementarPasoActual();
			}
	/*if(enemigo->ObtenerPasoActual()==1)
		if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
			enemigo->Mover(1);*/
    if(enemigo->ObtenerPasoActual()==2)
		if(!EsLimitePantalla(enemigo,BORDE_IZQUIERDO))
			enemigo->Mover(-15);
	else{
			enemigo->IncrementarPasoActual();
	        enemigo->IncrementarPasoActual();
			}
  /*if(enemigo->ObtenerPasoActual()==3)
       if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
		   enemigo->Mover(1);*/

	for (int i = 0; i < 10; i++)
	{
		if(enemigoArreglo[i]->ObtenerPasoActual()==0)
	    if(!EsLimitePantalla(enemigoArreglo[i],BORDE_DERECHO))
	enemigoArreglo[i]->Mover(15);//DERECHA
		else{
			enemigoArreglo[i]->IncrementarPasoActual();
	        enemigoArreglo[i]->IncrementarPasoActual();
		}
	/*if(enemigo->ObtenerPasoActual()==1)
		if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
			enemigo->Mover(1);*/
		if(enemigoArreglo[i]->ObtenerPasoActual()==2)
		if(!EsLimitePantalla(enemigoArreglo[i],BORDE_IZQUIERDO))
			enemigoArreglo[i]->Mover(-15);
		else
		{
			enemigoArreglo[i]->IncrementarPasoActual();
	        enemigoArreglo[i]->IncrementarPasoActual();
		}
  /*if(enemigo->ObtenerPasoActual()==3)
       if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
		   enemigo->Mover(1);*/
	

	}
	
	}
