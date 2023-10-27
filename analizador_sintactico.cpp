#include "analizador_sintactico.h"

analizador_sintactico::analizador_sintactico(){}

/*
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

    // Verificar si hay una expresión distinta a puntoComa
    while (it != tokens.end() && it->get_token() != "puntoComa") {
        it++;
    }

    if (it != tokens.end() && it->get_token() == "puntoComa") {
        return true;
    } else {
        return false;
    }
}
*/

// REGLAS ESTATICAS: -------------------------------------------------------------------------------

bool directiva(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it == end || it->get_token() != "Hashtag") {
        return false;
    }
    it++;  // Avanzar al siguiente token (Directiva)
    if(it == end || it->get_token() != "Directiva") {
        return false;
    }
    it++;  // Avanzar al siguiente token (cadena)
    if(it != end && it->get_token() == "cadena") {
        it++;  // Avanzar al siguiente token
        return true;
    }else if(it != end && it->get_token() == "opRelacional") {
        while(it != end && it->get_token() != "opRelacional") {
            it++;
        }
        if(it != end && it->get_token() == "opRelacional") {
            return true;
        }
    }
    return false;
}

bool secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool secuencia_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool secuencia_do_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool secuencia_for(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Hashtag"){
        it++; // Avanzar al siguiente token
    }
    return false;
}
bool instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it == end || it->get_token() != "Separador") {
        return false;
    }

    return false;
}
bool bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it == end || it->get_token() != "Separador") {
        return false;
    }

    return false;
}
// Inicio de validación de reglas
bool analizador_sintactico::validar_inicio(std::list<Componente>& tokens) {
    auto it = tokens.begin();   // Iterador al inicio de la lista
    auto end = tokens.end();    // Iterador al final de la lista

    // Llama a las funciones de validación correspondientes
    if(directiva(it, end)){
        return true;
    }
    if (declarar_variable(it, end)){
        return true;
    }
    if(funcion(it, end)){
        return true;
    }
    if(secuencia_if(it, end)){
        return true;
    }
    if(secuencia_while(it, end)){
        return true;
    }
    if(secuencia_for(it, end)){
        return true;
    }
    if(secuencia_switch(it, end)){
        return true;
    }
    if(secuencia_do_while(it, end)){
        return true;
    }
    return false;
}
