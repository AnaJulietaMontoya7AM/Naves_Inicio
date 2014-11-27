#ifndef __NAVE_H__
#define __NAVE_H__
#include "Objeto.h"


class Nave
{
	Objeto*nave;
	Objeto*bala;
public:
	Nave(SDL_Surface*screen,char * rutaImagen, int x, int y, int module); 
	void Pintar();
	void MoverIzquierdo();
	void MoverDerecho();
	void MoverAbajo();
	void MoverArriba();
	Objeto*GetNaveObjeto();

};

#endif 