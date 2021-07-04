#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

using namespace std;

SDL_Renderer* inicializarSDL(string nombre, int ancho, int alto, SDL_Renderer* renderer);
SDL_Texture* crearTextura(string archivo, SDL_Renderer* renderer);
SDL_Texture* crearCartel(string texto, TTF_Font* fuente, SDL_Color color, SDL_Renderer* renderer);
void dibujar(SDL_Texture* textura, int x, int y, SDL_Renderer* renderer);