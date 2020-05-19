#include <iostream>
#include <iomanip>
#include <locale>

#include "mina.h"
#include "juego.h"
#include "puntuaciones.h"

using namespace std;

int main() {
	tJuego juego;
	tPuntuaciones marcador;
	string nombreJugador;
	short int nivel = 1;
	int pos = -1, op = -1, opcion = -1;

	setlocale(LC_ALL, "");

	// Inicializa array dinamico, pregunta por el jugador y muestra estadisticas
	inicializarPuntuaciones(marcador, nombreJugador, pos);

	do {
		reiniciarJuego(juego);	// Pone los valores del struct del juego a los valores por defecto

		do {
			cout << endl << nombreJugador << ", ¿Qué mina quieres explorar?" << endl;
			cout << "Introduce un numero entre 1 y 5 para explorar una mina y 0 para salir: ";
			cin >> op;
		} while (op < 0 || op > 5);

		if (! op == 0) {
			if (cargarJuego(juego, op)) {
				opcion = menuMovimientos();	// Pregunta como se quiere jugar

				switch (opcion) {
					case 1:
						do {
							dibujar(juego);
							hacerMovimiento(juego, leerTecla());
						} while (!juego.siguienteNivel && !juego.gameOver);

						break;

					case 2:
						cargarMovimientos(juego);
						break;

					case 0:
						op = 0;
						break;
				}

				// Si el nivel se ha terminado con exito se actualiza o guarda la puntuacion
				if (juego.siguienteNivel && !juego.gameOver) {
					buscar(nombreJugador, marcador, pos);

					if (marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numMovimientos == 0)
						marcador.arrayClasificacion[pos].minasRecorridas++;

					marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].idMina = op;
					marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numDinamitas = juego.nDinamitas;
					marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numMovimientos = juego.nMovimientos;
					marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].numGemas = juego.gemas;
					marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].puntosMina = \
						juego.estadoMina.nColumnas * juego.estadoMina.nFilas + A * juego.gemas - juego.nMovimientos - B * juego.nDinamitas;
					marcador.arrayClasificacion[pos].puntTotal += marcador.arrayClasificacion[pos].vMinasRecorridas[op - 1].puntosMina;

					ordenarMinas(marcador.arrayClasificacion[pos]);
				}
			}
		}

		system("cls");
		cout << setw(66) << endl << "Mira las minas que has recorrido ordenadas por nivel." << endl;
		mostrarMinasUsuario(marcador, pos);
	} while (op != 0);
	
	guardarMarcador(marcador);	// Volcado del array dinamico al fichero
	destruir(marcador);	// Borrado del array dinamico
	
	return 0;
}