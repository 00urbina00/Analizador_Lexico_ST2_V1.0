#include <iostream>
#include <string>
#include <cctype>

class AnalizadorSintactico {
	public:
		AnalizadorSintactico(const std::string& codigo) : codigo_(codigo), posicion_(0) {}

		bool Analizar() {
			return Identificador();
		}
		bool Valor() {
			return Cadena() || Caracter() || Entero() || Real();
		}
		bool declarar_variable() {
			//ignorar espacios en blanco iniciales:
			while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
			{
				posicion_++;
			}
			// Intenta analizar el tipo
			if (Tipo()) {
				//ignorar espacios en blanco despues del tipo:
				while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
				{
					posicion_++;
				}
				// Luego, verifica un identificador
				if (Identificador()) {
					//ignorar espacios en blanco despues de identificador:
					while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
					{
						posicion_++;
					}
					// Finalmente, busca un punto y coma y verifica si hemos llegado al final
					return Coincide(';') && posicion_ == codigo_.length();
				}
			}
			return false;
		}
		bool secuencia_if() {
			// Ignora espacios en blanco después de "if"
			while (isspace(codigo_[posicion_])) {
				posicion_++;
			}

			if (Coincide("if")) {
				// Ignora espacios en blanco después de "if"
				while (isspace(codigo_[posicion_])) {
					posicion_++;
				}

				if (Coincide('(')) {
					// Ignora espacios en blanco después de '('
					while (isspace(codigo_[posicion_])) {
						posicion_++;
					}

					if (Condicion()) {
						// Ignora espacios en blanco antes o después de ')'
						while (isspace(codigo_[posicion_])) {
							posicion_++;
						}

						if (Coincide(')')) {
							// Ignora espacios en blanco antes de '{'
							while (isspace(codigo_[posicion_])) {
								posicion_++;
							}

							if (Coincide('{') && Bloque() && Coincide('}')) {
								return true; // Instrucción "if" válida
							}
						}
					}
				}
			}
			return false; // No se cumplió la estructura de la instrucción "if"
		}
		bool secuencia_while(){
			return true;
		}
		bool inicio() {
			return declarar_variable() || secuencia_if() || secuencia_while();
		}
	private:
		bool Coincide(const char caracter) {
			if (posicion_ < codigo_.length() && codigo_[posicion_] == caracter) {
				posicion_++;
				return true;
			}
			return false;
		}

		bool Coincide(const std::string& cadena) {
			if (codigo_.substr(posicion_, cadena.length()) == cadena) {
				posicion_ += cadena.length();
				return true;
			}
			return false;
		}

		bool Letra() {
			if (posicion_ < codigo_.length() && isalpha(codigo_[posicion_])) {
				posicion_++;
				return true;
			}
			return false;
		}

		bool Digito() {
			if (posicion_ < codigo_.length() && isdigit(codigo_[posicion_])) {
				posicion_++;
				return true;
			}
			return false;
		}

		bool Cadena() {
			if (Coincide('"')) {
				while (posicion_ < codigo_.length() && codigo_[posicion_] != '"') {
					posicion_++;
				}
				return Coincide('"');
			}
			return false;
		}

		bool Caracter() {
			if (Coincide('\'')) {
				if (posicion_ < codigo_.length() && codigo_[posicion_] != '\'') {
					posicion_++;
				}
				return Coincide('\'');
			}
			return false;
		}

