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
* Carga los datos del fichero puntuaciones.txt al array dinamico.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
bool cargarMarcador(tPuntuaciones& marcador);

/*
* Guarda los datos del array dinamico en el fichero puntuaciones.txt
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
bool guardarMarcador(tPuntuaciones& marcador);

/*
* Muestra todas las minas del usuario que recibe por el parametro cont.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
* @param cont, posicion en la que se encuentra el usuario en el array
*/
void mostrarMinasUsuario(const tPuntuaciones& marcador, int cont);

/*
* Muestra la puntuacion total de todos los jugadores
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void mostrarAlfabetico(const tPuntuaciones& marcador);

/*
* Muestra todos los datos de las minas recorridas por todos los jugadores
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void mostrarDatosUsuario(const tPuntuaciones& marcador);


// Helpers para el array dinamico
/*
* Inicializa el array dinamico con el tamaño por defecto
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void inicializarMarcador(tPuntuaciones& marcador);

/*
* Duplica la capacidad del array dinamico, volcando todos los datos al nuevo.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void aumentarCapacidad(tPuntuaciones& marcador);

/*
* Elimina el array dinamico del heap
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void destruir(tPuntuaciones& marcador);

/*
* Busca en el array el nombre del jugador, si lo encuentra en pos estará el indice.
*
* @param nombre, nombre del jugador que se va a buscar en el array
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
* @param pos, devuelve la posicion en la que se encuentra el jugador dentro del array
*/
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

/*
* Inserta un nuevo jugador en el array dinamico.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
* @param nombre, nombre del jugador que se va a insertar en el array
* @param pos, posicion en la que se encuentra el jugador dentro del array
*/
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);

/*
* Ordena los jugadores por nombre en el array dinamico.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
*/
void ordenarNombres(tPuntuaciones& marcador);

/*
* Ordena las minas del jugador enviado de menor a mayor.
*
* @param jugador, array con los datos del jugador
*/
void ordenarMinas(tPuntuacionJugador& jugador);

/*
* Inicializa el array dinamico, lee los datos del fichero al array y pregunta
* por el nombre del jugador, si es nuevo lo crea.
*
* @param marcador, array dinamico conteniendo todos los jugadores y sus puntuaciones
* @param nombre, nombre del jugador que se va a insertar en el array
* @param pos, posicion en la que se encuentra el jugador dentro del array
*/
void inicializarPuntuaciones(tPuntuaciones& marcador, string& nombreJugador, int& pos);

#endif
