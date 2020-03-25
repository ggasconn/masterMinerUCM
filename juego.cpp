#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "juego.h"

using namespace std;


bool cargarJuego(tJuego& juego, int nivel) {
	bool cargado = false;
	int escalaJuego = 0;
	string nombreFichero = to_string(nivel) + ".txt";
	ifstream fichero;

	fichero.open(nombreFichero);

	if (!fichero.is_open()) {
		cout << ">>> ERROR: No se pudo abrir el fichero" << endl;
	}else {
		cargarMina(fichero, juego.estadoMina);
		escalaJuego = menuModoJuego();
		if (!escalaJuego == 0) {
			juego.escalaJuego = escalaJuego;
			juego.siguienteNivel = false;
			fichero.close();
			cargado = true;
		}
	}

	return cargado;
}


bool cargarMovimientos(tJuego& juego) {
	ifstream fichero;
	string nombreFichero;
	char movimiento;
	bool cargado = false;

	cout << endl  << ">>> Introduce el nombre del fichero con los movimientos: ";
	cin >> nombreFichero;

	fichero.open(nombreFichero);

	if (!fichero.is_open()) {
		cout << endl  << ">>> ERROR: No se pudo abrir el fichero " << nombreFichero << ". Compruebe el nombre y ruta" << endl;
	}
	else {
		do {
			dibujar(juego); // Dibujar el tablero  actualizdo

			fichero.get(movimiento); // Leer siguiente caracter del fichero

			switch (movimiento) {
				case 'A':
					hacerMovimiento(juego, ARRIBA);
					break;
				case 'Z':
					hacerMovimiento(juego, ABAJO);
					break;
				case 'N':
					hacerMovimiento(juego, IZQA);
					break;
				case 'M':
					hacerMovimiento(juego, DCHA);
					break;
				default:
					hacerMovimiento(juego, NADA);
					break;
			}
		} while (!fichero.fail());

		fichero.close();
		cargado = true;
	}

	return cargado;
}


void dibujar(const tJuego& juego) {
	if (juego.escalaJuego == 1)
		dibujar1_1(juego.estadoMina);
	else
		dibujar1_3(juego.estadoMina);

	cout << endl << "Dinamitas:" << juego.nDinamitas << endl;
	cout << "Gemas:" << juego.gemas << endl;
	cout << "Movimientos:" << juego.nMovimientos << endl;
}


/*
* MENUS DE INTERACCION CON EL USUARIO 
*/
int menuModoJuego() {
	int opcion = -1;

	system("cls");
	cout << "1.- Jugar partida a escala 1:1" << endl;
	cout << "2.- Jugar partida a escala 1:3" << endl;
	cout << "0.- Salir" << endl;

	do {
		cout << "Introduce una opcion: ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 2);

	return opcion;
}


int menuMovimientos() {
	int opcion = -1;

	system("cls");
	cout << "Como quieres introducir los movimientos?" << endl;
	cout << "1.- Teclado" << endl;
	cout << "2.- Fichero" << endl;
	cout << "0.- Salir" << endl;

	do {
		cout << "Introduce una opcion: ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 2);

	return opcion;
}


int menuSiguienteNivel() {
	int opcion = -1;

	system("cls");
	cout << "1.- Jugar siguiente nivel" << endl;
	cout << "0.- Salir" << endl;

	do {
		cout << "Introduce una opcion: ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 1);

	return opcion;
}


tTecla leerTecla() {
	tTecla tecla = NADA;
	int codigo;
	cin.sync();

	codigo = _getch();

	if (codigo == 0xe0) {
		codigo = _getch();

		switch (codigo) {
			case 72:
				tecla = ARRIBA;
				break;

			case 80:
				tecla = ABAJO;
				break;

			case 77:
				tecla = DCHA;
				break;

			case 75:
				tecla = IZQA;
				break;
			}
	}
	else if (codigo == 27){
		tecla = SALIR;
	}
	else if (codigo == 32) {
		tecla = TNT;
	}
	else {
		tecla = NADA;
	}

	return tecla;
}


/*
* MOVIMIENTOS Y FUNCIONALIDAD EN ELLOS
*/
bool hacerMovimiento(tJuego& juego, tTecla tecla) {
	bool realizado = false;

	switch (tecla) {
		case ARRIBA:
			movimientoArriba(juego);
			realizado = true;
			break;

		case ABAJO:
			movimientoAbajo(juego);
			realizado = true;
			break;

		case DCHA:
			movimientoDerecha(juego);
			realizado = true;
			break;

		case IZQA:
			movimientoIzquierda(juego);
			realizado = true;
			break;

		case SALIR:
			realizado = true;
			juego.gameOver = true;
			break;

		case NADA:
			break;

		case TNT:
			lanzarDinamita(juego);
			realizado = true;
			break;
	}

	return realizado;
}


void movimientoArriba(tJuego& juego) {
	if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] != MURO && juego.estadoMina.fila - 1 >= 0) {
		if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == LIBRE || juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == TIERRA || juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == GEMA) {
			// Sumar si es gema
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == GEMA) {
				juego.gemas++;
			}

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;
			juego.estadoMina.fila--;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == SALIDA) {
			juego.siguienteNivel = true;
		}
	}
	juego.nMovimientos++;
}


