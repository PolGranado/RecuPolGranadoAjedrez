#include "FuncionesAjedrez.h"
#include <iostream> 
using namespace std;
 
void imprimirMatriz(char tablero[LADO][LADO])
{
	//Aqui tenemos la cabecera de las columnas  con margenes
	cout << "  ";
	for (int col = 1; col <= LADO; ++col) {
		cout << col << ' ';
	}
	cout << endl;

	//Esto es que cada fila estara numerada 
	for (int fila = 0; fila < LADO; ++fila) {
		cout << (LADO - fila) << ' ';
		//Tenemos el contenido de la fila
		for (int col = 0; col < LADO; ++col) {
			cout << tablero[fila][col] << ' ';
		}
		cout << endl;
	}
}

void elegirPieza(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posPiezaElegida)
{
	bool posicionValida = false;
	do {

		int inputFila;
		int inputColumna;
		do
		{
			system("cls");
			imprimirMatriz(tablero);
			mostrarTurno(turnoBlancas);
			cout << endl << endl;
			cout << "Elige una pieza (introduce su posicion)" << endl;
			cout << " Introduce la fila: " << flush;
			cin >> inputFila;
		} while ((inputFila <= 0 || inputFila > 8));
		cout << endl;
		do
		{
			system("cls");
			imprimirMatriz(tablero);
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

bool gestionarMovimientoValido(char tablero[LADO][LADO], bool turnoBlancas, bool enroques[], bool puedeEnrocar[], Posicion posOrigen, Posicion& posDestino)
{
	switch (tablero[posOrigen.fila][posOrigen.columna])
	{
	case 'T':
	case 't':
		return movimientoTorre(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'P':
	case 'p':
		return movimientoPeon(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'H':
	case 'h':
		return movimientoCaballo(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'B':
	case 'b':
		return movimientoAlfil(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'Q':
	case 'q':
		return movimientoReina(tablero, turnoBlancas, posOrigen, posDestino);
		break;

	case 'K':
	case 'k':
		return movimientoRey(tablero, turnoBlancas, posOrigen, posDestino, enroques, puedeEnrocar);
		break;

	default: 
		return false;
		break;
	}
}

void gestionarEnroque(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestinoRey, Posicion posDestinoTorre)
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

void gestionarPromocion(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestino)
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

bool movimientoPeon(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{
		char destino = tablero[posDestino.fila][posDestino.columna];
		if (destino == '*') {
			if (posOrigen.fila - 1 == posDestino.fila && posOrigen.columna == posDestino.columna)
			{
				if (posDestino.fila == 0)
					gestionarPromocion(tablero, turnoBlancas, posDestino);
				return true;
			}
			if (posOrigen.fila == 6 &&
				posDestino.fila == 4 &&
				tablero[5][posOrigen.columna] == '*')
			{
				return true;
			}
		}
		else {
			switch (destino)
			{
			case 't': case 'h': case 'b': case 'q': case 'k': case 'p':
				if ((posOrigen.columna + 1 == posDestino.columna ||
					posOrigen.columna - 1 == posDestino.columna) &&
					posOrigen.fila - 1 == posDestino.fila)
				{
					if (posDestino.fila == 0)
						gestionarPromocion(tablero, turnoBlancas, posDestino);
					return true;
				}
				break;
			}
		}
	}
	else
	{
		char destino = tablero[posDestino.fila][posDestino.columna];
		if (destino == '*') {
			if (posOrigen.fila + 1 == posDestino.fila &&
				posOrigen.columna == posDestino.columna)
			{
				if (posDestino.fila == LADO - 1)
					gestionarPromocion(tablero, turnoBlancas, posDestino);
				return true;
			}
			if (posOrigen.fila == 1 &&
				posDestino.fila == 3 &&
				tablero[2][posOrigen.columna] == '*')
			{
				return true;
			}
		}
		else {
			switch (destino)
			{
			case 'T': case 'H': case 'B': case 'Q': case 'K': case 'P':
				if ((posOrigen.columna + 1 == posDestino.columna ||
					posOrigen.columna - 1 == posDestino.columna) &&
					posOrigen.fila + 1 == posDestino.fila)
				{
					if (posDestino.fila == LADO - 1)
						gestionarPromocion(tablero, turnoBlancas, posDestino);
					return true;
				}
				break;
			}
		}
	}
	return false;
}

bool movimientoTorre(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
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

			if (posDestino.fila != posOrigen.fila)
			{
				int dif_filas = posDestino.fila - posOrigen.fila;
				for (int offset = dif_filas > 0 ? dif_filas-1 : dif_filas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila + offset][posOrigen.columna] != '*')
						return false;
				}
			}
			else						
			{
				int dif_columnas = posDestino.columna - posOrigen.columna;
				for (int offset = dif_columnas > 0 ? dif_columnas-1 : dif_columnas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')
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

			if (posDestino.fila != posOrigen.fila)
			{
				int dif_filas = posDestino.fila - posOrigen.fila;
				for (int offset = dif_filas > 0 ? dif_filas - 1 : dif_filas + 1;
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila + offset][posOrigen.columna] != '*')
						return false;
				}
			}
			else									
			{
				int dif_columnas = posDestino.columna - posOrigen.columna;
				for (int offset = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')
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

bool movimientoCaballo(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
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


			return
				((posOrigen.columna + 1 == posDestino.columna) &&
				(posOrigen.fila - 2 == posDestino.fila)) ||			
																	
				
				((posOrigen.columna - 1 == posDestino.columna) &&
				(posOrigen.fila - 2 == posDestino.fila)) ||			
																	
			
				((posOrigen.columna - 1 == posDestino.columna) &&	
				(posOrigen.fila + 2 == posDestino.fila)) ||			
				
				((posOrigen.columna + 1 == posDestino.columna) &&	
				(posOrigen.fila + 2 == posDestino.fila)) ||			
								
			
				((posOrigen.columna + 2 == posDestino.columna) &&	
				(posOrigen.fila - 1 == posDestino.fila)) ||			
																	

				((posOrigen.columna + 2 == posDestino.columna) &&   
				(posOrigen.fila + 1 == posDestino.fila)) ||			

				((posOrigen.columna - 2 == posDestino.columna) &&
				(posOrigen.fila - 1 == posDestino.fila)) ||			
				 
				((posOrigen.columna - 2 == posDestino.columna) &&	   
				(posOrigen.fila + 1 == posDestino.fila)); 			

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
				((posOrigen.columna + 1 == posDestino.columna) &&	
				(posOrigen.fila - 2 == posDestino.fila)) ||			

				((posOrigen.columna - 1 == posDestino.columna) &&	
				(posOrigen.fila - 2 == posDestino.fila)) ||			

				((posOrigen.columna - 1 == posDestino.columna) &&	
				(posOrigen.fila + 2 == posDestino.fila)) ||			

				((posOrigen.columna + 1 == posDestino.columna) &&	
				(posOrigen.fila + 2 == posDestino.fila)) ||			
																	

				((posOrigen.columna + 2 == posDestino.columna) &&
				(posOrigen.fila - 1 == posDestino.fila)) ||			
																	
				
				((posOrigen.columna + 2 == posDestino.columna) &&
				(posOrigen.fila + 1 == posDestino.fila)) ||			
																	

				((posOrigen.columna - 2 == posDestino.columna) &&	
				(posOrigen.fila - 1 == posDestino.fila)) ||			
																	

				((posOrigen.columna - 2 == posDestino.columna) &&	  
				(posOrigen.fila + 1 == posDestino.fila)); 			
																	
			break;

		default:
			break;
		}
	}
	return false;
}

bool movimientoAlfil(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
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

			if (abs(dif_filas) != abs(dif_columnas))	
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

			if (abs(dif_filas) != abs(dif_columnas))	
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

bool movimientoRey(char tablero[LADO][LADO],
	bool turnoBlancas,
	Posicion posOrigen,
	Posicion& posDestino,
	bool enrocado[],
	bool puedeEnrocar[])
{
	int colorIdx = turnoBlancas ? 0 : 1;

	int df = posDestino.fila - posOrigen.fila;
	int dc = posDestino.columna - posOrigen.columna;

	//Se mueve hacia cualquier lado pero solo 1 casilla
	if (std::abs(df) <= 1 && std::abs(dc) <= 1 && !(df == 0 && dc == 0)) {
		char destino = tablero[posDestino.fila][posDestino.columna];
		bool esVacia = (destino == '*');
		bool esRival;
		if (turnoBlancas) {
			esRival = std::islower(destino);
		}
		else {
			esRival = std::isupper(destino);
		}
		if (esVacia || esRival) {
			//Si se mueve rey ya no hay enroque
			puedeEnrocar[colorIdx] = false;
			return true;
		}
	}

	return false;
}

bool movimientoReina(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	return
		movimientoAlfil(tablero, turnoBlancas, posOrigen, posDestino) ||
		movimientoTorre(tablero, turnoBlancas, posOrigen, posDestino);
}

void elegirMovimiento(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posDestinoElegida)
{
	int inputFilaDestino;
	int inputColumnaDestino;

	bool posicionValida = false;
	do
	{
		do
		{
			system("cls");
			imprimirMatriz(tablero);
			cout << endl << endl;
			cout << "Elige una posicion destino" << endl;
			cout << " Introduce la fila: " << flush;
			cin >> inputFilaDestino;
		} while ((inputFilaDestino <= 0 || inputFilaDestino > 8));
		cout << endl;
		do
		{
			system("cls");
			imprimirMatriz(tablero);
			cout << endl << endl;
			cout << "Elige una posicion destino" << endl;
			cout << " Introduce la fila: " << inputFilaDestino;
			cout << endl;
			cout << " Introduce la columna: " << flush;
			cin >> inputColumnaDestino;
			cout << endl;
		} while (inputColumnaDestino <= 0 || inputColumnaDestino > 8);

		if (!turnoBlancas)	
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

void sustituirCasilla(char tablero[LADO][LADO], Posicion posOrigen, Posicion posDestino)
{
	char pieza = tablero[posOrigen.fila][posOrigen.columna];
	tablero[posOrigen.fila][posOrigen.columna] = '*';
	tablero[posDestino.fila][posDestino.columna] = pieza;
}

bool juegoAcabado(char tablero[LADO][LADO])
{
	int totalBlancas = 0;
	int totalNegras = 0;
	Posicion posReyBlancas;
	Posicion posReyNegras;
	bool reyBlancas = false;
	bool reyNegras = false;

	for (int i = 0; i < LADO; i++) {
		for (int j = 0; j < LADO; j++) {
			char pieza = tablero[i][j];
			if (pieza == 'K') {
				reyBlancas = true;
				posReyBlancas = { i, j };
			}
			else if (pieza == 'k') {
				reyNegras = true;
				posReyNegras = { i, j };
			}

			if (isupper(pieza)) totalBlancas++;
			if (islower(pieza)) totalNegras++;
		}
	}

	//Si algun rey falta se termina la partida
	if (!reyBlancas || !reyNegras) return true;

	//En caso de que este el rey solo, se termina partida (rey negro)
	if (totalNegras == 1) {
		cout << "Ganan blancas." << endl;
		return true;
	}

	//En caso de que este el rey solo, se termina partida (rey blanco)
	if (totalBlancas == 1) {
		cout << "Ganan negras." << endl;
		return true;
	}

	return false;
}

void mostrarTurno(bool turnoBlancas) {
	cout << endl;
	if (turnoBlancas) {
		cout << "Turno de las BLANCAS (piezas en MAYUSCULA)" << endl;
	}
	else {
		cout << "Turno de las NEGRAS (piezas en minuscula)" << endl;
	}
	cout << endl;
}