#include "FuncionesAjedrez.h"
#include <iostream>

using namespace std;

void imprimir_matriz(char tablero[LADO][LADO])
{
	cout << "  1 2 3 4 5 6 7 8" << endl;

	for (int i = 0; i < LADO; i++)
	{
		cout << LADO - i << ' ';
		for (int j = 0; j < LADO; j++)
		{
			cout << tablero[i][j] << ' ';
		}
		cout << endl;
	}
}

void elige_pieza(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posPiezaElegida)
{
	bool posicionValida = false;
	do {

		int inputFila;
		int inputColumna;
		do
		{
			system("cls");
			imprimir_matriz(tablero);
			cout << endl << endl;
			cout << "Elige una pieza (introduce su posicion)" << endl;
			cout << " Introduce la fila: " << flush;
			cin >> inputFila;
		} while ((inputFila <= 0 || inputFila > 8));
		cout << endl;
		do
		{
			system("cls");
			imprimir_matriz(tablero);
			cout << endl << endl;
			cout << "Elige una pieza (introduce su posicion)" << endl;
			cout << " Introduce la fila: " << inputFila;
			cout << endl;
			cout << " Introduce la columna: " << flush;
			cin >> inputColumna;
			cout << endl;
		} while (inputColumna <= 0 || inputColumna > 8);

		if (turnoBlancas)
		{
			switch (tablero[LADO - inputFila][inputColumna - 1])
			{
			case 'T':
			case 'H':
			case 'B':
			case 'Q':
			case 'K':
			case 'P':
				(*posPiezaElegida).fila = LADO - inputFila;
				(*posPiezaElegida).columna = inputColumna - 1;
				posicionValida = true;
				break;

			default: break;
			}

			/*if (tablero[inputFila][inputColumna] == 'T')
			if (tablero[inputFila][inputColumna] == 'H')
			if (tablero[inputFila][inputColumna] == 'Q')*/
		}
		else
		{
			switch (tablero[LADO - inputFila][inputColumna-1])
			{
			case 't':
			case 'h':
			case 'b':
			case 'q':
			case 'k':
			case 'p':
				(*posPiezaElegida).fila = LADO - inputFila;
				(*posPiezaElegida).columna = inputColumna - 1;
				posicionValida = true;
				break;

			default: break;
			}
		}

	} while (!posicionValida);

}

