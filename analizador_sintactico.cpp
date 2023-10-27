#include "analizador_sintactico.h"


analizador_sintactico::analizador_sintactico(){
    this->posicion = 0;
}

bool analizador_sintactico::analizar(std::string cadena){
    return true;
}

bool analizador_sintactico::analizar_asignacion(std::list<Componente>& tokens) {
    auto it = tokens.begin();


    if (it != tokens.end() && it->get_token() == "id") {
        it++;
    } else {
        return false;
    }

    if (it != tokens.end() && it->get_token() == "opIgual") {
        it++;
    } else {
        return false;
    }

    // Verificar si hay una expresión
    while (it != tokens.end() && it->get_token() != "puntoComa") {
        it++;
    }

    if (it != tokens.end() && it->get_token() == "puntoComa") {
        return true;
    } else {
        return false;
    }
}
bool analizador_sintactico::validar_inicio(std::list<Componente>& tokens) {
    auto it = tokens.begin();

    // Llama a las funciones de validación correspondientes en el orden deseado.
    if (declarar_variable(it)) {
        return true;
    }
    if (funcion(it)) {
        return true;
    }
    if (secuencia_if(it)) {
        return true;
    }
    if (secuencia_while(it)) {
        return true;
    }
    if (secuencia_for(it)) {
        return true;
    }
    if (secuencia_switch(it)) {
        return true;
    }
    if (secuencia_do_while(it)) {
        return true;
    }
    if (directiva(it)) {
        return true;
    }
    if (comentario(it)) {
        return true;
    }

    return false;
}
