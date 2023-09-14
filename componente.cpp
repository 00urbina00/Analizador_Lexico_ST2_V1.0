#include "componente.h"

Componente::Componente(const std::string& lexema, const std::string& token){
    nucleo = {{"token", token}, {"lexema", lexema}};
    id = -1;
    tipos_de_datos = {"int", "float", "void"};
    palabras_reservadas = {
        "case", "break", "continue", "return", "class",
        "public", "private", "protected", "const", "try", "except", "finally", "include",
        "new", "delete", "namespace", "template", "using", "typedef", "sizeof", "static",
        "virtual", "friend", "operator", "struct", "union", "this", "true", "false"
    };
    operadores_logicos = {"&&", "||", "!"};
    estructuras_de_control = {"while", "for", "do", "switch"};
    condicionales = {"if", "else", "elif"};
    operadores_relacionales = {"==", "<", ">", "<=", ">=", "!="};
    signos = {".", ",", ";"};
    set_token();
    set_id();
}
void Componente::set_token(){
    if (condicionales.find(nucleo["lexema"]) != condicionales.end()) {
        nucleo["token"] = "Condicional";
    }else if (tipos_de_datos.find(nucleo["lexema"]) != tipos_de_datos.end()) {
        nucleo["token"] = "tipo";
    }else if (palabras_reservadas.find(nucleo["lexema"]) != palabras_reservadas.end()) {
            nucleo["token"] = "Palabra Reservada";
    }else if (estructuras_de_control.find(nucleo["lexema"]) != estructuras_de_control.end()) {
            nucleo["token"] = "Estructura de Control";
    }
}
void Componente::set_id(){
    std::unordered_map<std::string, int> token_a_numero = {
        {"id",          0},      // Var1
        {"entero",      1},      // 1
        {"real",        2},      // 0.0
        {"cadena",      3},      // " "
        {"tipo",        4},      // int float void
        {"opSuma",      5},      // + -
        {"opMul",       6},      // * /
        {"opRelac",     7},      // <, <=, >, >=
        {"opOr",        8},      // ||
        {"opAnd",       9},      // &&
        {"opNot",       10},     // !
        {"opIgualdad",  11},     // ==, !=
        {";", 12},
        {",", 13},
        {"(", 14},
        {")", 15},
        {"{", 16},
        {"}", 17},
        {"=", 18},
        {"if", 19},
        {"while", 20},
        {"return", 21},
        {"else", 22},
        {"$", 23},
    };
    if(token_a_numero.find(nucleo["lexema"]) != token_a_numero.end()){
            id = token_a_numero[nucleo["lexema"]];
    }else if(token_a_numero.find(nucleo["token"]) != token_a_numero.end()){
            id = token_a_numero[nucleo["token"]];
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
