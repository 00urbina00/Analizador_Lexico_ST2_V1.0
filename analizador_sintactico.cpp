#include "analizador_sintactico.h"


analizador_sintactico::analizador_sintactico(){
    regla = "";
    token_esp = "";
    ultimo_token_recibido = "";
}

void analizador_sintactico::capturar_error(std::list<Componente>::iterator& it, std::string rule, std::string token_esperado){
    Componente componente = *it;
    regla = rule;
    token_esp = token_esperado;
    ultimo_token_recibido = componente.get_token();
}

void analizador_sintactico::print_elemento(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it!=end){
        Componente elemento = *it;
        std::cout<<"El elemento actual es: "<<elemento.get_lexema()<<",  token: "<<elemento.get_token()<<", Id: "<<elemento.get_id()<<std::endl;
    }
}

// REGLAS ESTATICAS: -------------------------------------------------------------------------------
bool analizador_sintactico::directiva(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it == end || it->get_token() != "Hashtag") {
        capturar_error(it, "Directiva", "Hashtag");
        return false;
    }
    it++;  // Avanzar al siguiente token (Directiva)
    if(it == end || it->get_token() != "Directiva") {
        capturar_error(it, "Directiva", "Directiva");
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
    capturar_error(it, "Directiva", "caden || <valor>");
    return false;
}
bool analizador_sintactico::entero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "entero"){
        it++;
        return true;
    }
    capturar_error(it, "Entero", "entero");
    return false;
}
bool analizador_sintactico::real(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "real"){
        it++;
        return true;
    }
    capturar_error(it, "Real", "real");
    return false;
}
bool analizador_sintactico::verdadero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 35) {
        it++;
        std::cout<<"Se leyo un valor verdadero valido.."<<std::endl;
        return true;
    }
    std::cout<<"No hubo un valor verdadero valido.."<<std::endl;
    capturar_error(it, "Verdadero", "Palabra Reservada");
    return false;
}
bool analizador_sintactico::falso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 36) {
        it++;
        std::cout<<"Se leyo un valor falso valido.."<<std::endl;
        return true;
    }
    std::cout<<"No hubo un valor falso valido... el valor actual fue: "<<it->get_token()<<" Con id: "<<it->get_id()<<std::endl;
    capturar_error(it, "Falso", "Palabra Reservada");
    return false;
}
bool analizador_sintactico::tipo(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "tipo"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Tipo", "tipo");
    return false;
}
bool analizador_sintactico::ope_aritmeticos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "opAritmetico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Aritmetico", "opAritmetico");
    return false;
}
bool analizador_sintactico::ope_relacional(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "<", ">", "<=", ">="
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() != 16 && it->get_id() != 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Relacional", "opRelacional");
    return false;
}
bool analizador_sintactico::ope_igualdad(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // == 16 | != 17
    if (it != end && it->get_token() == "opRelacional" && (it->get_id() == 16 || it->get_id() == 17)){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Igualdad", "opRelacional");
    return false;
}
bool analizador_sintactico::ope_logicos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // "&&", "||", "!"
    if (it != end && it->get_token() == "opLogico"){
        it++; // Avanzar al siguiente token
        return true;
    }
    capturar_error(it, "Operador Logico", "opLogico");
    return false;
}
bool analizador_sintactico::cadena(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "cadena"){
        it++;
        return true;
    }
    capturar_error(it, "Cadena", "cadena");
    return false;
}
bool analizador_sintactico::caracter(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "caracter"){
        it++;
        return true;
    }
    capturar_error(it, "Caracter", "caracter");
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
bool analizador_sintactico::valor(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(entero(it, end) || real(it, end) || cadena(it, end) ||
                      caracter(it, end) || verdadero(it, end) || falso(it, end)){
        std::cout<<"Se leyo un Valor valido.."<<std::endl;
        return true;
    }
    std::cout<<"No hubo un valor valido.."<<std::endl;
    return false;
}
bool analizador_sintactico::op_igual(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "opRelacional" && it->get_id() == 29){
        it++;
        return true;
    }
    capturar_error(it, "Operador Igual", "opRelacional");
    return false;
}
bool analizador_sintactico::condicional_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 30){
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "Condicional");
    return false;
}
bool analizador_sintactico::condicional_else(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Condicional" && it->get_id() == 31){
        it++;
        return true;
    }
    capturar_error(it, "Condicional if", "Condicional");
    return false;
}
bool analizador_sintactico::punto_coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 25){
        it++;
        return true;
    }
    capturar_error(it, "Punto y coma", "Separador");
    return false;
}
bool analizador_sintactico::llave_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 37){
        it++;
        return true;
    }
    capturar_error(it, "Llave izquierda", "Separador");
    return false;
}
bool analizador_sintactico::llave_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 38){
        it++;
        return true;
    }
    capturar_error(it, "Llave derecha", "Separador");
    return false;
}
bool analizador_sintactico::parentesis_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 39){
        it++;
        return true;
    }
    capturar_error(it, "Parentesis izquierdo", "Separador");
    return false;
}
bool analizador_sintactico::parentesis_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 40){
        it++;
        return true;
    }
    capturar_error(it, "Parentesis derecho", "Separador");
    return false;
}
bool analizador_sintactico::ope_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 32){
        it++;
        return true;
    }
    capturar_error(it, "Operador while", "Estructura de Control");
    return false;
}
bool analizador_sintactico::ope_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Estructura de Control" && it->get_id() == 34){
        it++;
        return true;
    }
    capturar_error(it, "Operador switch", "Estructura de Control");
    return false;
}
bool analizador_sintactico::asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end) {
    // Verificar si el primer token es un identificador
    if(!identificador(it, end)){
        return false;
    }
    std::cout<<"Se leyo un identificador valido.."<<std::endl;
    // Verificar si a continuación hay un operador de asignación
    if(!op_igual(it, end)){
        it--; // Se regresa luego de haber consumido el id
        return false;
    }
    std::cout<<"Se leyo un operador igual valido.."<<std::endl;
    // Verificar si a continuación hay un valor (que puede ser un entero o un identificador)
    if(valor(it, end) || identificador(it, end)){
        std::cout<<"Se leyo un un valor valido.."<<std::endl;
        return true;
    }
    // Si no se encontró un valor válido, entonces la asignación es incorrecta
    return false;
}
bool analizador_sintactico::declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // Verificar si el primer token no es un tipo
    if(!tipo(it, end)){
        return false;
    }
    std::cout<<"Se leyo un tipo valido.."<<std::endl;
    // Verificar si a continuación hay una asignacion
    if(asignacion(it, end)){
        return true;
    }
    // Verificar si a continuación hay un identificador
    if(identificador(it, end)){
        return true;
    }
    return false; // La estructura no coincide con la regla declarar_variable
}
bool analizador_sintactico::romper(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){ // break
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 45){
        it++;
        return true;
    }
    capturar_error(it, "Romper ciclo", "Palabra Reservada");
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
        capturar_error(it, "Retorno", "Palabra Reservada");
        return false;
    }
    return false;

}
bool analizador_sintactico::coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(it != end && it->get_token() == "Separador" && it->get_id() == 26){
        it++;
        return true;
    }
    capturar_error(it, "Coma", "Separador");
    return false;
}
bool analizador_sintactico::parametro(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(tipo(it, end)){
        if(identificador(it, end)){
            return true;
        }
    }
    return false;
}
bool analizador_sintactico::dos_puntos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Separador" && it->get_id() == 47){
        return true;
    }
    capturar_error(it, "Dos puntos", "Separador");
    return false;
}
bool analizador_sintactico::defecto(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 48){
        return true;
    }
    capturar_error(it, "Defectos", "Palabra Reservada");
    return false;
}
bool analizador_sintactico::caso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // 'case' valor ':' bloque 'break' ';'
    if(it != end && it->get_token() == "Palabra Reservada" && it->get_id() == 46){ // 'case'
        it++;
        if(identificador(it, end) || (entero(it, end)) && dos_puntos(it, end)){
            // Procesar el bloque y el 'break'
            if (bloque(it, end) && romper(it, end) && punto_coma(it, end)){
                return true;
            }
        }
    }else{
        capturar_error(it, "Case", "Palabra Reservada");
        return false;
    }
    return false;
}
bool analizador_sintactico::casos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
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
        capturar_error(it, "Casos", "caso | defecto | Separador | bloque | romper");
    }
    // El bucle terminará cuando no se encuentren más casos válidos
    return casos_validos; // Devolver true si se encontró al menos un caso válido
}

