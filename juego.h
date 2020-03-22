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
	int gemas = 0;
	int nMovimientos = 0;
	int nDinamitas = 0;
	int escalaJuego;
	bool gameOver = false;
	bool siguienteNivel = true;
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
* Menu para elegir el modo de juego
*/
int menuModoJuego();


/*
* Menu para elegir como introducir los movimientos
*/
int menuMovimientos();


/*
* Menu para elegir si seguir jugando o salir del juego
*/
int menuSiguienteNivel();


/*
* Devuele la tecla pulsada por el usuario
*/
tTecla leerTecla();


/*
* TODO
*
* @param juego, matriz con los datos del juego
* @param tecla, tecla pulsada clasificada previamente
*/
bool hacerMovimiento(tJuego &juego, tTecla tecla);

void movimientoArriba(tJuego& juego);
void movimientoAbajo(tJuego& juego);
void movimientoDerecha(tJuego& juego);
void movimientoIzquierda(tJuego& juego);
void lanzarDinamita(tJuego& juego);

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
* HELPER. Convierte un dato del tipo tCasilla a su respectivo char
*
* @param c, caracter a convertir en tipo enumerado
*/
char enumToChar(tCasilla t);


/*
* HELPER. Cambiar el color de fondo de la consola. 0 vuelve a negro.
*
* @param fondo, color con el que se dibujara el fondo
*/
void cambiarColor(int fondo = 0);


/*
* TODO
*
* @param juego, datos completos del juego
*/
void gravedadVertical(tJuego& juego, int fila);


/*
* TODO
*
* @param juego, datos completos del juego
*/
void gravedadHorizontal(tJuego& juego, int columna);

#endif	//Fin codigo modulo juego
