#include "analizador_lexico.h"

analizador_lexico::analizador_lexico(){
    componentes = std::list<Componente>();

}

bool analizador_lexico::issymbol(char caracter){
    return (caracter == '(' || caracter == ')' || caracter == '{' || caracter == '}' || caracter == '$' || caracter == ',' || caracter == ';' || caracter == '.');
}
bool analizador_lexico::isoperator(char caracter){
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/');
}
std::string analizador_lexico::token_symbol(char simbolo){
    std::string token;
    if(simbolo == '('){
        token = "parIzq";
    }else if(simbolo == ')'){
        token = "parDer";
    }else if(simbolo == '{'){
        token = "llaveIzq";
    }else if(simbolo == '}'){
        token = "llaveDer";
    }else if(simbolo == ';'){
        token = "puntoComa";
    }else if(simbolo == ','){
        token = "coma";
    }else if(simbolo == '.'){
        token = "punto";
    }else if(simbolo == '$'){
        token = "pesos";
    }return token;
}
std::string analizador_lexico::token_operator(char simbolo){
    std::string token;
    if(simbolo == '+'){
        token = "opSuma";
    }else if(simbolo == '-'){
        token = "opResta";
    }else if(simbolo == '*'){
        token = "opMultiplicacion";
    }else if(simbolo == '/'){
        token = "opDivision";
    }return token;
}
std::list<Componente> analizador_lexico::analizar_lexicamente(std::string cadena){
    componentes.clear();
    if(cadena.empty()){
        return componentes; // La cadena esta vacia
    }
    cadena += "$";
    int indice = 0;
    int estado = INICIAL;
    while(indice <= (cadena.length()-1) && estado == INICIAL){  // Recorre la cadena caracter a caracter
        std::string lexema = "";
        std::string token = "error";
        while(indice <= (cadena.length()-1) && estado != FINAL){   // Recorre las posibilidades para cada caracter
            switch(estado){
                case INICIAL:
                    if(isspace(cadena[indice])){    // Ignoramos los espacios
                        estado = INICIAL;
                    }else if(isalpha(cadena[indice]) || (cadena[indice] == '_')){   // \w, '_'
                        estado = IDENTIFICADOR;     // Saltamos al estado IDENTIFICADOR
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "identificador";    // Este lexema es un identificador
                    }else if(cadena[indice] == '"'){
                        estado = CADENA;            // Saltamos al estado
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        // Este lexema puede ser cadena
                    }else if(cadena[indice] == '\''){
                        estado = CARACTER;          // Saltamos al estado
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        // Este lexema puede ser caracter
                    }else if(cadena[indice] == '&'){
                        estado = OP_AND;            // Saltamos al estado 5
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opAnd";            // Este lexema es un operador and
                    }else if(cadena[indice] == '|'){
                        estado = OP_OR;             // Saltamos al estado 6
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opOr";             // Este lexema es un operador or
                    }else if(cadena[indice] == '!'){
                        estado = OP_RELAC;          // Saltamos al estado 7
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opNot";            // Este lexema es un operador not
                    }else if(cadena[indice] == '='){
                        estado = OP_RELAC;          // Saltamos al estado 7
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "=";                // Este lexema es un operador asignacion =
                    }else if(cadena[indice] == '<'){
                        estado = OP_RELAC;          // Saltamos al estado 7
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opRelac";          // Este lexema es un operador mayor que
                    }else if(cadena[indice] == '>'){
                        estado = OP_RELAC;          // Saltamos al estado 7
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opRelac";          // Este lexema es un operador menor que
                    }else if(isdigit(cadena[indice])){                             //
                        estado = ENTERO;            // Saltamos al estado 19
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "entero";       // Este lexema es un entero
                    }else if(issymbol(cadena[indice])){
                        estado = FINAL;            // Saltamos al estado 20
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = token_symbol(cadena[indice]);       // Este lexema es parentesis izquierdo
                    }else if(isoperator(cadena[indice])){
                        estado = FINAL;            // Saltamos al estado 20
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = token_operator(cadena[indice]);       // Este lexema es parentesis izquierdo
                    }
                    ++indice;
                    break;
                case IDENTIFICADOR:
                    if(isalpha(cadena[indice]) || isdigit(cadena[indice]) || cadena[indice] == '_'){
                        estado = IDENTIFICADOR;             // Saltamos al estado 4
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "id";           // Este lexema es un identificador
                        ++indice;
                    }else{      // Se recibe otro caracter, se termina la cadena
                        estado = FINAL;
                    }
                    break;
                case OP_AND:
                    if(cadena[indice] == '&'){
                        estado = FINAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opAnd";
                        ++indice;
                    }else{
                        estado = FINAL;
                        token = "error";
                    }
                    break;
                case OP_OR:
                    if(cadena[indice] == '|'){
                        estado = FINAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opOr";
                        ++indice;
                    }else{
                        estado = FINAL;
                        token = "error";
                    }
                    break;
                    case OP_RELAC:
                    if(cadena[indice] == '='){  // La cadena es "==, <=, >=, !="
                        estado = FINAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "opRelac";
                        ++indice;
                    }else{                      // La cadena es un operador "=, <, >, !"
                        estado = FINAL;
                    }
                    break;
                case CADENA:
                    if(cadena[indice] == '"'){     // Se recibe la comilla de cierre
                        estado = FINAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "cadena";
                        ++indice;
                    }
                    else if(isalpha(cadena[indice]) || isdigit(cadena[indice]) || (ispunct(cadena[indice]) && cadena[indice])){     // la cadena contiene numeros o letras o simbolos
                        estado = CADENA; // Nos quedamos en el mismo estado
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        ++indice;
                    }
                    else if(cadena[indice] == '\n'){    // La cadena tiene un salto de linea (se omite)
                        estado = CADENA; // Nos quedamos en el mismo estado
                        ++indice;
                    }
                    else if(isspace(cadena[indice])){   // la cadena contiene espacios o tabulaciones
                        estado = CADENA;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        ++indice;
                    }else{
                        estado = FINAL;
                    }break;
                case CARACTER:
                    if(cadena[indice] == '\''){     // Se recibe la comilla de cierre
                        estado = FINAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "caracter";
                        ++indice;
                    }
                    else if(isalpha(cadena[indice]) || isdigit(cadena[indice]) || (ispunct(cadena[indice]) && cadena[indice])){     // la cadena contiene numeros o letras o simbolos
                        estado = CARACTER; // Nos quedamos en el mismo estado
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        ++indice;
                    }
                    else if(cadena[indice] == '\n'){    // La cadena tiene un salto de linea (se omite)
                        estado = CARACTER; // Nos quedamos en el mismo estado
                        ++indice;
                    }
                    else if(isspace(cadena[indice])){   // la cadena contiene espacios o tabulaciones
                        estado = CARACTER;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        ++indice;
                    }else{
                        estado = FINAL;
                    }break;
                case ENTERO:
                    if(isdigit(cadena[indice])){
                        estado = ENTERO;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "entero";
                        ++indice;
                    }else if(cadena[indice] == '.'){    // Se recibe un punto
                        estado = REAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "real";
                        ++indice;
                    }else{
                        estado = FINAL;
                    }break;
                case REAL:
                    if(isdigit(cadena[indice])){
                        estado = REAL;
                        lexema += cadena[indice];   // Concatenamos el caracter actual
                        token = "real";
                        ++indice;
                    }else{
                        estado = FINAL;
                    }break;
                default:break;
            }
        }
        estado = INICIAL;
        Componente componente = Componente(lexema, token);
        componentes.push_back(componente);
    }
    return componentes;
}
