#pragma once

#define LADO 8

struct Posicion {
    int fila;
    int columna;
};

//Se imprime el tablero
void imprimirMatriz(char tablero[LADO][LADO]);

//Se declaran las funciones para mover las pieaas
void elegirPieza(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posicionElegida);
void elegirMovimiento(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posicionDestino);
bool gestionarMovimientoValido(char tablero[LADO][LADO], bool turnoBlancas, bool enroques[], bool puedeEnrocar[], Posicion posOrigen, Posicion& posDestino);

void gestionarEnroque(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestinoRey, Posicion posDestinoTorre);
void gestionarPromocion(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestino);

bool movimientoPeon(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino);
bool movimientoTorre(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino);
bool movimientoCaballo(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino);
bool movimientoAlfil(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino);
bool movimientoRey(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion& posDestino, bool enroques[], bool puedeEnrocar[]);
bool movimientoReina(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino);

void sustituirCasilla(char tablero[LADO][LADO], Posicion posOrigen, Posicion posDestino);
bool juegoAcabado(char tablero[LADO][LADO]);
