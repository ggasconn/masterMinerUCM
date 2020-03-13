/*
	Contiene los tipos y prototipos de las funciones relacionadas con la mina
*/
#ifndef mina_h
#define mina_h

#include <fstream>

using namespace std;

// Definicion de nuevos tipos de datos

typedef enum tCasilla { LIBRE, TIERRA, GEMA, PIEDRA, MURO, SALIDA, MINERO, DINAMITA };

const int MAX = 50;
typedef tCasilla tPlano[MAX][MAX];

typedef struct {
	tPlano planoMina;
	int fila;
	int columna;
	int nFilas; 
	int nColumnas;
} tMina;

typedef char tPlanoCaracteres[3 * MAX][3 * MAX];
typedef int tPlanoColores[3 * MAX][3 * MAX];


// Definicion de prototipos de funciones

/*
* Carga una nueva partida desde un fichero
*
* @param ifstream fichero, contiene el fichero con la partida a cargar
* @param mina, struct con la matriz de la mina y datos necesarios
*/
void cargarMina(ifstream& fichero, tMina& mina);

/*
* Dibuja el tablero en escala 1:1
*
* @param mina, struct con la matriz de la mina y datos necesarios
*/
void dibujar1_1(const tMina& mina);

/*
* Dibuja el tablero en escala 1:3
*
* @param mina, struct con la matriz de la mina y datos necesarios
*/
void dibujar1_3(const tMina& mina);

/*
* Dibuja la casilla aumentada, añadiendo caracteres y colores en la coordenada ixj
*
* @param
* @param
* @param
* @param
* @param
*/
void dibujar3x3(tCasilla casilla, tPlanoCaracteres caracteres, tPlanoColores colores, int i, int j);

/*
* HELPER. Devuelve el codigo de color de fondo acorde al caracter
*
* @param c, caracter a colorear
*/
int colorCaracter(char c);


#endif	//Fin codigo modulo mina