bool analizador_sintactico::secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    // 'switch' '(' identificador ')' '{' casos '}'
    if (ope_switch(it, end)) { // 'switch'
        it++;
        if(parentesis_izq(it, end) && identificador(it, end) && parentesis_der(it, end) &&
            llave_izq(it, end) && casos(it, end) && llave_der(it, end)) {
            return true;
        }
    }else{
        capturar_error(it, "Secuencia switch", "Palabra Reservada | Separador | identificador | Estructura de control");
        return false;
    }
    return false;

}
bool analizador_sintactico::funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if (tipo(it, end) && identificador(it, end) && parentesis_izq(it, end)) {
        // Procesar al menos un parámetro
        if (parametro(it, end)) {
            // Usar un bucle while para procesar múltiples parámetros
            while(coma(it, end)) {
                if (!parametro(it, end)) {
                    return false; // Error en la sintaxis del parámetro
                }
            }
            if(parentesis_der(it, end) && llave_izq(it, end) && bloque(it, end) && llave_der(it, end)) {
                return true; // La función se ha procesado correctamente
            }
        }else if(parentesis_der(it, end) && llave_izq(it, end) && bloque(it, end) && llave_der(it, end)) {
            return true;
        }
    }
    return false; // La estructura no coincide con la regla de función
}
bool analizador_sintactico::condicion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if((identificador(it, end) || valor(it, end)) && ope_relacional(it, end) && (identificador(it, end) || valor(it, end))){
        return true;
    }
    return false;
}
bool analizador_sintactico::instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(declarar_variable(it, end) || retorno(it, end) || romper(it, end) || asignacion(it, end)){
        if(punto_coma(it, end)){
            return true;
        }
    }
    if(secuencia_if(it, end) || secuencia_while(it, end) || secuencia_switch(it, end)){
        return true;
    }
    return false;
}
bool analizador_sintactico::bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    bool bandera = false;
    while(instruccion(it, end)) {
        bandera = true;
    }
    if(!bandera){
        capturar_error(it, "Bloque", "instruccion");
    }
    return bandera;
}
bool analizador_sintactico::secuencia_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(condicional_if(it,end) && parentesis_izq(it,end) && condicion(it, end) && parentesis_der(it,end) && llave_izq(it,end)){
        if(bloque(it, end)){
            if(llave_der(it,end)){
                return true;
            }
        }else{
            if(llave_der(it,end)){
                return true;
            }
        }
    }
    return false;
}
bool analizador_sintactico::secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end){
    if(ope_while(it, end) && parentesis_izq(it, end) && condicion(it, end) && parentesis_der(it, end) && llave_izq(it, end)){
        if(bloque(it, end) && llave_der(it, end)){
            return true; // La instrucción tiene un bloque válido
        }
    }
    return false; // Si falta el bloque, la instrucción es inválida
}
// Inicio de validación de reglas
std::string analizador_sintactico::validar_inicio(std::list<Componente>& tokens) {
    auto it = tokens.begin();   // Iterador al inicio de la lista
    auto end = tokens.end();    // Iterador al final de la lista
    if(it!=end){
        Componente componente = *it;
        if(componente.get_token() != "Fin de cadena"){
            if(instruccion(it, end) || directiva(it, end) || funcion(it, end)){
                return "La entrada proporcionada es valida!!!";
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
