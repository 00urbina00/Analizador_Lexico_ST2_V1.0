#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <iostream>
#include <list>
#include "componente.h"


class analizador_lexico
{
public:
    analizador_lexico();
    std::list<Componente> analizar_lexicamente(std::string cadena);
private:
    enum Estados {
        INICIAL,
        IDENTIFICADOR,
        OP_AND,
        OP_OR,
        OP_RELAC,
        CADENA,
        CARACTER,
        ENTERO,
        REAL,
        FINAL
    };
    static bool issymbol(char caracter);
    static bool isoperator(char caracterstatic );
    static bool isrelat(char caracter);

    static std::string symbol_token(char simbolostatic);
    static std::string arithmetic_ope_token(char simbolostatic);
    static std::string relational_ope_token(char simbolo);

    std::list<Componente> componentes;
};

#endif // ANALIZADOR_LEXICO_H