void movimientoAbajo(tJuego& juego) {
	if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] != MURO && juego.estadoMina.fila + 1 < juego.estadoMina.nFilas) {
		if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == LIBRE || juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == TIERRA || juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == GEMA) {
			if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == GEMA) {
				juego.gemas++;
			}

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;

			// Gravedad piedra
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
				gravedadVertical(juego, juego.estadoMina.fila - 1);
			}

			juego.estadoMina.fila++;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == SALIDA) {
			juego.siguienteNivel = true;
		}
	}
	juego.nMovimientos++;
}


void movimientoDerecha(tJuego& juego) {
	if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] != MURO && juego.estadoMina.columna + 1 < juego.estadoMina.nColumnas) {
		if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == LIBRE || juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == TIERRA || juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == GEMA) {
			// Sumar gemas si hay
			if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == GEMA) {
				juego.gemas++;
			}

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;

			// Gravedad piedra
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
				gravedadVertical(juego, juego.estadoMina.fila - 1);
			}

			juego.estadoMina.columna++;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 2] == LIBRE && juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == PIEDRA) {
			// Empujar piedra
			gravedadHorizontal(juego, juego.estadoMina.columna + 2);

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;

			// Gravedad piedra
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
				gravedadVertical(juego, juego.estadoMina.fila - 1);
			}

			juego.estadoMina.columna++;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == SALIDA) {
			juego.siguienteNivel = true;
		}
	}
	juego.nMovimientos++;
}


void movimientoIzquierda(tJuego& juego) {
	if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] != MURO && juego.estadoMina.columna - 1 >= 0) {
		if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == LIBRE || juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == TIERRA || juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == GEMA) {
			// Sumar gemas si hay
			if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == GEMA) {
				juego.gemas++;
			}

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;

			// Gravedad piedra
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
				gravedadVertical(juego, juego.estadoMina.fila - 1);
			}

			juego.estadoMina.columna--;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 2] == LIBRE && juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == PIEDRA) {
			// Empujar piedra
			gravedadHorizontal(juego, juego.estadoMina.columna - 2);

			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;

			// Gravedad piedra
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
				gravedadVertical(juego, juego.estadoMina.fila - 1);
			}

			juego.estadoMina.columna--;
			juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
		}
		else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == SALIDA) {
			juego.siguienteNivel = true;
		}
	}
	juego.nMovimientos++;
}


