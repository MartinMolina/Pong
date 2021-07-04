#include "utils.h"

string evaluar(int puntaje1, int puntaje2) {

    string resultado;

    if (puntaje1 == puntaje2)
        resultado = "EMPATE";
    else if (puntaje1 > puntaje2)
        resultado = "JUGADOR GANA";
    else
        resultado = "CPU GANA";

    return resultado;
}

void parpadear(SDL_Texture* textura, int x, int y, SDL_Renderer* renderer) {
    if ((SDL_GetTicks() / 1000) % 2 == 0)
        dibujar(textura, x, y, renderer);
}