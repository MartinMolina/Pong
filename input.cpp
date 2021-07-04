#include "input.h"

EstadoInput soltarTecla(int codigoTecla, EstadoInput estadoInput) {

    if (codigoTecla == SDLK_UP) {
        estadoInput.arriba = false;
    }
    else if (codigoTecla == SDLK_DOWN) {
        estadoInput.abajo = false;
    }

    if (codigoTecla == SDLK_RETURN) {
        estadoInput.enter = false;
    }

    if (codigoTecla == SDLK_ESCAPE) {
        estadoInput.escape = false;
    }

    return estadoInput;
}

EstadoInput pulsarTecla(int codigoTecla, EstadoInput estadoInput) {

    if (codigoTecla == SDLK_UP) {
        estadoInput.arriba = true;
        estadoInput.abajo = false;
    }
    else if (codigoTecla == SDLK_DOWN) {
        estadoInput.arriba = false;
        estadoInput.abajo = true;
    }

    if (codigoTecla == SDLK_RETURN) {
        estadoInput.enter = true;
    }

    if (codigoTecla == SDLK_ESCAPE) {
        estadoInput.escape = true;
    }

    return estadoInput;
}

EstadoInput actualizarInput(EstadoInput estadoInput) {
    SDL_Event evento;

    while (SDL_PollEvent(&evento)) {
        switch (evento.type) {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYUP:
            estadoInput = soltarTecla(evento.key.keysym.sym, estadoInput);
            break;

        case SDL_KEYDOWN:
            estadoInput = pulsarTecla(evento.key.keysym.sym, estadoInput);
            break;

        default:
            break;
        }
    }
    return estadoInput;
}