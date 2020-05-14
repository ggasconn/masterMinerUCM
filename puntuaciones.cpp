#include <iostream>
#include <fstream>
#include <string>

#include "puntuaciones.h"

using namespace std;


// Funciones del modulo

bool cargarMarcador(tPuntuaciones& marcador) {
	bool cargado = false;
	string temp;
	tDatosMina minaTemp;
	
	ifstream fichero;

	fichero.open("Puntuaciones.txt");

	if (fichero.is_open()) {
		fichero >> temp;

		while (temp != "000") {
			// Comprueba si la capacidad del array es menor que el numero de jugadores mas el nuevo
			if (marcador.capacidad == marcador.numJugadores + 1)
				aumentarCapacidad(marcador);

			marcador.arrayClasificacion[marcador.numJugadores].nombre = temp;
			fichero >> marcador.arrayClasificacion[marcador.numJugadores].puntTotal;
			fichero >> marcador.arrayClasificacion[marcador.numJugadores].minasRecorridas;

			for (int i = 0; i < marcador.arrayClasificacion[marcador.numJugadores].minasRecorridas; i++) {
				fichero >> marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[i].idMina;
				fichero >> marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[i].numMovimientos;
				fichero >> marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[i].numGemas;
				fichero >> marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[i].numDinamitas;
				fichero >> marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[i].puntosMina;
			}

			marcador.numJugadores++;
			fichero >> temp;
		}

		cargado = true;
	}

	fichero.close();

	return cargado;
}


bool guardarMarcador(tPuntuaciones& marcador) {
	bool guardado = false;

	ofstream fichero;

	fichero.open("Puntuaciones.txt");

	if (fichero.is_open()) {
		for (int i = 0; i < marcador.numJugadores; i++) {
			fichero << marcador.arrayClasificacion[i].nombre << endl;
			fichero << marcador.arrayClasificacion[i].puntTotal << endl;
			fichero << marcador.arrayClasificacion[i].minasRecorridas << endl;

			for (int j = 0; j < marcador.arrayClasificacion[i].minasRecorridas; j++) {
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].idMina;
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numMovimientos;
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numGemas;
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numDinamitas;
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].puntosMina;
			}
		}

		fichero << "000";

		guardado = true;
	}

	fichero.close();

	return guardado;
}


void mostrarMinasUsuario(const tPuntuaciones& marcador, int cont) {
}


void mostrarAlfabetico(const tPuntuaciones& marcador) {
}


void mostrarDatosUsuario(const tPuntuaciones& marcador) {
}


// Helpers para el array dinamico

void inicializarMarcador(tPuntuaciones& marcador) {
	marcador.capacidad = 2;
	marcador.numJugadores = 0;
	marcador.arrayClasificacion = new tPuntuacionJugador[2];
}


void aumentarCapacidad(tPuntuaciones& marcador) {
	tPuntuacionJugador* newArr = new tPuntuacionJugador[2 * marcador.capacidad];

	for (int i = 0; i < marcador.capacidad; i++) {
		marcador.arrayClasificacion[i] = newArr[i];
	}

	delete [] marcador.arrayClasificacion;

	marcador.arrayClasificacion = newArr;
	marcador.capacidad *= 2;
}


void destruir(tPuntuaciones& marcador) {
	delete[] marcador.arrayClasificacion;
	marcador.capacidad = 0;
	marcador.numJugadores = 0;
}


bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	int ini = 0, fin = marcador.capacidad - 1, mitad;
	bool encontrado = false;

	do {
		mitad = (ini + fin) / 2; // División entera
		if (nombre == marcador.arrayClasificacion[mitad].nombre)
			encontrado = true;
		else if (nombre < marcador.arrayClasificacion[mitad].nombre)
			fin = mitad - 1;
		else
			ini = mitad + 1;
	} while ((ini <= fin) && !encontrado);

	if (encontrado)
		pos = mitad;

	return encontrado;
}


void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	// Comprueba si la capacidad del array es menor que el numero de jugadores mas el nuevo
	if (marcador.capacidad == marcador.numJugadores + 1)
		aumentarCapacidad(marcador);
	
	int cont = 0;
	bool insertado = false;

	pos = buscar(nombre, marcador, pos);

	for (int i = marcador.capacidad; i > pos; i--) {
		marcador.arrayClasificacion[i] = marcador.arrayClasificacion[i - 1];
	}

	marcador.arrayClasificacion[pos].minasRecorridas = 0;
	marcador.arrayClasificacion[pos].puntTotal = 0;
	marcador.arrayClasificacion[pos].nombre = nombre;
}