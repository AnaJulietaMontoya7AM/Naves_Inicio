#include "SpriteDef.h"
#include "Header.h"


SpriteDef::SpriteDef(){
	Modulos[0].id=MODULE_MINAVE_NAVE;
	Modulos[0].x=0;
	Modulos[0].y=0;
	Modulos[0].w=64;
	Modulos[0].h=64;

	Modulos[1].id=MODULE_MENU_FONDO;
	Modulos[1].x=0;
	Modulos[1].y=0;
	Modulos[1].w= WIDTH_SCREEN;
	Modulos[1].h= HEIGHT_SCREEN;

	Modulos[2].id=MODULE_ENEMIGO_NAVE;
	Modulos[2].x=0;
	Modulos[2].y=0;
	Modulos[2].w= 54;
	Modulos[2].h= 61;

	Modulos[3].id=MODULE_TEXTO_TITULO;//Titulo
	Modulos[3].x=196;
	Modulos[3].y=59;
	Modulos[3].w= 253;
	Modulos[3].h= 31;

	Modulos[4].id=MODULE_TEXTO_NOMBRE;//Nombre
	Modulos[4].x=6;
	Modulos[4].y=430;
	Modulos[4].w= 479;
	Modulos[4].h= 38;

	Modulos[5].id=MODULE_TEXTO_MENU_OPCION1;
	Modulos[5].x=192;
	Modulos[5].y=136;
	Modulos[5].w= 86;
	Modulos[5].h= 30;

	Modulos[6].id=MODULE_TEXTO_MENU_OPCION2;
	Modulos[6].x=193;
	Modulos[6].y=202;
	Modulos[6].w= 88;
	Modulos[6].h= 26;

	Modulos[7].id=MODULE_TEXTO_MENU_OPCION1_SELECCIONADO;
	Modulos[7].x=340;
	Modulos[7].y=156;
	Modulos[7].w= 87;
	Modulos[7].h= 27;

	Modulos[8].id=MODULE_TEXTO_MENU_OPCION2_SELECCIONADO;
	Modulos[8].x=343;
	Modulos[8].y=195;
	Modulos[8].w= 69;
	Modulos[8].h= 28;

	Modulos[9].id=MODULE_BALAS_BALA;
	Modulos[9].x=0;
	Modulos[9].y=0;
	Modulos[9].w=5;
	Modulos[9].h=5;


}