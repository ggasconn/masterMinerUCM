#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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

			ordenarMinas(marcador.arrayClasificacion[marcador.numJugadores]);

			for (int k = marcador.arrayClasificacion[marcador.numJugadores].minasRecorridas; k < 5; k++) {
				marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[k].idMina = 0;
				marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[k].numMovimientos = 0;
				marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[k].numGemas = 0;
				marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[k].numDinamitas = 0;
				marcador.arrayClasificacion[marcador.numJugadores].vMinasRecorridas[k].puntosMina = 0;
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
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].idMina << " ";
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numMovimientos << " ";
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numGemas << " ";
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].numDinamitas << " ";
				fichero << marcador.arrayClasificacion[i].vMinasRecorridas[j].puntosMina << endl;
			}
		}

		fichero << "000";

		guardado = true;
	}

	fichero.close();

	return guardado;
}


void mostrarMinasUsuario(const tPuntuaciones& marcador, int cont) {
	cout << setw(12) << endl << marcador.arrayClasificacion[cont].nombre;
	cout << setw(15) << " Movimientos";
	cout << setw(8) << "Gemas";
	cout << setw(12) << "Dinamitas";
	cout << setw(10) << "Puntos";
	cout << setw(18) << "Puntos en total" << endl;

	for (int i = 0; i < marcador.arrayClasificacion[cont].minasRecorridas; i++) {
		cout << setw(9) << "Mina " << marcador.arrayClasificacion[cont].vMinasRecorridas[i].idMina << " ";
		cout << setw(13) << marcador.arrayClasificacion[cont].vMinasRecorridas[i].numMovimientos << " ";
		cout << setw(8) << marcador.arrayClasificacion[cont].vMinasRecorridas[i].numGemas << " ";
		cout << setw(9) << marcador.arrayClasificacion[cont].vMinasRecorridas[i].numDinamitas << " ";
		cout << setw(11) << marcador.arrayClasificacion[cont].vMinasRecorridas[i].puntosMina << " ";
		if (i == 0) cout << setw(14) << marcador.arrayClasificacion[cont].puntTotal << endl;  else cout << endl;
	}
}


void mostrarAlfabetico(const tPuntuaciones& marcador) {
	cout << setw(40) << endl << "-----  LISTA DE JUGADORES  -----" << endl << endl;

	for (int i = 0; i < marcador.numJugadores; i++) {
		cout << setw(30) << marcador.arrayClasificacion[i].nombre << " ";
		cout << marcador.arrayClasificacion[i].puntTotal << endl;
	}

	cout << endl;
}


void mostrarDatosUsuario(const tPuntuaciones& marcador) {
	cout << setw(60) << "-----  JUGADORES ORDENADOS POR NOMBRE  -----" << endl;

	for (int i = 0; i < marcador.numJugadores; i++) {
		mostrarMinasUsuario(marcador, i);
		cout << endl;
	}
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
		newArr[i] = marcador.arrayClasificacion[i];
	}

	delete [] marcador.arrayClasificacion;

	marcador.arrayClasificacion = newArr;
	marcador.capacidad *= 2;
}


void destruir(tPuntuaciones& marcador) {
	delete [] marcador.arrayClasificacion;
	marcador.capacidad = 0;
	marcador.numJugadores = 0;
}


void buscar(const string& nombre, const tPuntuaciones& marcador, int& pos, int ini, int fin, bool& encontrado) {
	int mitad;

	mitad = (ini + fin) / 2;

	if (ini <= fin) {
		if (nombre == marcador.arrayClasificacion[mitad].nombre) {
			encontrado = true;
			pos = mitad;
		}
		else if (nombre < marcador.arrayClasificacion[mitad].nombre)
			buscar(nombre, marcador, pos, ini, mitad - 1, encontrado);
		else
			buscar(nombre, marcador, pos, mitad + 1, fin, encontrado);
	}
}


void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	// Comprueba si la capacidad del array es menor que el numero de jugadores mas el nuevo
	if (marcador.capacidad == marcador.numJugadores)
		aumentarCapacidad(marcador);
	
	int cont = 0;
	bool insertado = false;

	for (int i = marcador.capacidad - 1; i > 0; i--) {
		marcador.arrayClasificacion[i] = marcador.arrayClasificacion[i - 1];
	}

	marcador.arrayClasificacion[0].minasRecorridas = 0;
	marcador.arrayClasificacion[0].puntTotal = 0;
	marcador.arrayClasificacion[0].nombre = nombre;

	for (int i = 0; i < 5; i++) {
		marcador.arrayClasificacion[0].vMinasRecorridas[i].idMina = 0;
		marcador.arrayClasificacion[0].vMinasRecorridas[i].numMovimientos = 0;
		marcador.arrayClasificacion[0].vMinasRecorridas[i].numGemas = 0;
		marcador.arrayClasificacion[0].vMinasRecorridas[i].numDinamitas = 0;
		marcador.arrayClasificacion[0].vMinasRecorridas[i].puntosMina = 0;
	}

	marcador.numJugadores++;
	ordenarNombres(marcador);
}


void ordenarNombres(tPuntuaciones& marcador) {
	tPuntuacionJugador temp;

	for (int i = 0; i < marcador.numJugadores; i++) {
		for (int j = i; j < marcador.numJugadores; j++) {
			if (marcador.arrayClasificacion[i].nombre > marcador.arrayClasificacion[j].nombre) {
				temp = marcador.arrayClasificacion[i];
				marcador.arrayClasificacion[i] = marcador.arrayClasificacion[j];
				marcador.arrayClasificacion[j] = temp;
			}
		}
	}
}


void ordenarMinas(tPuntuacionJugador& jugador) {
	tDatosMina temp;

	for (int i = 0; i < jugador.minasRecorridas; i++) {
		for (int j = i; j < jugador.minasRecorridas; j++) {
			if (jugador.vMinasRecorridas[i].idMina > jugador.vMinasRecorridas[j].idMina) {
				temp = jugador.vMinasRecorridas[i];
				jugador.vMinasRecorridas[i] = jugador.vMinasRecorridas[j];
				jugador.vMinasRecorridas[j] = temp;
			}
		}
	}
}


void inicializarPuntuaciones(tPuntuaciones& marcador, string& nombreJugador, int& pos) {
	bool encontrado = false;

	inicializarMarcador(marcador);
	cargarMarcador(marcador);

	cout << "SEGUNDA PARTE DE LA PRÁCTICA DEL MINERO" << endl << endl;
	cout << setw(50) << "Introduce tu nombre de jugador/a: ";
	cin >> nombreJugador;

	buscar(nombreJugador, marcador, pos, 0, marcador.numJugadores, encontrado);

	if (encontrado) {
		cout << endl << setw(35) << "Ya estás registrado/a." << endl << endl;
		cout << setw(66) << "Mira las minas que has recorrido ordenadas por nivel." << endl;
		mostrarMinasUsuario(marcador, pos);
	}else {
		cout << endl << setw(21) << "Eres nuevo/a: " << nombreJugador << endl << endl;
		cout << setw(52) << "Mira las puntuaciones de los otros jugadores." << endl;
		mostrarAlfabetico(marcador);
		insertar(marcador, nombreJugador, pos);
	}
}