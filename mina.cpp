#include <iostream>

#include "mina.h"
#include "juego.h"

using namespace std;

void cargarMina(ifstream& fichero, tMina& mina) {
	char temp;

	// Procesar fichero
	fichero >> mina.nFilas;
	fichero >> mina.nColumnas;
	fichero.ignore(); //Salta el espacio despues del tamaño de la matriz

	for (int i = 0; i < mina.nFilas; i++) {
		for (int j = 0; j < mina.nColumnas; j++) {
			fichero >> noskipws >> temp; //noskipws permite leer espacios en blanco
			mina.planoMina[i][j] = charToEnum(temp);
		}
		fichero.ignore();
	}
}

void dibujar1_1(const tMina& mina) {
	for (int i = 0; i < mina.nFilas; i++) {
		for (int j = 0; j < mina.nColumnas; j++) {
			cout << " " << enumToString(mina.planoMina[i][j]) << " ";
		}

		cout << endl; //Salto a la siguiente fila
	}
}

void dibujar1_3(const tMina& mina) {
}

void dibujar3x3(tCasilla casilla, tPlanoCaracteres caracteres, tPlanoColores colores, int i, int j) {
}