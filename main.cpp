#include "FuncionesAjedrez.h"
#include <iostream>
#include <Windows.h>

#define DURACION_FRAME 100

using namespace std;

int main() {
    //Tenemos el tablero con piezas bien peustas
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
    bool turnoBlancas = true; //nos permite cambiar quien empieza blancas o negras, ahora estan en blancas
    bool enroquesRealizados[2] = { false, false };//vigila el enroque
    bool puedeEnrocar[2] = { true,  true };//verifica las posibilidades de hacer enroque

    //Bucle principal del juego
    while (!juegoTerminado) {
        system("cls");//limpian la terminal (similar que el snake)
        imprimirMatriz(tablero);//Muestra tablero


        //Pedir el movimiento y ponerlo
        Posicion posicionPieza;
        elegirPieza(tablero, turnoBlancas, &posicionPieza);

        //pediremos donde tendra que ir la pieza seleccionada
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

        //Cambia de turno ahcia el otro jugador
        turnoBlancas = !turnoBlancas;

        //se espera un poco hasta la siguiente ronda
        Sleep(DURACION_FRAME);
    }

    //si termina muestra esto
    cout << endl;
    cout << "¡Juego terminado!" << endl;
    return 0;
}
