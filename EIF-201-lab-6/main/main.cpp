#include <iostream>
#include <string>
#include <limits>
#include "Bitacora.h"

using namespace EIF201;


void ejecutarMenu()
{
    std::string ruta;
    std::cout << "Ingrese ruta del archivo de bitacora: ";
    std::getline(std::cin, ruta);

    Bitacora bit(ruta);
    NodoAve* cabeza = nullptr;

    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1) Registrar ave\n";
        std::cout << "2) Cargar todas (cronologico)\n";
        std::cout << "3) Cargar validas (defensivo)\n";
        std::cout << "4) Mostrar contadores (validas/descartadas)\n";
        std::cout << "5) Liberar lista en memoria\n";
        std::cout << "6) Salir\n";
        std::cout << "Seleccione una opcion: ";

        int opcion = 0;
        if (!(std::cin >> opcion)) {
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion invalida. Intente de nuevo.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 1) {
            std::string anillo, especie, fecha;
            double peso = 0.0;
            char sexo = '\0';

            std::cout << "Anillo: ";
            std::getline(std::cin, anillo);
            std::cout << "Especie: ";
            std::getline(std::cin, especie);
            std::cout << "Peso: ";
            std::cin >> peso;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Sexo (M/H/X): ";
            std::cin >> sexo;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Fecha: ";
            std::getline(std::cin, fecha);

            if (bit.registrarAve(anillo, especie, peso, sexo, fecha)) {
                std::cout << "Registro guardado en archivo.\n";
            } else {
                std::cout << "Error al abrir el archivo para registrar.\n";
            }

        } else if (opcion == 2) {
            
            bit.lieberarlista(cabeza);
            int n = bit.cargartodas(cabeza);
            std::cout << n << " aves cargadas (todas).\n";

        } else if (opcion == 3) {
            
            bit.lieberarlista(cabeza);
            int n = bit.cargasvalidas(cabeza);
            std::cout << n << " aves validas cargadas.\n";

        } else if (opcion == 4) {
            std::cout << "Validas: " << bit.getVAlidas() << "\n";
            std::cout << "Descartadas: " << bit.getDescartados() << "\n";

        } else if (opcion == 5) {
            bit.lieberarlista(cabeza);
            std::cout << "Lista liberada de memoria.\n";

        } else if (opcion == 6) {
            bit.lieberarlista(cabeza);
            std::cout << "Saliendo...\n";
            break;

        } else {
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    }
}

int main()
{
    ejecutarMenu();
    return 0;
}

