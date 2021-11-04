#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "input.h"
#include "render.h"
#include "utils.h"

using namespace std;

const float C_FPS = 60.0;

SDL_Renderer* renderer;
TTF_Font* fuente8Bits;
TTF_Font* fuente8BitsGrande;
SDL_Color colorFuente = { 255, 255, 255 };
SDL_Surface* superficieTitulo;
SDL_Surface* superficieEmpezar;
SDL_Surface* superficieTiempo;
SDL_Surface* superficiePuntaje1;
SDL_Surface* superficiePuntaje2;
SDL_Surface* superficieResultado;
SDL_Surface* superficieVolver;
SDL_Texture* texturaTitulo;
SDL_Texture* texturaEmpezar;
SDL_Texture* texturaRed;
SDL_Texture* texturaPaleta;
SDL_Texture* texturaPelota;
SDL_Texture* texturaTiempo;
SDL_Texture* texturaPuntaje1;
SDL_Texture* texturaPuntaje2;
SDL_Texture* texturaResultado;
SDL_Texture* texturaVolver;

bool ejecutando = true;
bool enPartida = false;
bool postPartida = false;

int puntaje1 = 0;
int puntaje2 = 0;
int tiempoPartida = 120;
int difTiempo;

float gameTimer = 0;
float velocidadPelotaX = 5;
float velocidadPelotaY = 5;

string resultado;

Coordenadas paleta1;
Coordenadas paleta2;
Coordenadas pelota;

EstadoInput estadoInput;


void cargarAssets() {

    fuente8Bits = TTF_OpenFont("recursos/8-bit.ttf", 50);
    fuente8BitsGrande = TTF_OpenFont("recursos/8-bit.ttf", 225);
    texturaRed = crearTextura("recursos/red.png", renderer);
    texturaPaleta = crearTextura("recursos/paleta.png", renderer);
    texturaPelota = crearTextura("recursos/pelota.png", renderer);
    texturaTitulo = crearCartel("PONG!", fuente8BitsGrande, colorFuente, renderer);
    texturaEmpezar = crearCartel("pulsa enter para empezar", fuente8Bits, colorFuente, renderer);
    texturaVolver = crearCartel("pulsa esc para reiniciar", fuente8Bits, colorFuente, renderer);

}

void inicializarPosiciones() {
    paleta1.x = 100;
    paleta1.y = 100;
    paleta2.x = 1160;
    paleta2.y = 360;
    pelota.x = 630;
    pelota.y = 100;
}

void inicializarJuego() {
    renderer = inicializarSDL("Pong!", 1280, 720, renderer);
    cargarAssets();
    inicializarPosiciones();
}

void refrescarPartida(float deltaTimeInSeconds) {

    const float VELOCIDAD_PALETA = 250;

    float movimiento = VELOCIDAD_PALETA * deltaTimeInSeconds;


    // Manejo del tiempo de la partida

    tiempoPartida = ((SDL_GetTicks() - difTiempo) / 1000 - 120) * (-1);

    if (tiempoPartida == 0)
    {
        resultado = evaluar(puntaje1, puntaje2);

        // Terminar partida
        enPartida = false;
        postPartida = true;
    }


    // Paleta controlada por Jugador

    if (estadoInput.arriba && paleta1.y > 0)
        paleta1.y -= movimiento;
    else if (estadoInput.abajo && paleta1.y < 570)
        paleta1.y += movimiento;


    // Fisicas de la pelota

    if (pelota.x == 120 && (pelota.y > paleta1.y - 20 && pelota.y < paleta1.y + 150) || pelota.x == 1140 && (pelota.y > paleta2.y - 20 && pelota.y < paleta2.y + 150))
        velocidadPelotaX = -velocidadPelotaX;

    if (pelota.y == 0 || pelota.y == 700)
        velocidadPelotaY = -velocidadPelotaY;

    if (pelota.x <= -20 || pelota.x >= 1280)
    {
        if (pelota.x >= 1280)
            puntaje1++;
        else
            puntaje2++;
        inicializarPosiciones();
    }

    pelota.x += velocidadPelotaX;
    pelota.y += velocidadPelotaY;


    // Paleta controlada por CPU

    if (pelota.x > 690 && velocidadPelotaX > 0 && (SDL_GetTicks() / 1000) % 4 != 0)
    {
        if (pelota.y > paleta2.y)
        {
            if (paleta2.y < 570)
                paleta2.y += movimiento;
        }
        else if (paleta2.y > 0)
            paleta2.y -= movimiento;
    }

}

void renderizar() {

    // Limpia el buffer del renderer
    SDL_RenderClear(renderer);

    // Dependiendo de la pantalla actual, elige qué cosas insertar en el renderer
    if (enPartida) {
        texturaPuntaje1 = crearCartel(to_string(puntaje1).c_str(), fuente8Bits, colorFuente, renderer);
        texturaPuntaje2 = crearCartel(to_string(puntaje2).c_str(), fuente8Bits, colorFuente, renderer);
        texturaTiempo = crearCartel(to_string(tiempoPartida).c_str(), fuente8Bits, colorFuente, renderer);
        dibujar(texturaPaleta, paleta1.x, paleta1.y, renderer);
        dibujar(texturaPaleta, paleta2.x, paleta2.y, renderer);
        dibujar(texturaPelota, pelota.x, pelota.y, renderer);
        dibujar(texturaRed, 0, 0, renderer);
        dibujar(texturaPuntaje1, 320, 100, renderer);
        dibujar(texturaPuntaje2, 960, 100, renderer);
        dibujar(texturaTiempo, 0, 0, renderer);
    }
    else {
        if (!postPartida) {
            dibujar(texturaTitulo, 75, 100, renderer);
            parpadear(texturaEmpezar, 75, 500, renderer);
        }
        else {
            texturaResultado = crearCartel(resultado.c_str(), fuente8Bits, colorFuente, renderer);
            dibujar(texturaResultado, 200, 150, renderer);
            parpadear(texturaVolver, 85, 500, renderer);
        }
    }

    // Una vez insertados los dibujos en el renderer, los muestra
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {

    inicializarJuego();

    int currentTime = SDL_GetTicks();

    
    // Game Loop

    while (ejecutando) {

        int previousTime = currentTime;
        currentTime = SDL_GetTicks();
        float deltaTime = currentTime - previousTime; // Numeros cercanos a 16.6;
        float deltaTimeInSeconds = deltaTime / 1000.0; // 0.01 Segundos
        gameTimer += deltaTimeInSeconds;

        estadoInput = actualizarInput(estadoInput);

        if (enPartida)
            refrescarPartida(deltaTimeInSeconds);
        else
        {
            difTiempo = SDL_GetTicks();


            if (!postPartida && estadoInput.enter)
                enPartida = true; // Comenzar partida
            else if (estadoInput.escape)
            {
                postPartida = false; // Volver al inicio
                inicializarPosiciones();
                puntaje1 = 0;
                puntaje2 = 0;
            }
        }

        renderizar();

        SDL_Delay(1000 / C_FPS); // 60 FPS
    }

    return 0;
    
}