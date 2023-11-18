#include "analizador_sintactico.h"

#include <utility>

// CONSTRUCTOR: -----------------------------------------------------------------------------------
analizador_sintactico::analizador_sintactico(){
    regla = "";
    token_esp = "";
    ultimo_token_recibido = "";
    id_regla = -1;
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
Regla analizador_sintactico::crea_regla(std::string rl, int idx = -1){
    Regla r(std::move(rl), idx);
    return r;
}
// REGLAS PARA TOKENS BASICOS: --------------------------------------------------------------------
bool analizador_sintactico::dos_puntos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Separador" && it->get_id() == 47){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Dos puntos", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Dos puntos", ":");
    reglas_invalidas.emplace_back(crea_regla("Dos puntos"));
    return false;
}

bool analizador_sintactico::coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 26){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Coma", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Coma", ",");
    reglas_invalidas.emplace_back(crea_regla("Coma"));
    return false;
}
bool analizador_sintactico::punto_coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 25){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Punto y coma", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Punto y coma", ";");
    reglas_invalidas.emplace_back(crea_regla("Punto y coma"));
    return false;
}
bool analizador_sintactico::llave_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 37){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Llave izquierda", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Llave izquierda", "{");
    reglas_invalidas.emplace_back(crea_regla("Llave izquierda"));
    return false;
}
bool analizador_sintactico::llave_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 38){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Llave derecha", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Llave derecha", "}");
    reglas_invalidas.emplace_back(crea_regla("Llave derecha"));
    return false;
}
bool analizador_sintactico::parentesis_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 39){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Parentesis izquierdo", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Parentesis izquierdo", "(");
    reglas_invalidas.emplace_back(crea_regla("Parentesis izquierdo"));
    return false;
}
bool analizador_sintactico::parentesis_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 40){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Parentesis derecho", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Parentesis derecho", ")");
    reglas_invalidas.emplace_back(crea_regla("Parentesis derecho"));
    return false;
}
bool analizador_sintactico::entero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "entero"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Entero", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Entero", "0");
    reglas_invalidas.emplace_back(crea_regla("Entero"));
    return false;
}
bool analizador_sintactico::real(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "real"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Real", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Real", "0.0");
    reglas_invalidas.emplace_back(crea_regla("Real"));
    return false;
}
bool analizador_sintactico::verdadero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 35) {
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Verdadero", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Verdadero", "true");
    reglas_invalidas.emplace_back(crea_regla("Verdadero"));
    return false;
}
bool analizador_sintactico::falso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 36) {
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Falso", ++id_regla));
        return true;
    }
    capturar_error(it, "Falso", "false");
    reglas_invalidas.emplace_back(crea_regla("Falso"));
    return false;
}
bool analizador_sintactico::tipo(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "tipo"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Tipo", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Tipo", "(int| float | char | string | bool | void)");
    reglas_invalidas.emplace_back(crea_regla("Tipo"));
    return false;
}
bool analizador_sintactico::ope_aritmeticos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "opAritmetico"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador Aritmetico", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Aritmetico", "(* | / | + | -)");
    reglas_invalidas.emplace_back(crea_regla("Operador Aritmetico"));
    return false;
}
bool analizador_sintactico::ope_relacional(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "<", ">", "<=", ">="
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() != 16 && it->get_id() != 17)){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador Relacional", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Relacional", "(< | > | <= | >=)");
    reglas_invalidas.emplace_back(crea_regla("Operador Relacional"));
    return false;
}
bool analizador_sintactico::ope_igualdad(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // == 16 | != 17
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() == 16 || it->get_id() == 17)){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador Igualdad", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Igualdad", "(== | !=)");
    reglas_invalidas.emplace_back(crea_regla("Operador Igualdad"));
    return false;
}
bool analizador_sintactico::ope_logicos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "&&", "||", "!"
    if (it != end && it->get_token() == "opLogico"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador Logico", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Logico", "(&& | || | !)");
    reglas_invalidas.emplace_back(crea_regla("Operador Logico"));
    return false;
}
bool analizador_sintactico::cadena(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "cadena"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Cadena", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Cadena", "\"cadena\"");
    reglas_invalidas.emplace_back(crea_regla("Cadena"));
    return false;
}
bool analizador_sintactico::caracter(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "caracter"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Caracter", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Caracter", "\'c\'");
    reglas_invalidas.emplace_back(crea_regla("Caracter"));
    return false;
}
bool analizador_sintactico::identificador(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "id"){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Identificador", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Identificador", "id");
    reglas_invalidas.emplace_back(crea_regla("Identificador"));
    return false;
}
// REGLAS PARA EXPRESIONES: -----------------------------------------------------------------------
bool analizador_sintactico::valor(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador

    if(entero(it, end) || real(it, end) || cadena(it, end) ||
                      caracter(it, end) || verdadero(it, end) || falso(it, end)){
        // reglas_validas.emplace_back(crea_regla("Valor", ++id_regla));
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    // reglas_invalidas.emplace_back(crea_regla("Valor"));
    return false;
}
// REGLAS DE DIRECTIVAS: --------------------------------------------------------------------------
bool analizador_sintactico::directiva(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Respaldar estado del iterador #include <iostream> | #include "iostream.h"
    auto pila_aux = lista_componentes;
    auto it_aux = it;
    if(it == end || it->get_token() != "Hashtag") {
        capturar_error(it, "Directiva", "#");
        reglas_invalidas.emplace_back(crea_regla("Directiva - #"));
        return false;
    }
    lista_componentes.push_back(*it);
    it++;  // Avanzar al siguiente token (Directiva)
    if(it == end || it->get_token() != "Directiva") {
        capturar_error(it, "Directiva", "include | define");
        reglas_invalidas.emplace_back(crea_regla("Directiva - include | define"));
        return false;
    }
    lista_componentes.push_back(*it);
    it++;  // Avanzar al siguiente token (cadena)
    if(it != end && it->get_token() == "cadena") {
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Directiva", ++id_regla));
        it++;  // Avanzar al siguiente token
        return true;
    }else if(it != end && it->get_token() == "opRelacional" && it->get_id() == 18){ // '<'
        lista_componentes.push_back(*it);
        it++;
        while(it != end && it->get_token() != "opRelacional") {
            lista_componentes.push_back(*it);
            it++;
        }
        if(it != end && it->get_token() == "opRelacional" && it->get_id() == 19) { // '>'
            lista_componentes.push_back(*it);
            reglas_validas.emplace_back(crea_regla("Directiva", ++id_regla));
            it++;
            return true;
        }
    }
    lista_componentes = pila_aux; // Restaurar estado de la pila
    it = it_aux; // Restaurar estado del iterador
    capturar_error(it, "Directiva", "cadena || <valor>");
    reglas_invalidas.emplace_back(crea_regla("Directiva - cadena || <valor>"));
    return false;
}
// REGLAS DE ASIGNACION: --------------------------------------------------------------------------
bool analizador_sintactico::op_igual(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "opRelacional" && it->get_id() == 29){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador Igual", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Operador Igual", "=");
    reglas_invalidas.emplace_back(crea_regla("Operador Igual"));
    return false;
}
bool analizador_sintactico::asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end) {
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    // Verificar si el primer token es un identificador
    if(!identificador(it, end)){
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Asignacion - Identificador"));
        return false;
    }
    // Verificar si a continuación hay un operador de asignación
    if(!op_igual(it, end)){
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Asignacion - Operador Igual"));
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
                lista_componentes = pila_aux; // Restaurar estado de la pila
                // reglas_invalidas.emplace_back(crea_regla("Asignacion - Operador Aritmetico"));
                return false;
            }
        }
        // reglas_validas.emplace_back(crea_regla("Asignacion", ++id_regla));
        return true;
    }
    // Si no se encontró un valor válido, entonces la asignación es incorrecta
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Asignacion - Valor"));
    return false;
}
// REGLAS PARA COMPONENTES DE ESTRUCTURAS: ---------------------------------------------------------
bool analizador_sintactico::condicional_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 30){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Condicional if", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "if");
    reglas_invalidas.emplace_back(crea_regla("Condicional if"));
    return false;
}
bool analizador_sintactico::condicional_else(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 31){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Condicional else", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "else");
    reglas_invalidas.emplace_back(crea_regla("Condicional else"));
    return false;
}
bool analizador_sintactico::ope_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 32){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador while", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Operador while", "while()");
    reglas_invalidas.emplace_back(crea_regla("Operador while"));
    return false;
}
bool analizador_sintactico::ope_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 34){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador switch", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Operador switch", "switch()");
    reglas_invalidas.emplace_back(crea_regla("Operador switch"));
    return false;
}
bool analizador_sintactico::ope_case(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 46) { // 'case'
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Operador case", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Operador case", "case");
    reglas_invalidas.emplace_back(crea_regla("Operador case"));
    return false;
}
// REGLAS DE INSTRUCCIONES: ------------------------------------------------------------------------
bool analizador_sintactico::instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    // Opciones para instruccion
    if (funcion(it, end) || secuencia_if(it, end) || secuencia_while(it, end) || secuencia_switch(it, end) || directiva(it, end)) {
        // reglas_validas.emplace_back(crea_regla("Instruccion", ++id_regla));
        return true;
    }
    if (declarar_variable(it, end) || llamada_funcion(it, end) || retorno(it, end) || romper(it, end) || asignacion(it, end)) {
        if (punto_coma(it, end)) {
            // reglas_validas.emplace_back(crea_regla("Instruccion", ++id_regla));
            return true;
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Instruccion"));
    return false;
}
bool analizador_sintactico::bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    bool bandera = false;
    while(instruccion(it, end)) {
        // reglas_validas.emplace_back(crea_regla("Bloque", ++id_regla));
        bandera = true;
    }
    if(!bandera){
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Bloque"));
        it = it_aux; // Restaurar estado del iterador
    }
    return bandera;
}
bool analizador_sintactico::declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Verificar si el primer token no es un tipo
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila

    if(!tipo(it, end)){
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Declarar variable - Tipo"));
        return false;
    }
    // Verificar si a continuación hay una asignacion
    if(asignacion(it, end)){
        // reglas_validas.emplace_back(crea_regla("Declarar variable", ++id_regla));
        return true;
    }
    // Verificar si a continuación hay un identificador
    if(identificador(it, end)){
        // reglas_validas.emplace_back(crea_regla("Declarar variable", ++id_regla));
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Declarar variable - Identificador"));
    return false; // La estructura no coincide con la regla declarar_variable
}
bool analizador_sintactico::romper(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){ // break
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 45){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Romper ciclo", ++id_regla));
        it++;
        return true;
    }
    capturar_error(it, "Romper ciclo", "break");
    reglas_invalidas.emplace_back(crea_regla("Romper ciclo"));
    return false;
}
bool analizador_sintactico::retorno(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 44){
        lista_componentes.push_back(*it);
        it++;
        if(valor(it, end) || identificador(it, end)){
            reglas_validas.emplace_back(crea_regla("Retorno", ++id_regla));
            return true;
        }
        reglas_validas.emplace_back(crea_regla("Retorno", ++id_regla));
        return true;
    }else{
        capturar_error(it, "Retorno", "return");
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        reglas_invalidas.emplace_back(crea_regla("Retorno"));
        return false;
    }
}

