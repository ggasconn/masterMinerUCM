#include <iostream>

#include "mina.h"
#include "juego.h"

using namespace std;

int main() {
	tJuego juego;
	short int nivel = 1;

	do {
		if (!cargarJuego(juego, nivel)) {
			cout << ">>> No se puede seguir jugando!" << endl;
			juego.gameOver = true;
		}else {
			do {
				dibujar(juego);
				hacerMovimiento(juego, leerTecla());
			} while (!juego.siguienteNivel);
			nivel++;
		}
	} while (!juego.gameOver);

	cout << "G A M E   O V E R !" << endl;

	return 0;
}