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
    }else if(it != end && it->get_token() == "opRelacional" && it->get_id() == 18){ // '<'
        while(it != end && it->get_token() != "opRelacional") {
            it++;
        }
        if(it != end && it->get_token() == "opRelacional" && it->get_id() == 19) { // '>'
            return true;
        }
    }
    return false;
}
bool entero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "entero"){
        it++;
        return true;
    }
    return false;
}
bool real(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "real"){
        it++;
        return true;
    }
    return false;
}
bool verdadero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra reservada" && it->get_id() == 35) {
        it++;
        return true;
    }
    return false;
}
bool falso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra reservada" && it->get_id() == 36) {
        it++;
        return true;
    }
    return false;
}
bool tipo(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "tipo"){
        it++; // Avanzar al siguiente token
        return true;
    }
    return false;
}
bool ope_aritmeticos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "opAritmetico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    return false;
}
bool ope_relacional(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "<", ">", "<=", ">="
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() != 16 && it->get_id() != 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    return false;
}
bool ope_igualdad(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // == 16 | != 17
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() == 16 || it->get_id() == 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    return false;
}
bool ope_logicos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "&&", "||", "!"
    if (it != end && it->get_token() == "opLogico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    return false;
}
bool cadena(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "cadena"){
        it++;
        return true;
    }
    return false;
}
bool caracter(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "caracter"){
        it++;
        return true;
    }
    return false;
}
bool identificador(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "id"){
        it++;
        return true;
    }
    return false;
}
bool valor(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && (cadena(it, end) || caracter(it, end) || entero(it, end) ||
                      real(it, end) || verdadero(it, end) || falso(it, end))){
        it++;
        return true;
    }
    return false;
}
bool op_igual(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "opRelacional" && it->get_id() == 29){
        it++;
        return true;
    }
    return false;
}
bool asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Verificar si el primer token es un identificador
    if (!identificador(it, end)) {
        return false;
    }
    // Verificar si a continuación hay un operador de asignación
    if (!op_igual(it, end)) {
        return false;
    }
    // Verificar si a continuación hay un valor o un identificador
    if (!valor(it, end) && !identificador(it, end)) {
        return false;
    }// int id = valor

    if(!ope_aritmeticos(it, end) && !valor(it, end) && !identificador(it, end)){
        // Ya no queda mas sentencia
        return true;
    }
    return false;
}
bool declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Verificar si el primer token no es un tipo
    if(!tipo(it, end)){
        std::cout<<"Error en el tipo"<<std::endl;
        return false;
    }
    // Verificar si a continuación hay una asignacion
    if(asignacion(it, end)){
        return true;
    }
    // Verificar si a continuación hay un identificador
    it--; // Se regresa luego de haber consumido el id
    if(identificador(it, end)){
        return true;
    }
    std::cout<<"Error al declarar variable"<<std::endl;
    return false; // La estructura no coincide con la regla declarar_variable
}
bool secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool secuencia_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool secuencia_do_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool secuencia_for(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
bool instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(declarar_variable(it, end)){
        return true;
    }
    return false;
}
bool bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    return true;
}
// Inicio de validación de reglas
bool analizador_sintactico::validar_inicio(std::list<Componente>& tokens) {
    auto it = tokens.begin();   // Iterador al inicio de la lista
    auto end = tokens.end();    // Iterador al final de la lista

    // Llama a las funciones de validación correspondientes

    if(instruccion(it, end)){
        return true;
    }
    return false;
}
