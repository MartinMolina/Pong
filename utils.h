#pragma once
#include <string>
#include "render.h"

using namespace std;

typedef struct Coordenadas {
	int x;
	int y;
};

typedef struct Pelota: Coordenadas {
	Coordenadas direccion;
};

string evaluar(int puntaje1, int puntaje2);
void parpadear(SDL_Texture* textura, int x, int y, SDL_Renderer* renderer);