
#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"

class Nave{

	Sprite * sprite;
	int x;
	int y;
public:
	void Mover(int posicion);
	Nave(SDL_Surface*screen,char * rutaImagen);//Constructor
	void Pintar();


}
	
#endif
;