		bool OperadoresRelacionales() {
			const std::string operadoresValidos[] = { "<",">","<=",">=" };
			for (const std::string& operadorValido : operadoresValidos) {
				if (Coincide(operadorValido)) {
					//verificar el operador dentro de los validos
					if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
						return true;
					}
				}
			}
			return false;
		}

		bool OperadoresLogicos() {
			const std::string operadoresLogicos[] = { "||","&&","!" };
			for (const std::string& operadorValido : operadoresLogicos) {
				if (Coincide(operadorValido)) {
					//verificar el operador dentro de los validos
					if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
						return true;
					}
				}
			}
			return false;
		}

		bool OperadoresAritmeticos() {
			const char operadoresAritmeticos[] = { '+', '-', '*', '/' };
			for (const char& operadorValido : operadoresAritmeticos) {
				if (Coincide(operadorValido)) {
					//verificar el operador dentro de los validos
					if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
						return true;
					}
				}
			}
			return false;
		}

		bool OperadoresIgualdad() {
			const std::string operadoresIgualdad[] = { "==","!=" };
			for (const std::string& operadorValido : operadoresIgualdad) {
				if (Coincide(operadorValido)) {
					//verificar el operador dentro de los validos
					if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
						return true;
					}
				}
			}
			return false;
		}

		bool Entero() {
			int inicio = posicion_;
			while (Digito());
			return posicion_ > inicio;
		}

		bool Real() {
			int inicio = posicion_;
			if (Entero() && Coincide('.') && Entero()) {
				return true;
			}
			posicion_ = inicio;
			return false;
		}

		bool Tipo() {
			const std::string tiposValidos[] = { "int", "float", "void", "char", "string" };
			for (const std::string& tipoValido : tiposValidos) {
				if (Coincide(tipoValido)) {
					// Verifica que no haya caracteres alfanuméricos adicionales después del tipo
					if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
						return true;
					}
				}
			}
			return false;
		}

		bool Identificador() {
			if (Letra()) {
				while (Letra() || Digito() || Coincide('_'));
				return true;
			}
			return false;
		}

		bool Condicion() {
			// Primer operando (identificador o valor)
			if (Identificador() || Valor()) {
				// Operador relacional
				if (OperadoresRelacionales()) {
					// Segundo operando (identificador o valor)
					if (Identificador() || Valor()) {
						// Posible repetición con operadores lógicos
						while (OperadoresLogicos()) {
							// Tercer operando (identificador o valor)
							if (Identificador() || Valor()) {
								// Operador relacional
								if (!OperadoresRelacionales()) {
									return false; // Si no hay operador relacional, es inválido
								}
							}
							else {
								return false; // Si falta el tercer operando, es inválido
							}
						}
						return true; // Condición válida
					}
				}
			}
			return false; // No se cumplió la estructura de la condición
		}

		bool Asignacion() {
			if (Identificador()) {
				if (Coincide('=')) {
					if (Valor()) {
						return true; // Asignación simple
					}
					else {
						// Asignación con operaciones aritméticas
						while (OperadoresAritmeticos()) {
							if (!(Valor() || Identificador())) {
								return false; // Error si no se cumple el patrón
							}
						}
						return true; // Asignación con operaciones aritméticas válida
					}
				}
			}
			return false; // No se cumplió la estructura de la asignación
		}

		bool Paro() {
			return Coincide("Break");
		}

		bool Retorno() {
			//ignorar espacios en blanco iniciales:
			while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
			{
				posicion_++;
			}
			if (Coincide("return")) {
				//ignorar espacios en blanco despues de la palabra retorno:
				while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
				{
					posicion_++;
				}
				// Después de "return", puede haber un valor o un identificador opcional
				return Valor() || Identificador() || true; // Si no hay valor ni identificador, aún se considera válido
			}
			return false;
		}

		bool Instruccion() {
			if (secuencia_if()) {
				return true;  // Es una instrucción válida de secuencia_if
			}
			else {
				// Si no es una secuencia_if, verifica las otras posibles instrucciones
				if (declarar_variable() || Retorno() || Asignacion() || Paro()) {
					while (posicion_ < codigo_.length() && isspace(codigo_[posicion_]))
					{
						posicion_++;
					}
					// Verifica si hay un punto y coma al final
					if (Coincide(';')) {
						return true; // Instrucción válida
					}
				}
			}
			return false; // No se cumplió la estructura de la instrucción
		}

		bool Bloque() {
			if (Coincide('{')) {
				// Verifica una secuencia de instrucciones dentro del bloque
				while (Instruccion()) {
					// Continúa verificando más instrucciones si las hay
				}
				// Al final, verifica que el bloque se cierre con '}'
				if (Coincide('}')) {
					return true; // Bloque válido
				}
			}
			return false; // No se cumplió la estructura del bloque
		}



		const std::string& codigo_;
		size_t posicion_;
	};

int main() {
	std::string codigo = "if(a==1){return 0;}";
	AnalizadorSintactico analizador(codigo);

	if (analizador.secuencia_if()) {
		std::cout << "La entrada es valida." << std::endl;
	}
	else {
		std::cout << "La entrada no es valida." << std::endl;
	}
	return 0;
}
