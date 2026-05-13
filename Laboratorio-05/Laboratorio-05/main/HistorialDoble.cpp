#include "HistorialDoble.h"

namespace EIF201 {

	HistorialDoble::HistorialDoble() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

	HistorialDoble::~HistorialDoble() {

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
			cabeza = nuevo;
			cola = nuevo;
		}
		else {
			nuevo->anterior = cola;
			cola->siguiente = nuevo;
			cola = nuevo;
		}
		cantidad++;
		
	}

	void HistorialDoble::insertarEnPosicion(const std::string& cancion, int pos) {

		if (pos <= 0) {
			insertarAlInicio(cancion);
			return;
		}
		if (pos >= cantidad) {
			insertarAlFinal(cancion);
			return;
		}

		NodoHistorial* nuevo = new NodoHistorial(cancion);
		NodoHistorial* actual = cabeza;

		for (int i = 0; i < pos; i++) {
			actual = actual->siguiente;
		}

		NodoHistorial* previo = actual->anterior;
		nuevo->siguiente = actual;
		nuevo->anterior = previo;
		previo->siguiente = nuevo;
		actual->anterior = nuevo;
		cantidad++;
	}

	bool HistorialDoble::insertarAntesDe(const std::string& referencia, const std::string& nueva) {

		NodoHistorial* actual = cabeza;
		while (actual != nullptr) {
			if (actual->cancion == referencia) {
				if (actual == cabeza) {
					insertarAlInicio(nueva);
				}
				else {
					NodoHistorial* nuevo = new NodoHistorial(nueva);
					NodoHistorial* previo = actual->anterior;
					nuevo->siguiente = actual;
					nuevo->anterior = previo;
					previo->siguiente = nuevo;
					actual->anterior = nuevo;
					cantidad++;
				}
				return true;
			}
			
			actual = actual->siguiente;
		}
		return false;
	}

	bool HistorialDoble::insertarDespuesDe(const std::string& referencia, const std::string& nueva) {

		NodoHistorial* actual = cabeza;

		while (actual != nullptr) {
			if (actual->cancion == referencia) {
				if (actual == cola) {
					insertarAlFinal(nueva);
				}
				else {
					NodoHistorial* nuevo = new NodoHistorial(nueva);
					NodoHistorial* sig = actual->siguiente;
					nuevo->anterior = actual;
					nuevo->siguiente = sig;
					actual->siguiente = nuevo;
					sig->anterior = nuevo;
					cantidad++;
				}
				return true;
			}
			actual = actual->siguiente;
		}
		return false;
	}

	bool HistorialDoble::existeCancion(const std::string& cancion) const {

		NodoHistorial* actual = cabeza;

		while (actual != nullptr) {
			if (actual->cancion == cancion) {
				return true;
			}
			actual = actual->siguiente;
		}
		return false;
	}

	int HistorialDoble::obtenerPosicionDesdeElFinal(const std::string& cancion) const {

		NodoHistorial* actual = cola;
		int pos = 0;

		while (actual != nullptr) {
			if (actual->cancion == cancion) {
				return pos;
			}
			actual = actual->anterior;
			pos++;
		}
		return -1;
	}

	bool HistorialDoble::eliminarPrimera(const std::string& cancion) {

		NodoHistorial* actual = cabeza;

		while (actual != nullptr) {
			if (actual->cancion == cancion) {
				if (actual->anterior != nullptr) {
					actual->anterior->siguiente = actual->siguiente;
				}
				else {
					cabeza = actual->siguiente;
				}
				if (actual->siguiente != nullptr) {
					actual->siguiente->anterior = actual->anterior;
				}
				else {
					cola = actual->anterior;
				}

				delete actual;
				actual = nullptr;
				return true;
			}
			actual = actual->siguiente;
		}
		return false;
	}

	bool HistorialDoble::eliminarUltima(const std::string& cancion) {

		NodoHistorial* actual = cola;

		while (actual != nullptr) {
			if (actual->cancion == cancion) {
				if (actual->anterior != nullptr) {
					actual->anterior->siguiente = actual->siguiente;
				}
				else {
					cabeza = actual->siguiente;
				}
				if (actual->siguiente != nullptr) {
					actual->siguiente->anterior = actual->anterior;
				}
				else {
					cola = actual->anterior;
				}
				
				delete actual;
				actual = nullptr;
				cantidad--;
				return true;
			}
			actual = actual->anterior;
		}
		return false;
	}

	bool HistorialDoble::eliminarEnPosicion(int pos) {
		if (pos < 0 || pos >= cantidad) { return false; }
		if (pos == 0) { return eliminarCabeza(); }
		if (pos == cantidad - 1) { return eliminarCola(); }

		NodoHistorial* actual = cabeza;
		for (int i = 0; i < pos; i++) { actual = actual->siguiente;}

		actual->anterior->siguiente = actual->siguiente;
		actual->siguiente->anterior = actual->anterior;
		delete actual;
		actual = nullptr;
		cantidad--;
		return true;
	}
	
}