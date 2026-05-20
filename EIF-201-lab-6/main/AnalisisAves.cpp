#include "AnalisisAves.h"
#include <iostream>


using namespace EIF201;

void AnalisisAves::imprimirInversoAux(NodoAve* cab) const
{
	
	
		if (cab == nullptr) {
			return;
		}

		imprimirInversoAux(cab->siguiente);

		std::cout << "Anillo: " << cab->anillo << std::endl;
		std::cout << "Especie: " << cab->especie << std::endl;
		std::cout << "Peso: " << cab->peso << std::endl;
		std::cout << "Sexo: " << cab->sexo << std::endl;
		std::cout << "Fecha: " << cab->fecha << std::endl;
		std::cout << "----------------------" << std::endl;
	
}

NodoAve* AnalisisAves::maxAux(NodoAve* cab, NodoAve mejor) const
{
	return nullptr;
}

int AnalisisAves::contar(NodoAve * cab) const
{
	if (cab == nullptr){
		return 0;
	}

	return 1 + contar(cab->siguiente);
}

double AnalisisAves::sumaPesos(NodoAve* cab) const
{
	if (cab == nullptr) {
			return 0.0; 
	}

	return cab->peso + sumaPesos(cab->siguiente);
}

int AnalisisAves::contarEspecie(NodoAve* cab, const std::string& especie) const
{
	if (cab == nullptr) {
		return 0;
	}

	if (cab->especie == especie){
	    return 1 + contarEspecie(cab->siguiente, especie); 
	}

	return contarEspecie(cab->siguiente, especie);
}

bool AnalisisAves::existeEspecie(NodoAve* cab, const std::string& especie) const
{
	if (cab == nullptr) {
		return false;
	}

	if (cab->especie == especie) {
		return true;
	}

	return existeEspecie(cab->siguiente, especie);
}

NodoAve* AnalisisAves::aveMasPesada(NodoAve* cab, NodoAve* mejor) const
{
	if (cab == nullptr) {
		return mejor;
	}

	if (cab->peso > mejor->peso) {
		mejor = cab;
		return aveMasPesada(cab->siguiente, mejor);
	}

	return nullptr;
}

void AnalisisAves::imprimirCronologico(NodoAve* cab) const
{
	if (cab == nullptr) {
		return;
	}

	std::cout << cab->anillo << " "
			  << cab->especie << " "
			  << cab->peso << " "
			  << cab->sexo << " "
			  << cab->fecha << std::endl;

	imprimirCronologico(cab->siguiente);

}

void AnalisisAves::imprimirInverso(NodoAve* cab) const
{
	if (cab == nullptr) {
		return;
	}

	imprimirInverso(cab->siguiente); 
	std::cout << cab->anillo << '\n';
}

