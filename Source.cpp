#include <iostream>
#include <iomanip>

#include "mina.h"
#include "juego.h"
#include "puntuaciones.h"

using namespace std;

int main() {
	//TIPOS ANtiguos
	tJuego juego;
	short int nivel = 1;
	int opcion = -1;

	// Tipos nuevos
	tPuntuaciones marcador;
	string nombreJugador;
	int pos, op = -1;
	inicializarMarcador(marcador);
	cargarMarcador(marcador);

	cout << "SEGUNDA PARTE DE LA PRÁCTICA DEL MINERO" << endl << endl;
	cout << setw(50) << "Introduce tu nombre de jugador/a: ";
	cin >> nombreJugador;

	if (buscar(nombreJugador, marcador, pos)) {
		cout << endl << setw(35) << "Ya estás registrado/a." << endl << endl;
		cout << setw(66) << "Mira las minas que has recorrido ordenadas por nivel." << endl;
		mostrarMinasUsuario(marcador, pos);
	}else {
		cout << "Eres nuevo/a: " << nombreJugador << endl << endl;
		cout << "Mira las puntuaciones de los otros jugadores." << endl;
		mostrarAlfabetico(marcador);
		// pos contiene la posicon donde deberia ir ya que se ha llamado a la funcion antes
		insertar(marcador, nombreJugador, pos);
	}

	do {
		do {
			cout << endl << nombreJugador << ", ¿Qué mina quieres explorar?" << endl;
			cout << "Introduce un numero entre 1 y 5 para explorar una mina y 0 para salir: ";
			cin >> op;
		} while (op < 0 || op > 5);

		if (! op == 0) {
			if (cargarJuego(juego, op)) {
				opcion = menuMovimientos();

				switch (opcion) {
				case 1:
					do {
						dibujar(juego);
						hacerMovimiento(juego, leerTecla());
					} while (!juego.siguienteNivel && !juego.gameOver);

					if (juego.siguienteNivel && !juego.gameOver) {
						buscar(nombreJugador, marcador, pos);
						marcador.arrayClasificacion[pos].minasRecorridas++;
						marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].idMina = op;
						marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numDinamitas = juego.nDinamitas;
						marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numMovimientos = juego.nMovimientos;
						marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numGemas = juego.gemas;
					}

					break;

				case 2:
					cargarMovimientos(juego);
					break;

				case 0:
					op = 0;
					break;
				}
			}
		}
	} while (op != 0);
	
	
	destruir(marcador);
	guardarMarcador(marcador);

	return 0;
}