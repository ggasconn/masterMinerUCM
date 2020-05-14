/*
	Contiene los tipos y prototipos de las funciones relacionadas con las puntuaciones
*/
#ifndef puntuaciones_h
#define puntuaciones_h

#include <string>

using namespace std;


// Definicion de nuevos tipos de datos

const int NUM_TOTAL_PLAYERS = 25;
const int NUM_TOTAL_MINAS = 5;

const short int A = 10;
const short int B = 2;

typedef struct {
	int idMina;
	int numMovimientos = 0;
	int numGemas;
	int numDinamitas;
	int puntosMina;
} tDatosMina;

typedef struct {
	string nombre = "";
	int puntTotal;
	int minasRecorridas;
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS];
} tPuntuacionJugador;

typedef struct {
	int capacidad = 2;
	int numJugadores = 0;
	tPuntuacionJugador* arrayClasificacion; // Array dinamico
} tPuntuaciones;


// Definicion de prototipos de funciones

// Funciones del modulo
/*
*
*/
bool cargarMarcador(tPuntuaciones& marcador);

/*
*
*/
bool guardarMarcador(tPuntuaciones& marcador);

/*
*
*/
void mostrarMinasUsuario(const tPuntuaciones& marcador, int cont);

/*
*
*/
void mostrarAlfabetico(const tPuntuaciones& marcador);

/*
*
*/
void mostrarDatosUsuario(const tPuntuaciones& marcador);

/*
*
*/


// Helpers para el array dinamico
/*
*
*/
void inicializarMarcador(tPuntuaciones& marcador);

/*
*
*/
void aumentarCapacidad(tPuntuaciones& marcador);

/*
*
*/
void destruir(tPuntuaciones& marcador);

/*
*
*/
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

/*
*
*/
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);


#endif
