#include <string>
#include <iostream>

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
		cargado = true;
	}

	return cargado;
}

bool hacerMovimiento(tJuego& juego, tTecla tecla) {
	return false;
}

void dibujar(const tJuego& juego) {
	if (juego.escalaJuego == 1)
		dibujar1_1(juego.estadoMina);
	else
		dibujar1_3(juego.estadoMina);
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

string enumToString(tCasilla t) {
	string output;

	switch (t) {
		case LIBRE:
			output = " ";
			break;
		case TIERRA:
			output = ".";
			break;
		case GEMA:
			output = "G";
			break;
		case PIEDRA:
			output = "@";
			break;
		case MURO:
			output = "X";
			break;
		case SALIDA:
			output = "S";
			break;
		case MINERO:
			output = "M";
			break;
		case DINAMITA:
			output = "D";
			break;
	}

	return output;
}