// REGLAS DE FUNCIONES: ----------------------------------------------------------------------------
bool analizador_sintactico::parametro(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    if(tipo(it, end)){
        if(identificador(it, end)){
            // reglas_validas.emplace_back(crea_regla("Parametro", ++id_regla));
            return true;
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Parametro"));
    return false;
}
bool analizador_sintactico::llamada_funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
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
            // reglas_validas.emplace_back(crea_regla("Llamada a funcion", ++id_regla));
            return true; // La función se procesó correctamente
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Llamada a funcion"));
    return false; // La estructura no coincide con la regla de función
}
bool analizador_sintactico::funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
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
                    // reglas_validas.emplace_back(crea_regla("Funcion", ++id_regla));
                    return true; // La función se procesó correctamente
                }
                it--; // Regresar si no se encontró un bloque o paréntesis derecho
            }
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Funcion"));
    return false; // La estructura no coincide con la regla de función
}
// REGLAS DE ESTRUCTURAS
// REGLAS DE ESTRUCTURA SWITCH: --------------------------------------------------------------------
bool analizador_sintactico::caso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    // 'case' valor ':' bloque 'break' ';'
    if(ope_case(it, end)){ // 'case'
        if(identificador(it, end) || (entero(it, end)) && dos_puntos(it, end)){
            // Procesar el bloque y el 'break'
            if (bloque(it, end) && romper(it, end) && punto_coma(it, end)){
                // reglas_validas.emplace_back(crea_regla("Caso", ++id_regla));
                return true;
            }
        }
    }else{
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Caso - case"));
        return false;
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Caso - estructura"));
    return false;
}
bool analizador_sintactico::defecto(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 48){
        lista_componentes.push_back(*it);
        reglas_validas.emplace_back(crea_regla("Defecto", ++id_regla));
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Defectos", "default");
    reglas_invalidas.emplace_back(crea_regla("Defecto"));
    return false;
}
bool analizador_sintactico::casos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    bool casos_validos = false;  // Variable para verificar si se ha encontrado al menos un caso válido
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
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
            // reglas_validas.emplace_back(crea_regla("Casos", ++id_regla));
            return true;
        }
    }
    if(!casos_validos){
        lista_componentes = pila_aux; // Restaurar estado de la pila
        it = it_aux; // Restaurar estado del iterador
        // reglas_invalidas.emplace_back(crea_regla("Casos - case | default"));
    }
    // El bucle terminará cuando no se encuentren más casos válidos
    return casos_validos; // Devolver true si se encontró al menos un caso válido
}
bool analizador_sintactico::secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // 'switch' '(' identificador ')' '{' casos '}'
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    if (ope_switch(it, end)) { // 'switch'
        if(parentesis_izq(it, end) && identificador(it, end) && parentesis_der(it, end) &&
            llave_izq(it, end) && casos(it, end) && llave_der(it, end)) {
            // reglas_validas.emplace_back(crea_regla("Secuencia switch", ++id_regla));
            return true;
        }
    }else{
        it = it_aux; // Restaurar estado del iterador
        lista_componentes = pila_aux; // Restaurar estado de la pila
        // reglas_invalidas.emplace_back(crea_regla("Secuencia switch - switch"));
        return false;
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Secuencia switch - estructura"));
    return false;

}
// REGLAS PARA ESTRUCTURA WHILE: -------------------------------------------------------------------
bool analizador_sintactico::secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    if(ope_while(it, end) && parentesis_izq(it, end) && condicion(it, end) && parentesis_der(it, end) && llave_izq(it, end)){
        if(bloque(it, end) && llave_der(it, end)){
            // reglas_validas.emplace_back(crea_regla("Secuencia while", ++id_regla));
            return true; // La instrucción tiene un bloque válido
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // reglas_invalidas.emplace_back(crea_regla("Secuencia while"));
    return false; // Si falta el bloque, la instrucción es inválida
}
// REGLAS PARA CONDICIONALES: ----------------------------------------------------------------------
bool analizador_sintactico::condicion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    // ope_relacional = "<", ">", "<=", ">=", ope_igualdad = "==", "!="
    if((identificador(it, end) || valor(it, end)) && (ope_relacional(it, end) || ope_igualdad(it, end)) && (identificador(it, end) || valor(it, end))){
        // // reglas_validas.emplace_back(crea_regla("Condicion", ++id_regla));
        return true;
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // // reglas_invalidas.emplace_back(crea_regla("Condicion"));
    return false;
}
bool analizador_sintactico::secuencia_if(std::list<Componente>::iterator &it, std::list<Componente>::iterator end) {
    auto it_aux = it; // Respaldar estado del iterador
    auto pila_aux = lista_componentes; // Respaldar estado de la pila
    if (condicional_if(it, end) && parentesis_izq(it, end) && condicion(it, end) && parentesis_der(it, end) &&
        llave_izq(it, end)) {
        if (bloque(it, end) && llave_der(it, end)) {
            if (condicional_else(it, end) && llave_izq(it, end)) {  // Verificar si hay un else
                if (bloque(it, end) && llave_der(it, end)) {
                    // // reglas_validas.emplace_back(crea_regla("Secuencia if", ++id_regla));
                    return true;
                }
                it--; // Regresar else si no se encontró una llave derecha
            }
            // // reglas_validas.emplace_back(crea_regla("Secuencia if", ++id_regla));
            return true; // La instrucción tiene un bloque válido
        }
    }
    it = it_aux; // Restaurar estado del iterador
    lista_componentes = pila_aux; // Restaurar estado de la pila
    // // reglas_invalidas.emplace_back(crea_regla("Secuencia if"));
    return false;
}
std::string analizador_sintactico::mostrar_tokens_en_lista(){
    std::string info_concatenada = "Reglas validas:\n";
    for (auto& r : reglas_validas) {
        info_concatenada += r.obtener_info() + "\n"; // Puedes cambiar el formato según tu necesidad
    }
    /* info_concatenada += "\nReglas invalidas:\n";
    for (auto& r : reglas_invalidas) {
        info_concatenada += r.obtener_info() + "\n"; // Puedes cambiar el formato según tu necesidad
    }
     */
    return info_concatenada;
}
// Inicio de validación de reglas
std::string analizador_sintactico::validar_inicio(std::list<Componente>& tokens){
    auto it = tokens.begin();   // Iterador al inicio de la lista
    auto end = tokens.end();    // Iterador al final de la lista
    lista_componentes.clear();   // Limpiar la pila de componentes
    bool bandera = false;
    auto it_backup = it;  // Respaldar el iterador inicial
    while(it!=end){
        Componente componente = *it;
        if (componente.get_token() != "Fin de cadena") {
            if (instruccion(it, end)) {
                // Regla cumplida, realizar acciones necesarias
                bandera = true;
                it_backup = it;  // Actualizar el iterador de respaldo
            } else {
                // Regla no cumplida, avanzar al siguiente componente
                ++it;
            }
        } else {
            // Fin de cadena, avanzar al siguiente componente
            ++it;
        }
    }

// Restaurar el iterador al último punto de respaldo
    it = it_backup;
    if(bandera) {
        return "La entrada es valida sintacticamente. \n";// \n"  + mostrar_tokens_en_lista();
    } else {
        std::string mensaje_error;
        mensaje_error += "-------------------- Error de sintaxis --------------------\n";
        mensaje_error += "Error en la regla:   " + regla + "\n";
        mensaje_error += "Token esperado:      " + token_esp + "\n";
        mensaje_error += "Se recibió el token: " + ultimo_token_recibido + "\n";
        mensaje_error += "-----------------------------------------------------------\n";

        // std::cout << mostrar_tokens_en_lista(lista_componentes)<<std::endl;

        return mensaje_error + "\n";// + mostrar_tokens_en_lista();
    }
}
std::list<Componente> analizador_sintactico::obtener_lista_componentes(){
    return lista_componentes;
}