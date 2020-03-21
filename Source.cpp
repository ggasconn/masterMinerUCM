#include <iostream>

#include "mina.h"
#include "juego.h"

using namespace std;

int main() {
	tJuego juego;
	short int nivel = 1;
	int opcion = -1;

	do {
		if (!cargarJuego(juego, nivel)) {
			juego.gameOver = true;
		}else {
			opcion = menuMovimientos();

			switch (opcion) {
				case 1:
					do {
						dibujar(juego);
						hacerMovimiento(juego, leerTecla());
					} while (!juego.siguienteNivel && !juego.gameOver);

					if (juego.siguienteNivel && nivel < 4) {
						opcion = menuSiguienteNivel();

						if (opcion == 1) {
							nivel++;
						}
						else {
							juego.gameOver = true;
						}
					}
					
					break;

				case 2:
					//Codificar jugada por fichero
					break;

				case 0:
					juego.gameOver = true;
					break;
			}
		}
	} while (!juego.gameOver && nivel <= 4);

	cout << endl << "G A M E   O V E R !" << endl;

	return 0;
}