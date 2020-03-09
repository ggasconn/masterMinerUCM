/*
	Contiene los tipos y prototipos de las funciones relacionadas con el juego
*/
#ifndef juego_h
#define juego_h

#include "mina.h"

using namespace std;

// Definicion de nuevos tipos de datos

typedef enum tTecla { ARRIBA, ABAJO, DCHA, IZQA, SALIR, NADA, TNT };

typedef struct {
	tMina estadoMina;
	int gemas;
	int nMovimientos;
	int nDinamitas;
	int escalaJuego;
} tJuego;


// Definicion de prototipos de funciones

/*
* Carga una nueva partida desde un fichero
*
* @param juego, matriz con los datos del juego
* @param nivel, numero con el nivel que se va a cargar
*/
bool cargarJuego(tJuego& juego, int nivel);

/*
* TODO
*
* @param juego, matriz con los datos del juego
* @param tecla, tecla pulsada clasificada previamente
*/
bool hacerMovimiento(tJuego &juego, tTecla tecla);

/*
* TODO
*
* @param juego, matriz con los datos del juego
*/
void dibujar(const tJuego& juego);

/*
* HELPER. Convierte un caracter en un dato del tipo tCasilla
*
* @param c, caracter a convertir en tipo enumerado
*/
tCasilla charToEnum(char c);

/*
* HELPER. Convierte un dato del tipo tCasilla a su respectivo string
*
* @param c, caracter a convertir en tipo enumerado
*/
string enumToString(tCasilla t);

#endif	//Fin codigo modulo juego
