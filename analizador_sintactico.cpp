#include "analizador_sintactico.h"

#include <utility>
// CONSTRUCTOR: -----------------------------------------------------------------------------------
analizador_sintactico::analizador_sintactico(){
    regla = "";
    token_esp = "";
    ultimo_token_recibido = "";
}
// MANEJO DE ERRORES: -----------------------------------------------------------------------------
void analizador_sintactico::capturar_error(std::list<Componente>::iterator& it, std::string rule, std::string token_esperado){
    Componente componente = *it;
    regla = std::move(rule);
    token_esp = std::move(token_esperado);
    ultimo_token_recibido = componente.get_token();
}
// DEBUGGING: -------------------------------------------------------------------------------------
void analizador_sintactico::print_elemento(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it!=end){
        Componente elemento = *it;
        std::cout<<"El elemento actual es: "<<elemento.get_lexema()<<",  token: "<<elemento.get_token()<<", Id: "<<elemento.get_id()<<std::endl;
    }
}
// REGLAS PARA TOKENS BASICOS: --------------------------------------------------------------------
bool analizador_sintactico::dos_puntos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Separador" && it->get_id() == 47){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Dos puntos", ":");
    return false;
}

bool analizador_sintactico::coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 26){
        it++;
        return true;
    }
    capturar_error(it, "Coma", ",");
    return false;
}
bool analizador_sintactico::punto_coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 25){
        it++;
        return true;
    }
    capturar_error(it, "Punto y coma", ";");
    return false;
}
bool analizador_sintactico::llave_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 37){
        it++;
        return true;
    }
    capturar_error(it, "Llave izquierda", "{");
    return false;
}
bool analizador_sintactico::llave_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 38){
        it++;
        return true;
    }
    capturar_error(it, "Llave derecha", "}");
    return false;
}
bool analizador_sintactico::parentesis_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 39){
        it++;
        return true;
    }
    capturar_error(it, "Parentesis izquierdo", "(");
    return false;
}
bool analizador_sintactico::parentesis_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 40){
        it++;
        return true;
    }
    capturar_error(it, "Parentesis derecho", ")");
    return false;
}
bool analizador_sintactico::entero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "entero"){
        it++;
        return true;
    }
    capturar_error(it, "Entero", "0");
    return false;
}
bool analizador_sintactico::real(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "real"){
        it++;
        return true;
    }
    capturar_error(it, "Real", "0.0");
    return false;
}
bool analizador_sintactico::verdadero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 35) {
        it++;
        return true;
    }
    capturar_error(it, "Verdadero", "true");
    return false;
}
bool analizador_sintactico::falso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 36) {
        return true;
    }
    capturar_error(it, "Falso", "false");
    return false;
}
bool analizador_sintactico::tipo(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "tipo"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Tipo", "(int| float | char | string | bool | void)");
    return false;
}
bool analizador_sintactico::ope_aritmeticos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "opAritmetico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Aritmetico", "(* | / | + | -)");
    return false;
}
bool analizador_sintactico::ope_relacional(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "<", ">", "<=", ">="
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() != 16 && it->get_id() != 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Relacional", "(< | > | <= | >=)");
    return false;
}
bool analizador_sintactico::ope_igualdad(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // == 16 | != 17
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() == 16 || it->get_id() == 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Igualdad", "(== | !=)");
    return false;
}
bool analizador_sintactico::ope_logicos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "&&", "||", "!"
    if (it != end && it->get_token() == "opLogico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Logico", "(&& | || | !)");
    return false;
}
bool analizador_sintactico::cadena(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "cadena"){
        it++;
        return true;
    }
    capturar_error(it, "Cadena", "\"cadena\"");
    return false;
}
bool analizador_sintactico::caracter(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "caracter"){
        it++;
        return true;
    }
    capturar_error(it, "Caracter", "\'c\'");
    return false;
}
bool analizador_sintactico::identificador(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "id"){
        it++;
        return true;
    }
    capturar_error(it, "Identificador", "id");
    return false;
}
// REGLAS PARA EXPRESIONES: -----------------------------------------------------------------------
bool analizador_sintactico::valor(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    if(entero(it, end) || real(it, end) || cadena(it, end) ||
                      caracter(it, end) || verdadero(it, end) || falso(it, end)){
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}
// REGLAS DE DIRECTIVAS: --------------------------------------------------------------------------
bool analizador_sintactico::directiva(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Respaldar estado del iterador
    auto it_aux = it;
    if(it == end || it->get_token() != "Hashtag") {
        capturar_error(it, "Directiva", "#");
        return false;
    }
    it++;  // Avanzar al siguiente token (Directiva)
    if(it == end || it->get_token() != "Directiva") {
        capturar_error(it, "Directiva", "include | define | pragma");
        return false;
    }
    it++;  // Avanzar al siguiente token (cadena)
    if(it != end && it->get_token() == "cadena") {
        it++;  // Avanzar al siguiente token
        return true;
    }else if(it != end && it->get_token() == "opRelacional" && it->get_id() == 18){ // '<'
        it++;
        while(it != end && it->get_token() != "opRelacional") {
            it++;
        }
        if(it != end && it->get_token() == "opRelacional" && it->get_id() == 19) { // '>'
            it++;
            return true;
        }
    }
    it = it_aux; // Restaurar estado del iterador
    capturar_error(it, "Directiva", "caden || <valor>");
    return false;
}
// REGLAS DE ASIGNACION: --------------------------------------------------------------------------
bool analizador_sintactico::op_igual(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "opRelacional" && it->get_id() == 29){
        it++;
        return true;
    }
    capturar_error(it, "Operador Igual", "=");
    return false;
}
bool analizador_sintactico::asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end) {
    auto it_aux = it; // Respaldar estado del iterador
    // Verificar si el primer token es un identificador
    if(!identificador(it, end)){
        return false;
    }
    // Verificar si a continuación hay un operador de asignación
    if(!op_igual(it, end)){
        it--; // Se regresa luego de haber consumido el id
        return false;
    }
    // Verificar si a continuación hay un valor (que puede ser un entero, real o identificador)
    if(valor(it, end) || identificador(it, end)){
        // Ahora, permitir operadores aritméticos opcionales
        while(ope_aritmeticos(it, end)){
            if(valor(it, end) || identificador(it, end)){
                // Continuar permitiendo más operadores y valores
            } else {
                // Error si no hay valor después de un operador
                it = it_aux; // Restaurar estado del iterador
                return false;
            }
        }
        return true;
    }
    // Si no se encontró un valor válido, entonces la asignación es incorrecta
    it = it_aux; // Restaurar estado del iterador
    return false;
}
/*
bool analizador_sintactico::asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end) {
    auto it_aux = it; // Respaldar estado del iterador
    // Verificar si el primer token es un identificador
    if(!identificador(it, end)){
        return false;
    }
    // Verificar si a continuación hay un operador de asignación
    if(!op_igual(it, end)){
        it--; // Se regresa luego de haber consumido el id
        return false;
    }
    // Verificar si a continuación hay un valor (que puede ser un entero o un identificador)
    if(valor(it, end) || identificador(it, end)){
        return true;
    }
    // Si no se encontró un valor válido, entonces la asignación es incorrecta
    it = it_aux; // Restaurar estado del iterador
    return false;
}*/
// REGLAS PARA COMPONENTES DE ESTRUCTURAS: ---------------------------------------------------------
bool analizador_sintactico::condicional_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 30){
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "if");
    return false;
}
bool analizador_sintactico::condicional_else(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 31){
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "else");
    return false;
}
bool analizador_sintactico::ope_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 32){
        it++;
        return true;
    }
    capturar_error(it, "Operador while", "while()");
    return false;
}
bool analizador_sintactico::ope_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 34){
        it++;
        return true;
    }
    capturar_error(it, "Operador switch", "switch()");
    return false;
}
bool analizador_sintactico::ope_case(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 46) { // 'case'
        it++;
        return true;
    }
    capturar_error(it, "Operador case", "case");
    return false;
}
// REGLAS DE INSTRUCCIONES: ------------------------------------------------------------------------
bool analizador_sintactico::instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    if(declarar_variable(it, end) || llamada_funcion(it, end) || retorno(it, end) || romper(it, end) || asignacion(it, end)){
        if(punto_coma(it, end)){
            return true;
        }
    }
    if(secuencia_if(it, end) || secuencia_while(it, end) || secuencia_switch(it, end)){
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}
bool analizador_sintactico::bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    bool bandera = false;
    while(instruccion(it, end)) {
        bandera = true;
    }
    if(!bandera){
        it = it_aux; // Restaurar estado del iterador
    }
    return bandera;
}
bool analizador_sintactico::declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Verificar si el primer token no es un tipo
    auto it_aux = it; // Respaldar estado del iterador
    if(!tipo(it, end)){
        return false;
    }
    // Verificar si a continuación hay una asignacion
    if(asignacion(it, end)){
        return true;
    }
    // Verificar si a continuación hay un identificador
    if(identificador(it, end)){
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    return false; // La estructura no coincide con la regla declarar_variable
}
bool analizador_sintactico::romper(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){ // break
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 45){
        it++;
        return true;
    }
    capturar_error(it, "Romper ciclo", "break");
    return false;
}
bool analizador_sintactico::retorno(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 44){
        it++;
        if(valor(it, end) || identificador(it, end)){
            return true;
        }
        return true;
    }else{
        capturar_error(it, "Retorno", "return");
        return false;
    }
}

