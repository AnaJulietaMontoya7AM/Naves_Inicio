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


	nave=new Nave(screen,"../Data/MiNave.bmp",(WIDTH_SCREEN/2),(HEIGHT_SCREEN-80),MODULE_MINAVE_NAVE);
	menu=new Objeto(screen,"../Data/Fondo.bmp",0,0,MODULE_MENU_FONDO);
	textos=new Objeto(screen,"../Data/Menu.bmp",0,0,-1);
	//enemigo=new Nave(screen,"../Data/enemigo.bmp",0,0,2);
	fondo=new Objeto(screen,"../Data/Fondo.bmp",0,0,MODULE_MENU_FONDO);

	for(int i=0;i<10;i++) 
	{
		enemigoArreglo[i]=new Nave(screen,"../Data/enemigo.bmp",i*60,0,MODULE_ENEMIGO_NAVE);
		enemigoArreglo[i]->GetNaveObjeto()->SetAutoMovimiento(false);
		enemigoArreglo[i]->GetNaveObjeto()->SetPasoLimite(4);

	}

	tick=0;
	opcionSeleccionada=MODULE_TEXTO_MENU_OPCION1;

	//enemigo->SetAutoMovimiento(false);
	//enemigo->SetPasoLimite(4);

	


	//estado = ESTADO_INICIANDO;// ACT3: MAL Va en el constructor.
}
// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	//delete(keys);
	//delete(enemigo);
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


			Iniciando();//ACT3: Bien.

			InicializandoStage();

			//estado= ESTADO_JUGANDO;
			estado= ESTADO_MENU;
			break;
		case Estado:: ESTADO_MENU:
			menu->Pintar();
			textos->Pintar(MODULE_TEXTO_TITULO,100,50);
			textos->Pintar(MODULE_TEXTO_NOMBRE,0,400);
			Menu();
		
				//estado=ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_PRE_JUGANDO:
			nivelActual=0;
			Vida=1;
			enemigosEliminados=0;
			estado=ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_JUGANDO:
			//enemigo->Actualizar();
			for (int i = 0; i <nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				enemigoArreglo[i]->GetNaveObjeto()->Actualizar();
			}
			MoverEnemigo();
			fondo->Pintar();
			//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));//Limpia la imagen
			keys=SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave->GetNaveObjeto(),BORDE_DERECHO))
					nave->MoverDerecho(nivel[nivelActual].VelocidadNavePropia);
			}

			if (keys[SDLK_LEFT])
			{
				nave->MoverIzquierdo(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_UP])
			{
				nave->MoverArriba(nivel[nivelActual].VelocidadNavePropia);
			}

			if(keys[SDLK_DOWN])
			{
				nave->MoverAbajo(nivel[nivelActual].VelocidadNavePropia);
			}
			if (keys[SDLK_SPACE])
			{
				nave->Disparar(NAVE_PROPIA, nivel[nivelActual].balasMaximas);
			}
			//////SIMULACION COLICIONES////////////
			if (keys[SDLK_x])//BALA ENEMIGO/NUESTRA NAVE
			{
				nave->simularColision(true);
			}
			if (keys[SDLK_c])//NUESTRA VALA/NAVE ENEMIGO
			{
				int enemigoAEliminar=rand()%nivel[nivelActual].NumeroEnemigosVisibles;
				enemigoArreglo[enemigoAEliminar]->simularColision(true);
			}
			if (keys[SDLK_v])//NUESTRA NAVE/NAVE ENEMIGO
			{

			}
			//////////CONTROL DE COLICIONES//////////
			for(int i=0;i<nivel[nivelActual].NumeroEnemigosVisibles;i++)
			{
				if(enemigoArreglo[i]->estaColisionandoConBala(nave))
					Vida--;
				if(nave->estaColisionandoConBala(enemigoArreglo[i]))
				{
					enemigoArreglo[i]->setVisible(false);
					enemigosEliminados++;
					nave->simularColision(false);
					if (enemigosEliminados < nivel[nivelActual].NumeroEnemigosAEliminar)
					{
						enemigoArreglo[i]->CrearNuevo();
					}
				}

			}


			////////////////////////////////////////

			if (Vida<=0)
				estado=ESTADO_TERMINANDO;
			if(enemigosEliminados>=nivel[nivelActual].NumeroEnemigosAEliminar){
				nivelActual++;
			//CARGAR OTRO FONDO;


		}
			nave->Pintar(NAVE_PROPIA);
			//enemigo->Pintar();
			for(int i=0; i<nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				enemigoArreglo[i]->Pintar(NAVE_ENEMIGO);
			enemigoArreglo[i]->AutoDisparar(nivel[nivelActual].balasMaximas);
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
			/*printf("\n5.EstadoFinalizando");
			getchar();*/
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

bool CGame::EsLimitePantalla(Objeto * objeto,int bandera)
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
	//if(enemigo->ObtenerPasoActual()==0)
	//    if(!EsLimitePantalla(enemigo,BORDE_DERECHO))
	//	enemigo->Mover(15);//DERECHA
	//	else{
	//		enemigo->IncrementarPasoActual();
	//        enemigo->IncrementarPasoActual();
	//		}
	/*if(enemigo->ObtenerPasoActual()==1)
		if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
			enemigo->Mover(1);*/
   /* if(enemigo->ObtenerPasoActual()==2)
		if(!EsLimitePantalla(enemigo,BORDE_IZQUIERDO))
			enemigo->Mover(-15);
	else{
			enemigo->IncrementarPasoActual();
	        enemigo->IncrementarPasoActual();
			}*/
  /*if(enemigo->ObtenerPasoActual()==3)
       if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
		   enemigo->Mover(1);*/

	for (int i = 0; i <nivel[nivelActual].NumeroEnemigosVisibles; i++)
	{

		if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==0)
			if(!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(),BORDE_DERECHO))
				enemigoArreglo[i]->GetNaveObjeto()->Mover(nivel[nivelActual].VelocidadNaveEnemigo);//DERECHA
		else{
			enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
	       // enemigoArreglo[i]->IncrementarPasoActual();
		}

		if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==1)
		if(!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(),BORDE_INFERIOR))
			enemigoArreglo[i]->GetNaveObjeto()->Mover2(nivel[nivelActual].VelocidadNaveEnemigo);
		else
		{
			enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
		}

		if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==2)


		if(!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(),BORDE_IZQUIERDO))
			enemigoArreglo[i]->GetNaveObjeto()->Mover(-nivel[nivelActual].VelocidadNaveEnemigo);
		else
		{
			//enemigoArreglo[i]->IncrementarPasoActual();
	        enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
		}

  if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==3)
       if(!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(),BORDE_SUPERIOR))
		   enemigoArreglo[i]->GetNaveObjeto()->Mover2(-nivel[nivelActual].VelocidadNaveEnemigo);
	   else
	   {
		   enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
	   }
	

	}
	
	}

void CGame:: Menu()
{
	for(int i= MODULE_TEXTO_MENU_OPCION1, j=0;i<= MODULE_TEXTO_MENU_OPCION2; i++,j++)
	{
		keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_UP])
		{
			opcionSeleccionada=MODULE_TEXTO_MENU_OPCION1;
		}

		if (keys[SDLK_DOWN])
		{
			opcionSeleccionada=MODULE_TEXTO_MENU_OPCION2;
		}

		if (i==opcionSeleccionada)
		{
			textos->Pintar(i+2,200,180+(j*80));
		}
		else
			{
				textos->Pintar(i,200,180+(j*80));
		}

		if(keys[SDLK_KP_ENTER])
		{
			if(opcionSeleccionada==MODULE_TEXTO_MENU_OPCION1)
			{
				estado=ESTADO_PRE_JUGANDO;
			}

			else
			{
				estado=ESTADO_FINALIZANDO;
			}
		}
	}
}
