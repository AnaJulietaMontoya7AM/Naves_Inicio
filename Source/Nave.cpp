#include "Nave.h"
#include "Header.h"

Nave:: Nave(SDL_Surface*screen, char * rutaImagen){
	sprite=new Sprite(screen);
	sprite->CargarImagen(rutaImagen);
	x=(WIDTH_SCREEN/2)-(sprite->WidthModulo(0)/2);//Ancho
	y=(HEIGHT_SCREEN-80)-(sprite->HeightModulo(0));//Alto
}

void Nave::Pintar(){
	sprite->PintarModulo(0,x,y);
}
void Nave::Mover(int posicion){
	x+=posicion;
}