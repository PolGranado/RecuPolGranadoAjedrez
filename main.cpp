// Archivo: main.cpp

#include "FuncionesAjedrez.h"
#include <iostream>
#include <Windows.h>

#define DURACION_FRAME 100

using namespace std;

int main() {

    // Inicializar el tablero de ajedrez
    char tablero[LADO][LADO] = {
        't', 'h', 'b', 'q', 'k', 'b', 'h', 't',
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
        '*', '*', '*', '*', '*', '*', '*', '*',
        '*', '*', '*', '*', '*', '*', '*', '*',
        '*', '*', '*', '*', '*', '*', '*', '*',
        '*', '*', '*', '*', '*', '*', '*', '*',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
        'T', 'H', 'B', 'Q', 'K', 'B', 'H', 'T'
    };

    imprimirMatriz(tablero);

    bool juegoTerminado = false;
    bool turnoBlancas = true;
    bool enroquesRealizados[2] = { false, false }; // 0 -> blancas
    bool puedeEnrocar[2] = { true, true }; // 0 -> blancas

    while (!juegoTerminado) {

        Posicion posicionPieza;

         elegirPieza(tablero, turnoBlancas, &posicionPieza);

        Posicion posicionDestino;

        do {
            elegirMovimiento(tablero, turnoBlancas, &posicionDestino);

        } while (!gestionarMovimientoValido(tablero, turnoBlancas, enroquesRealizados, puedeEnrocar, posicionPieza, posicionDestino));

        sustituirCasilla(tablero, posicionPieza, posicionDestino);

        juegoTerminado = juegoTerminado || juegoAcabado(tablero);

        turnoBlancas = !turnoBlancas;

        system("cls");
        imprimirMatriz(tablero);

        Sleep(DURACION_FRAME);
    }

    cout << "\n\nJuego terminado!" << endl;

    return 0;
}