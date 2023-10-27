#ifndef ANALIZADORSINTACTICO_H
#define ANALIZADORSINTACTICO_H
#include <iostream>
#include <string>
#include <cctype>
class AnalizadorSintactico {
public:
    AnalizadorSintactico(const std::string& codigo) : codigo_(codigo), posicion_(0) {}
    bool declarar_variable() {
        // Ignorar espacios en blanco iniciales:
        EspaciosEnBlanco();
        // Intenta analizar el tipo
        if (Tipo()) {
            // Luego, verifica un identificador
            //EspaciosEnBlanco();
            if (Identificador()) {
                // Después, busca un punto y coma y verifica si hemos llegado al final
                EspaciosEnBlanco();
                if (Coincide(';')) {
                    return true;
                }
                // Si no encontramos un punto y coma, verificamos si hay una asignación (=)
                if (Coincide('=')) {
                    // Luego, intentamos analizar el valor
                    if (Valor()) {
                        // Finalmente, busca un punto y coma y verifica si hemos llegado al final
                        EspaciosEnBlanco();
                        return Coincide(';');
                    }
                }
            }
        }
        return false;
    }


private:
    bool Valor() {
        EspaciosEnBlanco();
        if (Cadena() || Caracter() || Entero() || Real()) {
            EspaciosEnBlanco();
            return true;
        }
        return false;
    }

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
        if (posicion_ < codigo_.length()) {
            char c = codigo_[posicion_];
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 'á' && c <= 'ú') || (c >= 'Á' && c <= 'Ú')) {
                posicion_++;
                return true;
            }
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
        EspaciosEnBlanco();
        const std::string tiposValidos[] = {"int", "float", "void", "char", "string"};
        for (const std::string& tipoValido : tiposValidos) {
            if (Coincide(tipoValido)) {
                // Verifica que no haya caracteres alfanuméricos adicionales después del tipo
                EspaciosEnBlanco();
                if (posicion_ == codigo_.length() || !isalnum(codigo_[posicion_])) {
                    return true;
                }
            }
        }
        return false;
    }


    bool Identificador() {
        if (Letra() || Coincide('_')) {
            while (Letra() || Digito() || Coincide('_')) {
                // Continuar mientras se encuentren letras, dígitos o guiones bajos
            }
            // Verificar que el identificador no termine con un carácter no permitido
            if (posicion_ < codigo_.length() && !isalnum(codigo_[posicion_]) && codigo_[posicion_] != '_') {
                return false;
            }
            return true;
        }
        return false;
    }


    void EspaciosEnBlanco() {
        while (posicion_ < codigo_.length() && std::isspace(codigo_[posicion_])) {
            posicion_++;
        }
    }

    const std::string& codigo_;
    size_t posicion_;
};


#endif // ANALIZADORSINTACTICO_H
