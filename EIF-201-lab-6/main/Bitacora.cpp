#include "Bitacora.h"
#include <fstream>
#include <sstream>
namespace EIF201{
	Bitacora::Bitacora(const std::string& ruta) :Ruta(ruta), Validos(0), Descartados(0)
	{

	}
	bool Bitacora::registrarAve(const std::string& anillo, const std::string& especie, double peso, char sexo, const std::string& fecha)
	{
		std::ofstream ofs(Ruta, std::ios::app);
		if (!ofs.is_open()) {
			return false;
		}
		ofs << anillo << ";" << especie << ";" << peso << ";" << sexo << ";" << fecha << "\n";
		ofs.close();
		return true;
	}
	int Bitacora::cargartodas(NodoAve*& cabesa)
	{
		std::ifstream ifs(Ruta);
		if (!ifs.is_open()) {
			cabesa = nullptr;
			return 0;
		}

		std::string linea;               
		int contador = 0;               
		NodoAve* tail = nullptr;  

		while (std::getline(ifs, linea)) {
			
			if (linea.empty()) continue;
			
			std::stringstream ss(linea);
			std::string anillo, especie, pesoStr, sexoStr, fecha;
			
			if (!std::getline(ss, anillo, ';')) continue;
			if (!std::getline(ss, especie, ';')) continue;
			if (!std::getline(ss, pesoStr, ';')) continue;
			if (!std::getline(ss, sexoStr, ';')) continue;
			
			if (!std::getline(ss, fecha)) {
				
				fecha.clear();
			}

			
			double peso = 0.0;
			try {
				peso = std::stod(pesoStr);
			} catch (...) {
				peso = 0.0; 
			}
			
			char sexo = sexoStr.empty() ? '\0' : sexoStr[0];

			
			NodoAve* nodo = new NodoAve(anillo, especie, peso, sexo, fecha);
			
			if (cabesa == nullptr) {
				cabesa = nodo;
				tail = nodo;
			} else {
				
				tail->siguiente = nodo;
				tail = nodo;
			}
			++contador; 
		}

		
		ifs.close();
		return contador;
	}
	int Bitacora::cargasvalidas(NodoAve*& cabesa)
	{
     
		std::ifstream ifs(Ruta);
		if (!ifs.is_open()) {
			cabesa = nullptr;
			return 0;
		}

		
		cabesa = nullptr;
		Validos = 0;
		Descartados = 0;
		NodoAve* tail = nullptr;
		std::string linea;
		
		while (std::getline(ifs, linea)) {
			
			if (linea.empty()) {
				++Descartados;
				continue;
			}
			std::stringstream ss(linea);
			std::string anillo, especie, pesoStr, sexoStr, fecha;
			
			if (!std::getline(ss, anillo, ';') ||
				!std::getline(ss, especie, ';') ||
				!std::getline(ss, pesoStr, ';') ||
				!std::getline(ss, sexoStr, ';') ||
				!std::getline(ss, fecha)) {
				
				++Descartados;
				continue;
			}

		
			double peso = 0.0;
			try {
				peso = std::stod(pesoStr);
			} catch (...) {
				++Descartados; 
				continue;
			}
			if (peso <= 0.0) {
				++Descartados; 
				continue;
			}

			
			char sexo = sexoStr.empty() ? '\0' : sexoStr[0];
			if (!(sexo == 'M' || sexo == 'H' || sexo == 'X')) {
				++Descartados;
				continue;
			}

			
			NodoAve* nodo = new NodoAve(anillo, especie, peso, sexo, fecha);
			if (cabesa == nullptr) {
				cabesa = nodo;
				tail = nodo;
			} else {
				tail->siguiente = nodo;
				tail = nodo;
			}
			++Validos;
		}

		ifs.close();
		return Validos;
	}
	int Bitacora::getVAlidas() const
	{
       return Validos;
	}
	int Bitacora::getDescartados() const
	{
       return Descartados;
	}
	void Bitacora::lieberarlista(NodoAve*& cabesa)
	{
       
		while (cabesa != nullptr) {
			NodoAve* siguiente = cabesa->siguiente;
			delete cabesa;
			cabesa = siguiente;
		}
		cabesa = nullptr;
	}
}