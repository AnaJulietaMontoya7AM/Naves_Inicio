
#include "Sprite.h"
#include <SDL.h>

//Constructor
Sprite::Sprite(SDL_Surface*screen){
	screen;
	this->screen=screen;
}
//Destructor
Sprite::~Sprite(){
	SDL_FreeSurface(imagen);
}
	void  Sprite::CargarImagen(char * path){
		imagen = SDL_LoadBMP(path);
		//Fondo de nave transparente
		SDL_SetColorKey(imagen, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(imagen-> format, 255, 0,255));
	}

	//void Sprite::PintarModulo(int nombre,int x ,int y, int w, int h)
	/*}
		SDL_Rect src;
		src.x=x;
		src.y=y;
		src.w=w;
		src.h=h;
		SDL_BlitSurface(imagen,&src, screen, NULL);
	}*/

		void Sprite::PintarModulo(int nombre,int x ,int y)
	{
		SDL_Rect src;
		src.x= spriteDef.Modulos[nombre].x;
		src.y=spriteDef.Modulos[nombre].y;
		src.w=spriteDef.Modulos[nombre].w;
		src.h=spriteDef.Modulos[nombre].h;
		SDL_Rect dest;
		dest.x=x;
		dest.y=y;
		SDL_BlitSurface(imagen,&src, screen, &dest);


	}
		int Sprite:: WidthModulo(int module){
			return spriteDef.Modulos[module].w;

		}
			int Sprite:: HeightModulo(int module){
				return spriteDef.Modulos[module].h;

		}



