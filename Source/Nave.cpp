#include "Nave.h"

Nave::Nave(SDL_Surface*screen,char * rutaImagen, int x, int y, int module)
{
	nave= new Objeto(screen, rutaImagen,x, y,module);
}

void Nave::Pintar()
{
	nave->Pintar();
}

void Nave::MoverAbajo()
{
	nave->Mover2(15);
}
void Nave::MoverArriba()
{
	nave->Mover2(-15);
}
void Nave::MoverDerecho()
{
	nave->Mover(15);
}
void Nave::MoverIzquierdo()
{
	nave->Mover(-15);
}
Objeto*Nave::GetNaveObjeto()
{
	return nave;
}
