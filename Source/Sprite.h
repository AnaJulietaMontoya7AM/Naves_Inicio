#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"


class Sprite
{
	SDL_Surface * imagen;//La imagen a manipular
	SDL_Surface * screen;//La pantalla
	SpriteDef spriteDef;//Definicion del sprite
public:
	Sprite(SDL_Surface*screen);//Constructor, recive la pantalla
	~Sprite();//Destructor se llama con delete
	void CargarImagen(char * path);
	
	void PintarModulo(int nombre, int x,int y);
	int WidthModulo(int module);
	int HeightModulo(int module);




};

#endif 

