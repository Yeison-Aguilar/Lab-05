#include "RotacionCircular.h"
#include "HistorialDoble.h"
namespace EIF201 {
	RotacionCircular::RotacionCircular()
		: cola(nullptr), cantidad(0) {
	}
	// Método auxiliar privado
	NodoLocutor* RotacionCircular::getCabeza() const {
		return (cola != nullptr) ? cola->siguiente : nullptr;
	}

	RotacionCircular:: ~RotacionCircular() {
		if (cola == nullptr) {
			return;
		}

		NodoLocutor* cabeza = cola->siguiente;
		cola->siguiente = nullptr; // Romper el ciclo antes de liberar
		NodoLocutor* actual = cabeza;
		while (actual != nullptr) {
			NodoLocutor* temp = actual->siguiente;
			delete actual;
			actual = temp;
		}
		cola = nullptr;
		cout << "[RotacionCircular destruida]" << endl;
	}
	void RotacionCircular::insertarAlFinal(const string& nombre)
	{
		NodoLocutor* nuevo = new NodoLocutor(nombre);
		if (cola == nullptr) {
			nuevo->siguiente = nuevo;
			cola = nuevo;
		}
		else {
			nuevo->siguiente = cola->siguiente;
			cola->siguiente = nuevo;
			cola = nuevo;
		}
		cantidad++;
	}

	void RotacionCircular::insertarAlInicio(const string& nombre) {
		NodoLocutor* nuevo = new NodoLocutor(nombre);
		if (cola == nullptr) {
			nuevo->siguiente = nuevo;
			cola = nuevo;
		}
		else {
			nuevo->siguiente = cola->siguiente;
			// nuevo->sig vieja cabeza
			cola->siguiente = nuevo;
			// cola ahora apunta al nuevo
			// cola no cambia: solo cambió quién es la cabeza
		}
		cantidad++;
	}
	bool RotacionCircular::insertarDespuesDe(const string& referencia,
		const string& nuevo_nombre) {
		if (cola == nullptr) { return false; }
		NodoLocutor* cabeza = getCabeza();
		NodoLocutor* actual = cabeza;
		do {
			if (actual->nombre == referencia) {
				NodoLocutor* nuevo = new NodoLocutor(nuevo_nombre);
				nuevo->siguiente = actual->siguiente;
				actual->siguiente = nuevo;
				if (actual == cola) cola = nuevo; // si era la cola, el nuevo es la nueva cola
				cantidad++;
				return true;
			}
			actual = actual->siguiente;
		} while (actual != cabeza);
		return false;
	}
	bool RotacionCircular::existeLocutor(const string& nombre) const
	{
		if (cola == nullptr) { return false; }

		NodoLocutor* cabeza = getCabeza();


		NodoLocutor* actual = cabeza;

		do {
			if (actual->nombre == nombre) { return true; }
			actual = actual->siguiente;
		} while (actual != cabeza);
		return false;
	}
	int RotacionCircular::obtenerPosicion(const string& nombre) const {
		if (cola == nullptr) { return -1; }
		NodoLocutor* cabeza = getCabeza();
		NodoLocutor* actual = cabeza;
		int pos = 0;
		do {
			if (actual->nombre == nombre) { return pos; }
			actual = actual->siguiente;
			pos++;
		} while (actual != cabeza);
		return -1;
	}
	string RotacionCircular::turnoActual() const {

		if (cola == nullptr) { return ""; }
		return getCabeza()->nombre;

	}
	bool RotacionCircular::eliminarLocutor(const string& nombre) {
		if (cola == nullptr) { return false; }
		NodoLocutor* cabeza = getCabeza();
		NodoLocutor* actual = cabeza;
		NodoLocutor* previo = cola; // el recorrido circular comienza con previo = cola
		do {
			if (actual->nombre == nombre) {
				if (actual == cola && actual == cabeza) {
					// único nodo en la lista
					cola = nullptr;
				}
				else {
					previo->siguiente = actual->siguiente;
					// saltar al actual
					if (actual == cola) cola = previo;
					// si era la cola, actualizar
				}
				delete actual;
				actual = nullptr;
				cantidad--;
				return true;
			}
			previo = actual;
			actual = actual->siguiente;
		} while (actual != cabeza);
		return false;

	}

	bool RotacionCircular::eliminarTurnoActual()
	{
		if (cola == nullptr) { return false; }
		return eliminarLocutor(getCabeza()->nombre);

	}

	string RotacionCircular::siguiente() {
		if (cola == nullptr) { return ""; }
		cola = cola->siguiente; // rotar: la cola avanza, por lo que la cabeza cambia
		getCabeza()->turnosAsignados++;
		return getCabeza()->nombre;
		
	}
	void RotacionCircular::simularTurnos(int n) {
		if (cola == nullptr) { cout << "Sin locutores en rotacion." << endl; return; }
		for (int i = 1; i <= n; i++) {
			cout << "Turno " << i << ": " << siguiente() << endl;
		}
	}
	void RotacionCircular::imprimirRotacion() const {
		if (cola == nullptr) { cout << "Rotacion vacia." << endl; return; }
		NodoLocutor* cabeza= getCabeza();
		NodoLocutor* actual= cabeza;
		cout << "Rotacion: ";
		do {
			cout << actual->nombre;
			actual = actual->siguiente;
			if (actual != cabeza) { cout << " -> "; }
		} while (actual != cabeza);
		cout <<" -> (inicio)" << endl;
	}
	void RotacionCircular::imprimirEstadisticas() const
	{

		if (cola == nullptr) {
			std::cout << "No hay locutores en la rotacion" << std::endl;
			return;
		}

		NodoLocutor* cabeza = getCabeza();
		NodoLocutor* actual = cabeza;

		std::cout << "Estadisticas" << std::endl;
		do {

			std::cout << "Locutor: " << actual->nombre << "Turnos: asignados: " << actual->turnosAsignados << std::endl;
			actual = actual->siguiente;

		} while (actual != cabeza);

	}
	string RotacionCircular::locutorMasActivo() const
	{
		return string();
	}
	int RotacionCircular::getCantidad() const { return cantidad; }
	bool RotacionCircular::estavacia() const { return cola == nullptr; }
} // namespace EIF201



