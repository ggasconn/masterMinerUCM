#include <iostream>
#include <iomanip>

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

			if (temp == 'J') {
				mina.fila = i;
				mina.columna = j;
			}
		}
		fichero.ignore();
	}
}


void dibujar1_1(const tMina& mina) {
	tPlanoCaracteres caracteresPlano;
	tPlanoColores coloresPlano;

	for (int i = 0; i < mina.nFilas; i++) {
		for (int j = 0; j < mina.nColumnas; j++) {
			caracteresPlano[i][j] = enumToChar(mina.planoMina[i][j]);
			coloresPlano[i][j] = colorCaracter(enumToChar(mina.planoMina[i][j]));
		}
	}

	system("cls");

	for (int i = 0; i < mina.nFilas; i++) {
		for (int j = 0; j < mina.nColumnas; j++) {
			cambiarColor(coloresPlano[i][j]);
			cout << setw(2) << caracteresPlano[i][j];
		}

		cout << endl; //Salto a la siguiente fila
	}

	cambiarColor();
}


void dibujar1_3(const tMina& mina) {
}


void dibujar3x3(tCasilla casilla, tPlanoCaracteres caracteres, tPlanoColores colores, int i, int j) {
	string s;
	short int cont = 0;

	switch (casilla) {
		case GEMA:
			s = "GEMA AMA_";
			break;
		case SALIDA:
			s = "SALIDAESC";
			break;
		case MINERO:
			s = "MI--NERO!";
			break;
		case DINAMITA:
			s = "DINAMITA!";
			break;
		default:
			break;
	}

	for (int k = i; k < 4; k++) {
		for (int z = j; z < 4; z++) {
			caracteres[i][j] = s[cont];
			colores[i][j] = colorCaracter(casilla);
			cont++;
		}
	}
}


int colorCaracter(char c) {
	//4 por defecto para libre, tierra, piedra, muro y dinamita
	int color = 4;

	switch (c) {
		case 'G':
			color = 2;
			break;
		case 'S':
			color = 1;
			break;
		case 'M':
			color = 7;
			break;
	}

	return color;
}
