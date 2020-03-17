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

	cambiarColor(); //Volver a poner fondo negro
}


void dibujar1_3(const tMina& mina) {
	tPlanoCaracteres caracteresPlano;
	tPlanoColores coloresPlano;
	int subI = 0, subJ = 0;

	for (int i = 0; i < mina.nFilas; i++) {
		for (int j = 0; j < mina.nColumnas; j++) {
			dibujar3x3(mina.planoMina[i][j], caracteresPlano, coloresPlano, subI, subJ);
			subJ = subJ + 3; //Aumenta el indice de 3 en 3 para compensar el tamaño de la matriz
		}
		subJ = 0; //Pone las columnas a 0 para empezar en la siguiente fila
		subI = subI + 3;
	}

	system("cls");

	for (int i = 0; i < mina.nFilas*3; i++) {
		for (int j = 0; j < mina.nColumnas*3; j++) {
			cambiarColor(coloresPlano[i][j]);
			cout << setw(2) << caracteresPlano[i][j];
		}

		cout << endl; //Salto a la siguiente fila
	}

	cambiarColor(); //Volver a poner fondo negro
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
		case MURO:
			s = "XXXXXXXXX";
			break;
		case TIERRA:
			s = ".........";
			break;
		case LIBRE:
			s = "         ";
			break;
		case PIEDRA:
			s = "@@@@@@@@@";
			break;
	}

	for (int k = 0; k < 3; k++) {
		for (int z = 0; z < 3; z++) {
			caracteres[i + k][j + z] = s[cont];
			colores[i + k][j + z] = colorCasilla(casilla);
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


int colorCasilla(tCasilla c) {
	//4 por defecto para libre, tierra, piedra, muro y dinamita
	int color = 4;

	switch (c) {
		case GEMA:
			color = 2;
			break;
		case SALIDA:
			color = 1;
			break;
		case MINERO:
			color = 7;
			break;
		case DINAMITA:
			color = 2;
			break;
	}

	return color;
}
