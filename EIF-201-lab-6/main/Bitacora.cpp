#include "Bitacora.h"
namespace EIF201{
	Bitacora::Bitacora(const std::string& ruta) :Ruta(ruta), Validos(0), Descartados(0)
	{

	}
	bool Bitacora::registrarAve(const std::string& anillo, const std::string& especie, double peso, char sexo, const std::string& fecha)
	{
		return false;
	}
	int Bitacora::cargartodas(NodoAve*& cabesa)
	{
		return 0;
	}
	int Bitacora::cargasvalidas(NodoAve*& cabesa)
	{
		return 0;
	}
	int Bitacora::getVAlidas() const
	{
		return 0;
	}
	int Bitacora::getDescartados() const
	{
		return 0;
	}
	void Bitacora::lieberarlista(NodoAve*& cabesa)
	{
	}
}