void lanzarDinamita(tJuego& juego) {
	int columna = juego.estadoMina.columna, fila = juego.estadoMina.fila;

	do {
		fila++;
	} while (juego.estadoMina.planoMina[fila][columna] == LIBRE && fila < juego.estadoMina.nFilas - 1);

	juego.estadoMina.planoMina[fila - 1][columna] = DINAMITA;

	dibujar(juego);

	for (int i = fila - 2; i < fila + 1; i++) {
		for (int j = columna - 1; j < columna + 2; j++) {
			if (juego.estadoMina.planoMina[i][j] == MINERO) {
				juego.gameOver = true;
				juego.siguienteNivel = true;
			}

			juego.estadoMina.planoMina[i][j] = LIBRE;
		}
	}

	// Comprobar si han quedado objetos arriba que puedan caer por gravedad
	gravedadDinamita(juego, fila - 3, columna - 1);
	gravedadDinamita(juego, fila - 3, columna);
	gravedadDinamita(juego, fila - 3, columna + 1);

	juego.nDinamitas++;
}


/*
* EMULACION DE LA GRAVEDAD EN AMBOS SENTIDOS
*/
void gravedadHorizontal(tJuego &juego, int columna) {
	int fila = juego.estadoMina.fila;

	do {
		fila++;
	} while (juego.estadoMina.planoMina[fila][columna] == LIBRE && fila < juego.estadoMina.nFilas);

	juego.estadoMina.planoMina[fila - 1][columna] = PIEDRA;
}


void gravedadVertical(tJuego &juego, int fila) {
	if ((juego.estadoMina.planoMina[fila][juego.estadoMina.columna] == PIEDRA \
		|| juego.estadoMina.planoMina[fila][juego.estadoMina.columna] == GEMA) && fila >= 0) {
		int columna = juego.estadoMina.columna, posPiedra = fila;

		do {
			posPiedra++;
		} while (juego.estadoMina.planoMina[posPiedra][columna] == LIBRE && posPiedra < juego.estadoMina.nFilas);

		// TERNARY OPERATOR para decidir si lo que ha caido es una gema o una piedra
		juego.estadoMina.planoMina[posPiedra - 1][columna] = juego.estadoMina.planoMina[fila][columna] == GEMA ? GEMA : PIEDRA;
		juego.estadoMina.planoMina[fila][columna] = LIBRE;

		dibujar(juego); // Actualizar el tablero con la piedra cayendo

		gravedadVertical(juego, fila - 1);
	}
}


void gravedadDinamita(tJuego& juego, int fila, int columna) {
	if ((juego.estadoMina.planoMina[fila][columna] == PIEDRA \
		|| juego.estadoMina.planoMina[fila][columna] == GEMA) && fila >= 0) {
		int posPiedra = fila;

		do {
			posPiedra++;
		} while (juego.estadoMina.planoMina[posPiedra][columna] == LIBRE && posPiedra < juego.estadoMina.nFilas);

		// TERNARY OPERATOR para decidir si lo que ha caido es una gema o una piedra
		juego.estadoMina.planoMina[posPiedra - 1][columna] = juego.estadoMina.planoMina[fila][columna] == GEMA ? GEMA : PIEDRA;
		juego.estadoMina.planoMina[fila][columna] = LIBRE;

		dibujar(juego); // Actualizar el tablero con la piedra cayendo

		gravedadDinamita(juego, fila - 1, columna);
	}
}



/*
* HELPERS
*/
void cambiarColor(int fondo) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (fondo << 4));
}


tCasilla charToEnum(char c) {
	tCasilla output;

	switch (c) {
		case ' ':
			output = LIBRE;
			break;
		case 'T':
			output = TIERRA;
			break;
		case 'G':
			output = GEMA;
			break;
		case 'P':
			output = PIEDRA;
			break;
		case 'M':
			output = MURO;
			break;
		case 'S':
			output = SALIDA;
			break;
		case 'J':
			output = MINERO;
			break;
	}

	return output;
}


char enumToChar(tCasilla t) {
	char output;

	switch (t) {
		case LIBRE:
			output = ' ';
			break;
		case TIERRA:
			output = '.';
			break;
		case GEMA:
			output = 'G';
			break;
		case PIEDRA:
			output = '@';
			break;
		case MURO:
			output = 'X';
			break;
		case SALIDA:
			output = 'S';
			break;
		case MINERO:
			output = 'M';
			break;
		case DINAMITA:
			output = 'D';
			break;
	}

	return output;
}