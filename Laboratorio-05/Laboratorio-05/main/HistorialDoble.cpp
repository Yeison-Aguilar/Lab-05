#include "HistorialDoble.h"

namespace EIF201 {

	HistorialDoble::HistorialDoble() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

	HistorialDoble::HistorialDoble() {

		NodoHistorial* actual = cabeza;

		while (actual != nullptr) {
			NodoHistorial* temp = actual->siguiente;
			delete actual;
			actual = temp;
		}
		cabeza = nullptr;
		cola = nullptr;
		std::cout << "[HitorialDoble destruido]" << std::endl;
	}
	
	void HistorialDoble::insertarAlInicio(const std::string& cancion) {
		NodoHistorial* nuevo = new NodoHistorial(cancion);

		if (cabeza == nullptr) {
			cabeza = nuevo;
			cola = nuevo;
		}
		else {
			nuevo->siguiente = cabeza;
			cabeza->anterior = nuevo;
			cabeza = nuevo;
		}

		cantidad++;
	}
	
	void HistorialDoble::insertarAlFinal(const std::string& cancion) {
		NodoHistorial* nuevo = new NodoHistorial(cancion);

		if (cola == nullptr) {

		}

		
	}

}