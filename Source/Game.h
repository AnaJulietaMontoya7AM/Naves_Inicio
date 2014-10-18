#include <SDL.h>
#include "Nave.h"
class CGame
{
public:
	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};

	bool Start();
	static CGame instanceGame;

	CGame();
	void Finalize();

private:
	void Iniciando();
	
	Uint8*keys;//Esta variable sirve para ver si determinadas teclas estan o no pulsadas
	SDL_Event event;//La variabe event es un tipo de evento de SDL para monitorizar el teclado
	SDL_Surface * screen;
	Nave * nave;
	Nave*enemigo;
	Estado estado;

};