bool gestionar_movimiento_valido(char tablero[LADO][LADO], bool turnoBlancas, bool enroques[], bool puedeEnrocar[], Posicion posOrigen, Posicion& posDestino)
{
	switch (tablero[posOrigen.fila][posOrigen.columna])
	{
	case 'T':
	case 't':
		return movimiento_torre(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'P':
	case 'p':
		return movimiento_peon(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'H':
	case 'h':
		return movimiento_caballo(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'B':
	case 'b':
		return movimiento_alfil(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'Q':
	case 'q':
		return movimiento_reina(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'K':
	case 'k':
		return movimiento_rey(tablero, turnoBlancas, posOrigen, posDestino, enroques, puedeEnrocar);
		break;

	default: 
		return false;
		break;
	}
}

void gestionar_enroque(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestinoRey, Posicion posDestinoTorre)
{
	if (turnoBlancas)
	{
		tablero[posDestinoRey.fila][posDestinoRey.columna] = 'K';
		tablero[posDestinoTorre.fila][posDestinoTorre.columna] = 'T';
	}
	else
	{
		tablero[posDestinoRey.fila][posDestinoRey.columna] = 'k';
		tablero[posDestinoTorre.fila][posDestinoTorre.columna] = 't';
	}
}

void gestionar_promotion(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestino)
{
	if (turnoBlancas)
	{
		tablero[posDestino.fila][posDestino.columna] = 'Q';
	}
	else
	{
		tablero[posDestino.fila][posDestino.columna] = 'q';
	}
}

bool movimiento_peon(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
			if (((posOrigen.columna + 1 == posDestino.columna) ||	// derecha
				(posOrigen.columna - 1 == posDestino.columna)) &&	//izquierda
				(posOrigen.fila - 1 == posDestino.fila))			//casilla siguiente hacia arriba
			{
				if (posDestino.fila == 0)
					gestionar_promotion(tablero, turnoBlancas, posDestino);
				return true;
			}
			break;

		case '*':
			if ((posOrigen.fila - 1 == posDestino.fila) &&			//peon se mueve hacia arriba
				(posOrigen.columna == posDestino.columna))
			{
				if (posDestino.fila == 0)
					gestionar_promotion(tablero, turnoBlancas, posDestino);
				return true;
			}
			break;

		default:
			break;
		}
	}

	else {
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
			//juegan las negras
			if (((posOrigen.columna + 1 == posDestino.columna) ||	// derecha
				(posOrigen.columna - 1 == posDestino.columna)) &&	//izquierda
				(posOrigen.fila + 1 == posDestino.fila))			//casilla siguiente hacia abajo
			{
				if (posDestino.fila == LADO-1)
					gestionar_promotion(tablero, turnoBlancas, posDestino);
				return true;
			}
			break;

		case '*':
			if ((posOrigen.fila + 1 == posDestino.fila) &&			//peon se mueve hacia abajo
				(posOrigen.columna == posDestino.columna))
			{
				if (posDestino.fila == LADO-1)
					gestionar_promotion(tablero, turnoBlancas, posDestino);
				return true;
			}
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimiento_torre(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*':

			if (posDestino.fila != posOrigen.fila)	//movimiento vertical
			{
				int dif_filas = posDestino.fila - posOrigen.fila;
				for (int offset = dif_filas > 0 ? dif_filas-1 : dif_filas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila + offset][posOrigen.columna] != '*')
						return false;
				}
			}
			else									//movimiento horizontal
			{
				int dif_columnas = posDestino.columna - posOrigen.columna;
				for (int offset = dif_columnas > 0 ? dif_columnas-1 : dif_columnas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')	//saltando por encima de otra pieza
						return false;
				}
			}
			
			// todas las posiciones que lleguen a estas funciones siempre estan dentro del tablero
			// (se comprueba en elige_pieza() y elige_movimiento())

			return
				((posOrigen.columna != posDestino.columna) &&
				(posOrigen.fila == posDestino.fila)) ||
				((posOrigen.fila != posDestino.fila) &&
				(posOrigen.columna == posDestino.columna));
			break;

		default:
			break;
		}
	}

	else {
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
		case '*':

			if (posDestino.fila != posOrigen.fila)	//movimiento vertical
			{
				int dif_filas = posDestino.fila - posOrigen.fila;
				for (int offset = dif_filas > 0 ? dif_filas - 1 : dif_filas + 1;
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila + offset][posOrigen.columna] != '*')
						return false;
				}
			}
			else									//movimiento horizontal
			{
				int dif_columnas = posDestino.columna - posOrigen.columna;
				for (int offset = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')	//saltando por encima de otra pieza
						return false;
				}
			}

			return
				((posOrigen.columna != posDestino.columna) &&
				(posOrigen.fila == posDestino.fila)) ||
				((posOrigen.fila != posDestino.fila) &&
				(posOrigen.columna == posDestino.columna));
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimiento_caballo(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*':

			//el caballo puede saltar otras piezas, no hacen falta otras comprobaciones

			return
				((posOrigen.columna + 1 == posDestino.columna) &&	//	 # D
				(posOrigen.fila - 2 == posDestino.fila)) ||			//	 #
																	//	 O
				
				((posOrigen.columna - 1 == posDestino.columna) &&	// D #
				(posOrigen.fila - 2 == posDestino.fila)) ||			//   #
																	//	 O
			
				((posOrigen.columna - 1 == posDestino.columna) &&	//   O
				(posOrigen.fila + 2 == posDestino.fila)) ||			//   #
																	// D #
				
				((posOrigen.columna + 1 == posDestino.columna) &&	//   O
				(posOrigen.fila + 2 == posDestino.fila)) ||			//   #
																	//   # D
				
				((posOrigen.columna + 2 == posDestino.columna) &&	//     D
				(posOrigen.fila - 1 == posDestino.fila)) ||			// O # #
																	// 

				((posOrigen.columna + 2 == posDestino.columna) &&	//     
				(posOrigen.fila + 1 == posDestino.fila)) ||			// O # #
																	//     D

				((posOrigen.columna - 2 == posDestino.columna) &&	// D  
				(posOrigen.fila - 1 == posDestino.fila)) ||			// # # O
																	//
				 
				((posOrigen.columna - 2 == posDestino.columna) &&	//     
				(posOrigen.fila + 1 == posDestino.fila)); 			// # # O
																	// D   
				
			break;

		default:
			break;
		}
	}

	else {
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
		case '*':

			return
				((posOrigen.columna + 1 == posDestino.columna) &&	//	 # D
				(posOrigen.fila - 2 == posDestino.fila)) ||			//	 #
																	//	 O

				((posOrigen.columna - 1 == posDestino.columna) &&	// D #
				(posOrigen.fila - 2 == posDestino.fila)) ||			//   #
																	//	 O

				((posOrigen.columna - 1 == posDestino.columna) &&	//   O
				(posOrigen.fila + 2 == posDestino.fila)) ||			//   #
																	// D #

				((posOrigen.columna + 1 == posDestino.columna) &&	//   O
				(posOrigen.fila + 2 == posDestino.fila)) ||			//   #
																	//   # D

				((posOrigen.columna + 2 == posDestino.columna) &&	//     D
				(posOrigen.fila - 1 == posDestino.fila)) ||			// O # #
																	// 
				
				((posOrigen.columna + 2 == posDestino.columna) &&	//     
				(posOrigen.fila + 1 == posDestino.fila)) ||			// O # #
																	//     D

				((posOrigen.columna - 2 == posDestino.columna) &&	// D  
				(posOrigen.fila - 1 == posDestino.fila)) ||			// # # O
																	//

				((posOrigen.columna - 2 == posDestino.columna) &&	//     
				(posOrigen.fila + 1 == posDestino.fila)); 			// # # O
																	// D 
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimiento_alfil(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*': {
			int dif_filas = posDestino.fila - posOrigen.fila;
			int dif_columnas = posDestino.columna - posOrigen.columna;

			if (abs(dif_filas) != abs(dif_columnas))	//si son distintos, el movimiento no es diagonal
				return false;
			
			int offset_filas = dif_filas > 0 ? dif_filas - 1 : dif_filas + 1;
			int offset_columnas = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;
			for (	; offset_filas != 0 || offset_columnas != 0; 
				offset_filas = offset_filas > 0 ? offset_filas - 1 : offset_filas + 1, 
				offset_columnas = offset_columnas > 0 ? offset_columnas - 1 : offset_columnas + 1)
			{
				if (tablero[posOrigen.fila + offset_filas][posOrigen.columna + offset_columnas] != '*')
					return false;
			}

			return
				(posOrigen.columna != posDestino.columna) &&
				(posOrigen.fila != posDestino.fila);
		}
			break;

		default:
			break;
		}
	}

	else {
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
		case '*': {
			int dif_filas = posDestino.fila - posOrigen.fila;
			int dif_columnas = posDestino.columna - posOrigen.columna;

			if (abs(dif_filas) != abs(dif_columnas))	//si son distintos, el movimiento no es diagonal
				return false;
			
			int offset_filas = dif_filas > 0 ? dif_filas - 1 : dif_filas + 1;
			int offset_columnas = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;
			for ( ;
				offset_filas != 0 || offset_columnas != 0;
				offset_filas = offset_filas > 0 ? offset_filas - 1 : offset_filas + 1,
				offset_columnas = offset_columnas > 0 ? offset_columnas - 1 : offset_columnas + 1)
			{
				if (tablero[posOrigen.fila + offset_filas][posOrigen.columna + offset_columnas] != '*')
					return false;
			}

			return
				(posOrigen.columna != posDestino.columna) &&
				(posOrigen.fila != posDestino.fila);
		}
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimiento_rey(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion& posDestino, bool enrocado[], bool puedeEnrocar[])
{
	if (turnoBlancas)
	{
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
			if (!enrocado[0] && puedeEnrocar[0])
			{
				int dif_columnas = posDestino.columna - posOrigen.columna;
				for (int offset = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')	//saltando por encima de otra pieza
						return false;
				}

				if (posDestino.columna < posOrigen.columna) //enroque largo
				{
					Posicion reyEnrocado = { posOrigen.fila, posOrigen.columna - 2 };
					Posicion torreEnrocada = { reyEnrocado.fila, reyEnrocado.columna + 1 };
				
					enrocado[0] = true;
					puedeEnrocar[0] = false;
					gestionar_enroque(tablero, turnoBlancas, reyEnrocado, torreEnrocada);
					tablero[posDestino.fila][posDestino.columna] = '*';
					posDestino.fila = reyEnrocado.fila;
					posDestino.columna = reyEnrocado.columna;
					return true;
				}
				else //enroque corto
				{
					Posicion reyEnrocado = { posOrigen.fila, posOrigen.columna + 2 };
					Posicion torreEnrocada = { reyEnrocado.fila, reyEnrocado.columna - 1 };

					enrocado[0] = true;
					puedeEnrocar[0] = false;
					gestionar_enroque(tablero, turnoBlancas, reyEnrocado, torreEnrocada);
					tablero[posDestino.fila][posDestino.columna] = '*';
					posDestino.fila = reyEnrocado.fila;
					posDestino.columna = reyEnrocado.columna;
					return true;
				}
			}
			break;

		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*':
			puedeEnrocar[0] = false;			

			return
				((posOrigen.fila - 1 == posDestino.fila) &&			//Arriba
				(posOrigen.columna == posDestino.columna)) ||
				((posOrigen.fila == posDestino.fila) &&				//Izquierda
				(posOrigen.columna + 1 == posDestino.columna)) ||
				((posOrigen.fila + 1 == posDestino.fila) &&			//Abajo
				(posOrigen.columna == posDestino.columna)) ||
				((posOrigen.fila == posDestino.fila) &&				//Derecha
				(posOrigen.columna - 1 == posDestino.columna));
			break;

		default:
			break;
		}
	}

	else {
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
			if (!enrocado[1] && puedeEnrocar[1])
			{
				if (posDestino.columna < posOrigen.columna) //enroque largo
				{
					Posicion reyEnrocado = { posOrigen.fila, posOrigen.columna - 2 };
					Posicion torreEnrocada = { reyEnrocado.fila, reyEnrocado.columna + 1 };

					enrocado[1] = true;
					puedeEnrocar[1] = false;
					gestionar_enroque(tablero, turnoBlancas, reyEnrocado, torreEnrocada);
					tablero[posDestino.fila][posDestino.columna] = '*';
					posDestino.fila = reyEnrocado.fila;
					posDestino.columna = reyEnrocado.columna;
					return true;
				}
				else //enroque corto
				{
					Posicion reyEnrocado = { posOrigen.fila, posOrigen.columna + 2 };
					Posicion torreEnrocada = { reyEnrocado.fila, reyEnrocado.columna - 1 };

					enrocado[1] = true;
					puedeEnrocar[1] = false;
					gestionar_enroque(tablero, turnoBlancas, reyEnrocado, torreEnrocada);
					tablero[posDestino.fila][posDestino.columna] = '*';
					posDestino.fila = reyEnrocado.fila;
					posDestino.columna = reyEnrocado.columna;
					return true;
				}
			}
			break;

		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
			puedeEnrocar[1] = false;

			return
				((posOrigen.fila - 1 == posDestino.fila) &&			//Arriba
				(posOrigen.columna == posDestino.columna)) ||
				((posOrigen.fila == posDestino.fila) &&				//Izquierda
				(posOrigen.columna - 1 == posDestino.columna)) ||
				((posOrigen.fila + 1 == posDestino.fila) &&			//Abajo
				(posOrigen.columna == posDestino.columna)) ||
				((posOrigen.fila == posDestino.fila) &&				//Derecha
				(posOrigen.columna - 1 == posDestino.columna));
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimiento_reina(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	return
		movimiento_alfil(tablero, turnoBlancas, posOrigen, posDestino) ||
		movimiento_torre(tablero, turnoBlancas, posOrigen, posDestino);
}

void elige_movimiento(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posDestinoElegida)
{
	int inputFilaDestino;
	int inputColumnaDestino;

	bool posicionValida = false;
	do
	{
		do
		{
			system("cls");
			imprimir_matriz(tablero);
			cout << endl << endl;
			cout << "Elige una posicion destino" << endl;
			cout << " Introduce la fila: " << flush;
			cin >> inputFilaDestino;
		} while ((inputFilaDestino <= 0 || inputFilaDestino > 8));
		cout << endl;
		do
		{
			system("cls");
			imprimir_matriz(tablero);
			cout << endl << endl;
			cout << "Elige una posicion destino" << endl;
			cout << " Introduce la fila: " << inputFilaDestino;
			cout << endl;
			cout << " Introduce la columna: " << flush;
			cin >> inputColumnaDestino;
			cout << endl;
		} while (inputColumnaDestino <= 0 || inputColumnaDestino > 8);

		if (!turnoBlancas)	//las negras solo pueden atacar blancas o usar una casilla vacia
		{
			switch (tablero[LADO - inputFilaDestino][inputColumnaDestino - 1])
			{
			case 'T':
			case 'H':
			case 'B':
			case 'Q':
			case 'K':
			case 'P':
			case '*':
			case 't':
				(*posDestinoElegida).fila = LADO - inputFilaDestino;
				(*posDestinoElegida).columna = inputColumnaDestino - 1;
				posicionValida = true;
				break;

			default: break;
			}
		}
		else
		{
			switch (tablero[LADO - inputFilaDestino][inputColumnaDestino - 1])
			{
			case 't':
			case 'h':
			case 'b':
			case 'q':
			case 'k':
			case 'p':
			case '*':
			case 'T':
				(*posDestinoElegida).fila = LADO - inputFilaDestino;
				(*posDestinoElegida).columna = inputColumnaDestino - 1;
				posicionValida = true;
				break;

			default: break;
			}
		}
	} while (!posicionValida);
}

void sustituir_casilla(char tablero[LADO][LADO], Posicion posOrigen, Posicion posDestino)
{
	char pieza = tablero[posOrigen.fila][posOrigen.columna];
	tablero[posOrigen.fila][posOrigen.columna] = '*';
	tablero[posDestino.fila][posDestino.columna] = pieza;
}

bool juego_acabado(char tablero[LADO][LADO])
{
	bool reyBlancas = false;
	bool reyNegras = false;

	for (int i = 0; i < LADO; i++)
	{
		for (int j = 0; j < LADO; j++)
		{
			if (tablero[i][j] == 'K')
				reyBlancas = true;
			else if(tablero[i][j] == 'k')
				reyNegras = true;
		}
	}
	return !(reyBlancas && reyNegras);
}
