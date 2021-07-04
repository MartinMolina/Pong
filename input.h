#pragma once
#include "SDL.h"

typedef struct EstadoInput {
    bool arriba;
    bool abajo;
    bool enter;
    bool escape;
};

EstadoInput soltarTecla(int codigoTecla, EstadoInput estadoInput);
EstadoInput pulsarTecla(int codigoTecla, EstadoInput estadoInput);
EstadoInput actualizarInput(EstadoInput estadoInput);