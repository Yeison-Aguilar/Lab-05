#ifndef NODO_HISTORIAL_H
#define NODO_HISTORIAL_H
#include <iostream>
#include <string>
using namespace std;
namespace EIF201 {
	struct NodoHistorial {
		string cancion;
		// identificador de la canción
		NodoHistorial* siguiente;
		// apunta al nodo sucesor
		NodoHistorial* anterior;
		// apunta al nodo predecesor
		// Constructor: inicializa el dato y ambos punteros en nullptr
		NodoHistorial(const string& c)
			: cancion(c), siguiente(nullptr), anterior(nullptr) {
			cout << "[NodoHistorial creado:" << c << "]" << endl;
		}
		~NodoHistorial() {
			cout << "[NodoHistorial destruido: "<< cancion << "]" << endl;
		}
	};
} // namespace EIF201
#endif // NODO_HISTORIAL_H