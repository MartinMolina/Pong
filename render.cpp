#include "render.h"

SDL_Renderer* inicializarSDL(string nombre, int ancho, int alto, SDL_Renderer* renderer) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Window* ventana = SDL_CreateWindow(nombre.c_str(), 100, 100, ancho, alto, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(ventana, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return renderer;
}

SDL_Texture* crearTextura(string archivo, SDL_Renderer* renderer) {

    SDL_Texture* textura;

    printf("Cargando %s...\n", archivo.c_str());

    textura = IMG_LoadTexture(renderer, archivo.c_str());
    return textura;

}

SDL_Texture* crearCartel(string texto, TTF_Font* fuente, SDL_Color color, SDL_Renderer* renderer) {

    SDL_Surface* superficie;
    SDL_Texture* textura;

    superficie = TTF_RenderText_Blended(fuente, texto.c_str(), color);
    textura = SDL_CreateTextureFromSurface(renderer, superficie);
    return textura;

}

void dibujar(SDL_Texture* textura, int x, int y, SDL_Renderer* renderer) {

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(textura, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, textura, NULL, &dest);
}