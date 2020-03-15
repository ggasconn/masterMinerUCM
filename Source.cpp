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
			cout << ">>> No se puede seguir jugando!" << endl;
			juego.gameOver = true;
		}else {
			opcion = menuMovimientos();

			if (opcion != 1) {
				//Codificar jugada por fichero
			}else {
				do {
					dibujar(juego);
					hacerMovimiento(juego, leerTecla());
				} while (!juego.siguienteNivel);

				opcion = menuSiguienteNivel();

				if (opcion == 1)
					nivel++;
				else
					juego.gameOver = true;
			}
		}
	} while (!juego.gameOver);

	cout << "G A M E   O V E R !" << endl;

	return 0;
}