// REGLAS DE FUNCIONES: ----------------------------------------------------------------------------
bool analizador_sintactico::parametro(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    if(tipo(it, end)){
        if(identificador(it, end)){
            return true;
        }
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}
bool analizador_sintactico::llamada_funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (identificador(it, end) && parentesis_izq(it, end)) {
        // Verificar si hay parámetros (pueden ser 0 o más)
        while (valor(it, end) || identificador(it, end)) {
            // Si se encuentra una coma, procesar otro parámetro
            if (!coma(it, end)) {
                break; // Salir si no se encuentra una coma
            }
        }
        // Procesar paréntesis derecho
        if (parentesis_der(it, end)) {
            return true; // La función se procesó correctamente
        }
    }
}
bool analizador_sintactico::funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    // Verificar si hay un tipo seguido de un identificador
    if (tipo(it, end) && identificador(it, end)) {
        // Procesar paréntesis izquierdo
        if (parentesis_izq(it, end)) {
            // Verificar si hay parámetros (pueden ser 0 o más)
            while (parametro(it, end)) {
                // Si se encuentra una coma, procesar otro parámetro
                if (!coma(it, end)) {
                    break; // Salir si no se encuentra una coma
                }
            }
            // Procesar paréntesis derecho
            if (parentesis_der(it, end)) {
                // Procesar llave izquierda, bloque y llave derecha
                if (llave_izq(it, end) && bloque(it, end) && llave_der(it, end)) {
                    return true; // La función se procesó correctamente
                }
                it--; // Regresar si no se encontró un bloque o paréntesis derecho
            }
        }
    }
    it = it_aux; // Restaurar estado del iterador
    return false; // La estructura no coincide con la regla de función
}
// REGLAS DE ESTRUCTURAS
// REGLAS DE ESTRUCTURA SWITCH: --------------------------------------------------------------------
bool analizador_sintactico::caso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    // 'case' valor ':' bloque 'break' ';'
    if(ope_case(it, end)){ // 'case'
        if(identificador(it, end) || (entero(it, end)) && dos_puntos(it, end)){
            // Procesar el bloque y el 'break'
            if (bloque(it, end) && romper(it, end) && punto_coma(it, end)){
                return true;
            }
        }
    }else{
        it = it_aux; // Restaurar estado del iterador
        return false;
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}
bool analizador_sintactico::defecto(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 48){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Defectos", "default");
    return false;
}
bool analizador_sintactico::casos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    bool casos_validos = false;  // Variable para verificar si se ha encontrado al menos un caso válido
    while(it != end) {
        if(caso(it, end)) {
            casos_validos = true; // Se encontró al menos un caso válido
        }else{
            break; // Salir del bucle si no se encuentra un caso válido
        }
    }
    // Después de procesar todos los casos, verificamos si hay un caso por defecto
    if (defecto(it, end)) { // 'default'
        if (dos_puntos(it, end) && bloque(it, end) && romper(it, end) && punto_coma(it, end)) {
            // Se encontró un caso por defecto
            return true;
        }
    }
    if(!casos_validos){
        it = it_aux; // Restaurar estado del iterador
    }
    // El bucle terminará cuando no se encuentren más casos válidos
    return casos_validos; // Devolver true si se encontró al menos un caso válido
}
bool analizador_sintactico::secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // 'switch' '(' identificador ')' '{' casos '}'
    auto it_aux = it; // Respaldar estado del iterador
    if (ope_switch(it, end)) { // 'switch'
        if(parentesis_izq(it, end) && identificador(it, end) && parentesis_der(it, end) &&
            llave_izq(it, end) && casos(it, end) && llave_der(it, end)) {
            return true;
        }
    }else{
        it = it_aux; // Restaurar estado del iterador
        return false;
    }
    it = it_aux; // Restaurar estado del iterador
    return false;

}
// REGLAS PARA ESTRUCTURA WHILE: -------------------------------------------------------------------
bool analizador_sintactico::secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    if(ope_while(it, end) && parentesis_izq(it, end) && condicion(it, end) && parentesis_der(it, end) && llave_izq(it, end)){
        if(bloque(it, end) && llave_der(it, end)){
            return true; // La instrucción tiene un bloque válido
        }
    }
    it = it_aux; // Restaurar estado del iterador
    return false; // Si falta el bloque, la instrucción es inválida
}
// REGLAS PARA CONDICIONALES: ----------------------------------------------------------------------
bool analizador_sintactico::condicion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    // ope_relacional = "<", ">", "<=", ">=", ope_igualdad = "==", "!="
    if((identificador(it, end) || valor(it, end)) && (ope_relacional(it, end) || ope_igualdad(it, end)) && (identificador(it, end) || valor(it, end))){
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}
bool analizador_sintactico::secuencia_if(std::list<Componente>::iterator &it, std::list<Componente>::iterator end) {
    auto it_aux = it; // Respaldar estado del iterador
    if (condicional_if(it, end) && parentesis_izq(it, end) && condicion(it, end) && parentesis_der(it, end) &&
        llave_izq(it, end)) {
        if (bloque(it, end) && llave_der(it, end)) {
            if (condicional_else(it, end) && llave_izq(it, end)) {  // Verificar si hay un else
                if (bloque(it, end) && llave_der(it, end)) {
                    return true;
                }
                it--; // Regresar else si no se encontró una llave derecha
            }
            return true; // La instrucción tiene un bloque válido
        }
    }
    it = it_aux; // Restaurar estado del iterador
    return false;
}

// Inicio de validación de reglas
std::string analizador_sintactico::validar_inicio(std::list<Componente>& tokens) {
    auto it = tokens.begin();   // Iterador al inicio de la lista
    auto end = tokens.end();    // Iterador al final de la lista
    if(it!=end){
        Componente componente = *it;
        if(componente.get_token() != "Fin de cadena"){
            if(instruccion(it, end)){
                // La entrada es una instrucción válida
                return "La entrada es valida sintacticamente.";
            }
            else if(directiva(it, end)){
                // La entrada es una directiva válida
                return "La entrada es valida sintacticamente.";
            }
            else if(funcion(it, end)){
                // La entrada es una función válida
                return "La entrada es valida sintacticamente.";
            }
        }
    }
    std::string mensaje_error;
    mensaje_error += "-------------------- Error de sintaxis --------------------\n";
    mensaje_error += "Error en la regla: " + regla + "\n";
    mensaje_error += "Se recibió el token: " + ultimo_token_recibido + "\n";
    mensaje_error += "Token esperado: " + token_esp + "\n";
    mensaje_error += "-----------------------------------------------------------\n";

    std::cout << mensaje_error;

    return mensaje_error;
}
