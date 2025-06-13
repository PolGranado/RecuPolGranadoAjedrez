#include "FuncionesAjedrez.h"
#include <iostream>
#include <Windows.h>

#define DURACION_FRAME 100

using namespace std;

int main() {
    // Inicializar el tablero de ajedrez
    char tablero[LADO][LADO] = {
        't','h','b','q','k','b','h','t',
        'p','p','p','p','p','p','p','p',
        '*','*','*','*','*','*','*','*',
        '*','*','*','*','*','*','*','*',
        '*','*','*','*','*','*','*','*',
        '*','*','*','*','*','*','*','*',
        'P','P','P','P','P','P','P','P',
        'T','H','B','Q','K','B','H','T'
    };

    bool juegoTerminado = false;
    bool turnoBlancas = true;
    bool enroquesRealizados[2] = { false, false };
    bool puedeEnrocar[2] = { true,  true };


    while (!juegoTerminado) {
        system("cls");
        imprimirMatriz(tablero);


        //Pedir el movimiento y ponerlo
        Posicion posicionPieza;
        elegirPieza(tablero, turnoBlancas, &posicionPieza);

        Posicion posicionDestino;
        do {
            elegirMovimiento(tablero, turnoBlancas, &posicionDestino);
        } while (!gestionarMovimientoValido(
            tablero, turnoBlancas,
            enroquesRealizados, puedeEnrocar,
            posicionPieza, posicionDestino
        ));

        sustituirCasilla(tablero, posicionPieza, posicionDestino);

        //Verifica el final del juego
        juegoTerminado = juegoAcabado(tablero);
        //Cambia de turno
        turnoBlancas = !turnoBlancas;

        Sleep(DURACION_FRAME);
    }

    cout << endl;
    cout << "¡Juego terminado!" << endl;
    return 0;
}
