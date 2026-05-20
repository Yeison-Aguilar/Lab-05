#include "Bitacora.h"
#include <fstream>
#include <sstream>
namespace EIF201{
	Bitacora::Bitacora(const std::string& ruta) :Ruta(ruta), Validos(0), Descartados(0)
	{

	}
	bool Bitacora::registrarAve(const std::string& anillo, const std::string& especie, double peso, char sexo, const std::string& fecha)
	{
      // Abrir el archivo en modo append para añadir al final sin truncar
		std::ofstream ofs(Ruta, std::ios::app);
		// Si no se pudo abrir el archivo, indicar fallo
		if (!ofs.is_open()) {
			return false;
		}
		// Escribir los campos separados por ';' y terminar con salto de línea
		ofs << anillo << ";" << especie << ";" << peso << ";" << sexo << ";" << fecha << "\n";
		// Cerrar el stream explícitamente (se cerrará de todos modos al destruirse)
		ofs.close();
		// Indicar éxito
		return true;
	}
	int Bitacora::cargartodas(NodoAve*& cabesa)
	{
     // Abrir el archivo para lectura
		std::ifstream ifs(Ruta);
		// Si no se puede abrir, dejar la cabeza en nullptr y retornar 0
		if (!ifs.is_open()) {
			cabesa = nullptr;
			return 0;
		}

		std::string linea;               // buffer para cada línea del archivo
		int contador = 0;               // contador de aves leídas
		NodoAve* tail = nullptr;        // puntero al último nodo para anexar al final
		// Leer el archivo línea por línea
		while (std::getline(ifs, linea)) {
			// Ignorar líneas vacías
			if (linea.empty()) continue;
			// Crear un stringstream para dividir la línea por ';'
			std::stringstream ss(linea);
			std::string anillo, especie, pesoStr, sexoStr, fecha;
			// Extraer cada campo usando ';' como separador
			if (!std::getline(ss, anillo, ';')) continue;
			if (!std::getline(ss, especie, ';')) continue;
			if (!std::getline(ss, pesoStr, ';')) continue;
			if (!std::getline(ss, sexoStr, ';')) continue;
			// El último campo puede ocupar el resto de la línea
			if (!std::getline(ss, fecha)) {
				// si falla, dejar fecha vacía
				fecha.clear();
			}

			// Convertir el peso de string a double, manejando errores
			double peso = 0.0;
			try {
				peso = std::stod(pesoStr);
			} catch (...) {
				peso = 0.0; // en caso de formato inválido usar 0.0
			}
			// Obtener el carácter sexo (primer carácter del campo)
			char sexo = sexoStr.empty() ? '\0' : sexoStr[0];

			// Crear un nuevo nodo dinámico con los datos leídos
			NodoAve* nodo = new NodoAve(anillo, especie, peso, sexo, fecha);
			// Si la lista está vacía, este nodo será la cabeza
			if (cabesa == nullptr) {
				cabesa = nodo;
				tail = nodo;
			} else {
				// Enlazar el nodo al final y actualizar tail
				tail->siguiente = nodo;
				tail = nodo;
			}
			++contador; // incrementar contador de aves cargadas
		}

		// Cerrar el stream y retornar la cantidad leída
		ifs.close();
		return contador;
	}
	int Bitacora::cargasvalidas(NodoAve*& cabesa)
	{
     // Abrir el archivo para lectura
		std::ifstream ifs(Ruta);
		if (!ifs.is_open()) {
			cabesa = nullptr;
			return 0;
		}

		// Inicializar contadores y lista
		cabesa = nullptr;
		Validos = 0;
		Descartados = 0;
		NodoAve* tail = nullptr;
		std::string linea;
		// Leer línea por línea y validar defensivamente
		while (std::getline(ifs, linea)) {
			// Línea vacía -> descartada
			if (linea.empty()) {
				++Descartados;
				continue;
			}
			std::stringstream ss(linea);
			std::string anillo, especie, pesoStr, sexoStr, fecha;
			// Extraer los cinco campos separados por ';'
			if (!std::getline(ss, anillo, ';') ||
				!std::getline(ss, especie, ';') ||
				!std::getline(ss, pesoStr, ';') ||
				!std::getline(ss, sexoStr, ';') ||
				!std::getline(ss, fecha)) {
				// Si no se extrajeron los cinco campos, contar como descartada
				++Descartados;
				continue;
			}

			// Validar peso: debe ser decimal y positivo
			double peso = 0.0;
			try {
				peso = std::stod(pesoStr);
			} catch (...) {
				++Descartados; // peso inválido
				continue;
			}
			if (peso <= 0.0) {
				++Descartados; // peso no positivo
				continue;
			}

			// Validar sexo: debe ser 'M', 'H' o 'X'
			char sexo = sexoStr.empty() ? '\0' : sexoStr[0];
			if (!(sexo == 'M' || sexo == 'H' || sexo == 'X')) {
				++Descartados;
				continue;
			}

			// Si todo es válido, crear nodo y anexarlo al final
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
       // Liberar todos los nodos de la lista enlazada y dejar la cabeza en nullptr
		while (cabesa != nullptr) {
			NodoAve* siguiente = cabesa->siguiente;
			delete cabesa;
			cabesa = siguiente;
		}
		cabesa = nullptr;
	}
}