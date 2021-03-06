#include "Objeto.h"
#include "Header.h"

Objeto:: Objeto(SDL_Surface*screen, char * rutaImagen, int x, int y, int module)
{
	this->module=module;
	sprite=new Sprite(screen);
	sprite->CargarImagen(rutaImagen);
	w=sprite->WidthModulo(this->module);
	h=sprite->HeightModulo(this->module);
	this->x=x;
	this->y=y;
	autoMovimiento=false;
	pasoActual=0;
	pasoLimite=-1;
	isVisible=true;
}

void Objeto::SetAutoMovimiento(bool autoMovimiento){
	this->autoMovimiento=autoMovimiento;
}

void Objeto::Actualizar()
{
	if(autoMovimiento)
	{
		Mover(1);
	}
	if(pasoLimite>0)
	{
		//pasoActual++;
		if(pasoActual>=pasoLimite)
			pasoActual=0;
	}
}

void Objeto::Pintar()
{
	if(isVisible)
	sprite->PintarModulo(module,x,y);
}
void Objeto::Pintar(int module, int x, int y)
{
	if(isVisible)
	sprite->PintarModulo(module,x,y);
}

void Objeto::SetVisible(bool isVisible)
{
	this->isVisible=isVisible;
}
void Objeto::Mover(int posicion)
{
	x+=posicion;
}

void Objeto::Mover2(int posicion)
{
	y+=posicion;
}

int Objeto:: ObtenerX()
{
	return x;
}
int Objeto:: ObtenerY()
{
	return y; 
}
int Objeto:: ObtenerW()
{
	return h; 
}
int Objeto:: ObtenerH()
{
	return h; 
}
void Objeto::SetPasoLimite(int pasos)
{
	this ->pasoLimite=pasos;
}

int Objeto::ObtenerPasoActual()
{
	return pasoActual;
}
void Objeto:: IncrementarPasoActual()
{
	pasoActual++;
}
bool Objeto:: EstaColicionando(Objeto* b)
{
	return false;
}

void Objeto::PonerEn(int x, int y)
{
	this->x=x;
	this->y=y;
}