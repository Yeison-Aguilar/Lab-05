#ifndef HISTORIAL_DOBLE_H
#define HISTORIAL_DOBLE_H

#include <string>

#include "NodoHistorial.h"
namespace EIF201 {

	class HistorialDoble
	{
	private:
		NodoHistorial* cabeza;
		NodoHistorial* cola;
		int cantidad;

	public:
		HistorialDoble();
		~HistorialDoble();

		void insertarAlInicio(const std::string& cancion);
		void insertarAlFinal(const std::string& cancion);

		void insertarEnPosicion(const std::string& cancion, int pos);
		bool insertarAntesDe(const std::string& referencia, const std::string& nueva);

		bool insertarDespuesDe(const std::string& referencia, const std::string& nueva);
		bool existeCancion(const std::string& cancion) const;

		int obtenerPosicion(const std::string& cancion) const;

		std::string obtenerEnPosicion(int pos) const;
		int obtenerPosicionDesdeElFinal(const std::string& cancion) const;

		bool eliminarPrimera(const std::string& cancion);

		bool eliminarUltima(const std::string& cancion);

		bool eliminarEnPosicion(int pos);

		bool eliminarCabeza();
		bool eliminarCola();

		//Recorrido
		void imprimirCronologico() const; //Cabeza -> cola
		void imprimirInverso() const; // Cola -> cabeza

		int getCantidad() const;
		bool estaVacia() const;

	};
}


#endif // !HISTORIAL_DOBLE_H