#include <iostream>

#include "mina.h"
#include "juego.h"

using namespace std;

int main() {
	tJuego juego;
	bool salir = false;
	short int nivel = 1;

	do {
		if (!cargarJuego(juego, nivel)) {
			cout << ">>> No se puede seguir jugando!" << endl;
			salir = true;
		}
		else {
			dibujar(juego);
			salir = true;
		}
	} while (!salir);
	return 0;
}