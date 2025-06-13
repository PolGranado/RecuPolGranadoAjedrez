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

//ahce que el jugador eliga una pieza para moverla
void elegirPieza(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posPiezaElegida)
{
	bool posicionValida = false;
	do {

		int inputFila;
		int inputColumna;

		//se le pide la fila
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

		//se le pide la columna
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

		if (turnoBlancas)//verifica que si esta el turno de blancas solo se podran seleccionar turno de las blancas
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
		else//turnod e las negras
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

//se encarga de verificar el movimiento valido
bool gestionarMovimientoValido(char tablero[LADO][LADO], bool turnoBlancas, bool enroques[], bool puedeEnrocar[], Posicion posOrigen, Posicion& posDestino)
{
	//dependera de la pieza seleccionada llamara a su función para verificar si es valido
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

//en casod e ahcer enroque vovleran a su sitio
void gestionarEnroque(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestinoRey, Posicion posDestinoTorre)
{
	//en caso de ser turnod e las blancas
	if (turnoBlancas)
	{
		tablero[posDestinoRey.fila][posDestinoRey.columna] = 'K';
		tablero[posDestinoTorre.fila][posDestinoTorre.columna] = 'T';
	}
	else//turno de las negras
	{
		tablero[posDestinoRey.fila][posDestinoRey.columna] = 'k';
		tablero[posDestinoTorre.fila][posDestinoTorre.columna] = 't';
	}
}

//ejecuta el cambio de roles del peon
void gestionarPromocion(char tablero[LADO][LADO], bool turnoBlancas, Posicion posDestino)
{
	//en casod e que los blancos llegue al final se ejceuta y se convierte en reina 
	if (turnoBlancas)
	{
		tablero[posDestino.fila][posDestino.columna] = 'Q';
	}
	else//si es el peon engro se convertira en la reina negra
	{
		tablero[posDestino.fila][posDestino.columna] = 'q';
	}
}

//verifica si el movimiento del peon es valido
bool movimientoPeon(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	//en caso de ser el turnod e las blancas
	if (turnoBlancas)
	{
		char destino = tablero[posDestino.fila][posDestino.columna];

		//Tenemos un if para verificar que el destino sea un *
		if (destino == '*') {
			//se mueve 1 hacia delante
			if (posOrigen.fila - 1 == posDestino.fila && posOrigen.columna == posDestino.columna)
			{
				//En caso de que llegue al final del tablero (0) se convertira en reina
				if (posDestino.fila == 0)
					gestionarPromocion(tablero, turnoBlancas, posDestino);
				return true;
			}
			//En caso de estar en la fila origial podrmeos mover 2 casillas
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
				//Mira si hay una ficha enemiga en diagonal para matarla
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
	else//en el caso de las negras
	{
		char destino = tablero[posDestino.fila][posDestino.columna];

		//se mueve 1 hacia delante
		if (destino == '*') {
			if (posOrigen.fila + 1 == posDestino.fila &&
				posOrigen.columna == posDestino.columna)
			{
				if (posDestino.fila == LADO - 1)
					gestionarPromocion(tablero, turnoBlancas, posDestino);
				return true;
			}

			//se movera 2 enc asod e estar en la fila correcta
			if (posOrigen.fila == 1 &&
				posDestino.fila == 3 &&
				tablero[2][posOrigen.columna] == '*')
			{
				return true;
			}
		}
		else {
			//Si hay pieza blanca  hacia donde va
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

//Comprueba si la torre se puede mover correctamente
bool movimientoTorre(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{	//en caso de que sea el turno de las blancas
	if (turnoBlancas)
	{	//Solo podria ir a * o a una casilla con una negra
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*':
			//Si se mueve en certical cambia la fila
			if (posDestino.fila != posOrigen.fila)
			{
				//calculamos cuantas filas hay
				int dif_filas = posDestino.fila - posOrigen.fila;

				//Se mira cada casilla por donde ira para ver si es valido el movimiento
				for (int offset = dif_filas > 0 ? dif_filas-1 : dif_filas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila + offset][posOrigen.columna] != '*')
						return false;//si hay algo que no le deja pasar no sera vlaido
				}
			}
			else//si se mueve en horizaontal cmabia columna						
			{
				//lo mismo que tenemos arriba codigo muy similar
				int dif_columnas = posDestino.columna - posOrigen.columna;

				for (int offset = dif_columnas > 0 ? dif_columnas-1 : dif_columnas+1; 
					offset != 0; offset = offset > 0 ? offset - 1 : offset + 1)
				{
					if (tablero[posOrigen.fila][posOrigen.columna + offset] != '*')
						return false;
				}
			}
			

			//devuelve que verdadero si es en filas o columnas solo
			return
				((posOrigen.columna != posDestino.columna) && (posOrigen.fila == posDestino.fila)) ||
				((posOrigen.fila != posDestino.fila) && (posOrigen.columna == posDestino.columna));
			break;

		default:
			break;
		}
	}
	//Turno de las negras, mismo codigo de arriba cambiando perqueñas cosas
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


//Verifica que su movimienta sea valido
bool movimientoCaballo(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	if (turnoBlancas)
	{//Puede ir a casillas * o a ocupadas si es del enemigo para amtarlo
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 't':
		case 'h':
		case 'b':
		case 'q':
		case 'k':
		case 'p':
		case '*':

			//Mira las 8 posibles movimientso en todas direcciones
			return
				((posOrigen.columna + 1 == posDestino.columna) && (posOrigen.fila - 2 == posDestino.fila)) ||	//arriba 2, derecha 1
																	
				((posOrigen.columna - 1 == posDestino.columna) && (posOrigen.fila - 2 == posDestino.fila)) ||	//arriba 2, izquierda 1		
																	
				((posOrigen.columna - 1 == posDestino.columna) && (posOrigen.fila + 2 == posDestino.fila)) ||	//abajo 2, izquierda 1		
				
				((posOrigen.columna + 1 == posDestino.columna) && (posOrigen.fila + 2 == posDestino.fila)) ||	//abajo 2, derecha 1		
								
				((posOrigen.columna + 2 == posDestino.columna) && (posOrigen.fila - 1 == posDestino.fila)) ||	//derecha 2, arriba 1															

				((posOrigen.columna + 2 == posDestino.columna) && (posOrigen.fila + 1 == posDestino.fila)) ||	//derecha 2, abajo 1		

				((posOrigen.columna - 2 == posDestino.columna) && (posOrigen.fila - 1 == posDestino.fila)) ||	//izquierda 2, arriba 1		
				 
				((posOrigen.columna - 2 == posDestino.columna) && (posOrigen.fila + 1 == posDestino.fila)); 	//izquierda 2, abajo 1		

			break;

		default:
			break;
		}
	}

	else {
		//Logica del caballo  negro que peude hacer lo mismo que el blanco ir a * o capturar fichas enemigas
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
		case '*':

			//Comprueva lo mismo que en el blanco
			return
				((posOrigen.columna + 1 == posDestino.columna) && (posOrigen.fila - 2 == posDestino.fila)) ||			

				((posOrigen.columna - 1 == posDestino.columna) && (posOrigen.fila - 2 == posDestino.fila)) ||			

				((posOrigen.columna - 1 == posDestino.columna) && (posOrigen.fila + 2 == posDestino.fila)) ||			

				((posOrigen.columna + 1 == posDestino.columna) && (posOrigen.fila + 2 == posDestino.fila)) ||			
																	
				((posOrigen.columna + 2 == posDestino.columna) && (posOrigen.fila - 1 == posDestino.fila)) ||			
																				
				((posOrigen.columna + 2 == posDestino.columna) && (posOrigen.fila + 1 == posDestino.fila)) ||			
																	
				((posOrigen.columna - 2 == posDestino.columna) && (posOrigen.fila - 1 == posDestino.fila)) ||			
																	 
				((posOrigen.columna - 2 == posDestino.columna) && (posOrigen.fila + 1 == posDestino.fila)); 			
																	
			break;

		default:
			break;
		}
	}
	//Si ningun movimientoe s valido devuelve false
	return false;
}

bool movimientoAlfil(char tablero[LADO][LADO], bool turnoBlancas, Posicion posOrigen, Posicion posDestino)
{
	//en caso de que sea el turno de las blancas mirara que letra es y con un case hara x cosa
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
			//miramos cuantas casillas se mueve
			int dif_filas = posDestino.fila - posOrigen.fila;
			int dif_columnas = posDestino.columna - posOrigen.columna;

			//Verifica que se mueva en diagonal
			if (abs(dif_filas) != abs(dif_columnas))	
				return false;
			
			//Miramos el camino que hara para ver si es valido y tenerlo
			int offset_filas = dif_filas > 0 ? dif_filas - 1 : dif_filas + 1;
			int offset_columnas = dif_columnas > 0 ? dif_columnas - 1 : dif_columnas + 1;

			//Se recorre cada casilla hasta llegar donde hemos puesto
			for (	; offset_filas != 0 || offset_columnas != 0; 
				offset_filas = offset_filas > 0 ? offset_filas - 1 : offset_filas + 1, 
				offset_columnas = offset_columnas > 0 ? offset_columnas - 1 : offset_columnas + 1)
			{
				//Si alguna casilla no es * no podremos pasar y se quedara ahi
				if (tablero[posOrigen.fila + offset_filas][posOrigen.columna + offset_columnas] != '*')
					return false;
			}

			//Mira si el camino es vvalido en caso de que si, seria valido
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
		//el aflil solo puede matar fichas minusculas  o casillas con *
		switch (tablero[posDestino.fila][posDestino.columna])
		{
		case 'T':
		case 'H':
		case 'B':
		case 'Q':
		case 'K':
		case 'P':
		case '*': {
			//el mismo codigo qque arriba pero con las negras
			int dif_filas = posDestino.fila - posOrigen.fila;
			int dif_columnas = posDestino.columna - posOrigen.columna;

			if (abs(dif_filas) != abs(dif_columnas))	
				return false;
			//se calcula/prepara el camino que se hara
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
			//en caso de un movimiento valido
			return
				(posOrigen.columna != posDestino.columna) &&
				(posOrigen.fila != posDestino.fila);
		}
			break;

		default:
			break;
		}
	}
	//en caso de que nada sea vvalido devuelve falso
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

//Permite al jugador coger una casilla valida para mover las piezas
void elegirMovimiento(char tablero[LADO][LADO], bool turnoBlancas, Posicion* posDestinoElegida)
{
	int inputFilaDestino;
	int inputColumnaDestino;

	bool posicionValida = false;
	do
	{
		//Se le pide la fila en la que esta
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

		//se le pide la columna
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

		//mira si es el turno de las negras con un "si es diferente a turnoBlancas pasamos a este codigo"
		if (!turnoBlancas)	
		{
			//Miramos si es valido la casilla final destino para capturar
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
				//se guarda la posición
				(*posDestinoElegida).fila = LADO - inputFilaDestino;
				(*posDestinoElegida).columna = inputColumnaDestino - 1;
				posicionValida = true;
				break;

			default: break;
			}
		}
		else //turno de las blancas
		{
			//comprovamos que hay enc asilla destino
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

			default: break;//en caso de que ninguno de las opciones se seleccione se quita
			}
		}
	} while (!posicionValida);//Se repetira hasta que sea valido
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
	//Muestra simplemente que le toca a cada uno
	cout << endl;
	if (turnoBlancas) {
		cout << "Turno de las BLANCAS (piezas en MAYUSCULA)" << endl;
	}
	else {
		cout << "Turno de las NEGRAS (piezas en minuscula)" << endl;
	}
	cout << endl;
}