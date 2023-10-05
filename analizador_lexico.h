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
    bool issymbol(char caracter);
    bool isoperator(char caracter);
    std::string token_symbol(char simbolo);
    std::string token_operator(char simbolo);
    std::list<Componente> componentes;
};

#endif // ANALIZADOR_LEXICO_H
