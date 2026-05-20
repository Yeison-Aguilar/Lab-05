#ifndef BITACORA_H
#define BITACORA_H
#include"NodoAve.h"
#include<string>


namespace EIF201
{
	class Bitacora
	{
	private: 
		std::string Ruta;
		int Validos;
		int Descartados;


	public:
		Bitacora(const std::string& ruta );
		bool registrarAve(const std::string& anillo, const std::string& especie,double peso, char sexo, const std::string& fecha);
		int cargartodas(NodoAve*& cabesa);
		int cargasvalidas(NodoAve*& cabesa);
		int getVAlidas() const;
		int getDescartados() const;
		static void lieberarlista(NodoAve*& cabesa);


	};
}
#endif