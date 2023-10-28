#include "componente.h"
// Definición estática de los diccionarios

std::unordered_set<std::string> tipos_de_datos;
std::unordered_set<std::string> palabras_reservadas;
std::unordered_set<std::string> operadores_logicos;
std::unordered_set<std::string> estructuras_de_control;
std::unordered_set<std::string> condicionales;
std::unordered_set<std::string> operadores_relacionales;
std::unordered_set<std::string> operadores_aritmeticos;
std::unordered_set<std::string> signos;
std::unordered_set<std::string> directivas;

void Componente::inicializar_diccionarios(){
    // Inicialización estática de los diccionarios
    tipos_de_datos = {"int", "float", "void", "string", "bool", "char"};
    palabras_reservadas = {
        "case", "break", "continue", "return", "class", "printf",
        "public", "private", "protected", "const", "try", "except", "finally", "include",
        "new", "delete", "namespace", "template", "using", "typedef", "sizeof", "static",
        "virtual", "friend", "operator", "struct", "union", "this", "true", "false", "empty",
        "std", "endl", "cin", "cout", "main", "const", "static"
    };
    operadores_logicos = {"&&", "||", "!"};
    estructuras_de_control = {"while", "for", "do", "switch"};
    condicionales = {"if", "else"};
    operadores_relacionales = {"==", "<", ">", "<=", ">=", "!="};
    operadores_aritmeticos = {"+", "-", "*", "/"};
    signos = {".", ",", ";", "(", ")", "{", "}"};
    directivas = {"define", "include", "ifdef", "ifndef", "endif"};
}

Componente::Componente(const std::string& lexema, const std::string& token){
    // Se crea un componente con el lexema y token que se regresa el lexico
    nucleo = {{"token", token}, {"lexema", lexema}};
    id = -1;
    // Llamadas a funciones para asignar el token y el id
    set_token();    
    set_id(); 
}
void Componente::set_token(){
    /*
        Esta función asigna el token correspondiente según el lexema en los diccionarios
        Utiliza conjuntos de lexemas para asignar el nombre del token
    */
    if (directivas.find(nucleo["lexema"]) != directivas.end()) {
        nucleo["token"] = "Directiva";
    }else if (condicionales.find(nucleo["lexema"]) != condicionales.end()) {
        nucleo["token"] = "Condicional";
    }else if (operadores_logicos.find(nucleo["lexema"]) != operadores_logicos.end()) {
        nucleo["token"] = "OpLogico";
    }else if (tipos_de_datos.find(nucleo["lexema"]) != tipos_de_datos.end()) {
        nucleo["token"] = "tipo";
    }else if (palabras_reservadas.find(nucleo["lexema"]) != palabras_reservadas.end()) {
        nucleo["token"] = "Palabra Reservada";
    }else if (estructuras_de_control.find(nucleo["lexema"]) != estructuras_de_control.end()) {
        nucleo["token"] = "Estructura de Control";
    }else if (signos.find(nucleo["lexema"]) != signos.end()) {
        nucleo["token"] = "Separador";
    }else if (operadores_relacionales.find(nucleo["lexema"]) != operadores_relacionales.end()) {
        nucleo["token"] = "opRelacional";
    }else if (operadores_aritmeticos.find(nucleo["lexema"]) != operadores_aritmeticos.end()) {
        nucleo["token"] = "opAritmetico";
    }
}
void Componente::set_id(){
    /*
        Esta función asigna el id correspondiente según el lexema del map
        Asigna id´s específicos para cada lexema
    */
    std::unordered_map<std::string, int> lex_to_num = {
        {"error", 0},
        {"id", 1},
        {"entero", 2},
        {"real", 3},
        {"cadena", 4},
        {"caracter", 5},
        {"int", 6},
        {"float", 7},
        {"void", 8},
        {"string", 9},
        {"char", 10},
        {"bool", 11},
        {"+", 12},
        {"-", 13},
        {"*", 14},
        {"/", 15},
        {"==", 16},
        {"!=", 17},
        {"<", 18},
        {">", 19},
        {"<=", 20},
        {">=", 21},
        {"||", 22},
        {"&&", 23},
        {"!", 24},
        {";", 25},
        {",", 26},
        {".", 27},
        {"#", 28},
        {"=", 29},
        {"if", 30},
        {"else", 31},
        {"while", 32},
        {"for", 33},
        {"switch", 34},
        {"true", 35},
        {"false", 36},
        {"{", 37},
        {"}", 38},
        {"(", 39},
        {")", 40},
        {"$", 41},
        {"Palabra Reservada", 42},
        {"Directiva", 43}
    };
    if(lex_to_num.find(nucleo["lexema"]) != lex_to_num.end()){
        id = lex_to_num[nucleo["lexema"]];
    }else if(lex_to_num.find(nucleo["token"]) != lex_to_num.end()){
        id = lex_to_num[nucleo["token"]];
    }
}

std::string Componente::get_lexema(){
    return nucleo["lexema"];
}
std::string Componente::get_token(){
    return nucleo["token"];
}
int Componente::get_id(){
    return id;
}
