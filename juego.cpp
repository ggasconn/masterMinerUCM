#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "juego.h"

using namespace std;


bool cargarJuego(tJuego& juego, int nivel) {
	bool cargado = true;
	string nombreFichero = to_string(nivel) + ".txt";
	ifstream fichero;

	fichero.open(nombreFichero);

	if (!fichero.is_open()) {
		cout << ">>> ERROR: No se pudo abrir el fichero" << endl;
	}
	else {
		cargarMina(fichero, juego.estadoMina);
		juego.escalaJuego = 1; // CAMBIAR Y PREGUNTAR AL USUARIO
		juego.siguienteNivel = false;
		cargado = true;
	}

	return cargado;
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


bool hacerMovimiento(tJuego& juego, tTecla tecla) {
	bool realizado = false;

	switch (tecla)
	{
		case ARRIBA:
			if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] != MURO) {
				if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == PIEDRA) {
					//IMPLEMENTAR SI HAY UNA PIEDRA
				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == LIBRE \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == TIERRA \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna] == GEMA) {
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;
					juego.estadoMina.fila--;
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;

					if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] == GEMA) juego.gemas++;

				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila - 1][juego.estadoMina.columna]) {
					juego.siguienteNivel = true;
				}
			}
			juego.nMovimientos++;
			realizado = true;
			break;
		case ABAJO:
			if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] != MURO) {
				if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == PIEDRA) {
					//IMPLEMENTAR SI HAY UNA PIEDRA
				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == LIBRE \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == TIERRA \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna] == GEMA) {
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;
					juego.estadoMina.fila++;
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;

					if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] == GEMA) juego.gemas++;

				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila + 1][juego.estadoMina.columna]) {
					juego.siguienteNivel = true;
				}
			}
			juego.nMovimientos++;
			realizado = true;
			break;
		case DCHA:
			if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] != MURO) {
				if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == PIEDRA \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == LIBRE \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == TIERRA \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == GEMA) {
					if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 2] == LIBRE) {
						//CREAR GRAVEDAD Y REVISAR TODO
						juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 2] = PIEDRA;
					}
					if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == GEMA) {
						juego.gemas++;
					}

					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;
					juego.estadoMina.columna++;
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna + 1] == SALIDA) {
					juego.siguienteNivel = true;
				}
			}
			juego.nMovimientos++;
			realizado = true;
			break;
		case IZQA:
			if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] != MURO) {
				if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == PIEDRA) {
					//IMPLEMENTAR SI HAY UNA PIEDRA
				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == LIBRE \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == TIERRA \
					|| juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == GEMA) {
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = LIBRE;
					juego.estadoMina.columna--;
					juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna] = MINERO;
					if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1] == GEMA) juego.gemas++;

				}
				else if (juego.estadoMina.planoMina[juego.estadoMina.fila][juego.estadoMina.columna - 1]) {
					juego.siguienteNivel = true;
				}
			}
			juego.nMovimientos++;
			realizado = true;
			break;
		case SALIR:
			realizado = true;
			juego.gameOver = true;
			break;
		case NADA:
			break;
		case TNT:
			realizado = true;
			break;
	}

	return realizado;
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


void cambiarColor(int fondo){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (fondo << 4));
}
