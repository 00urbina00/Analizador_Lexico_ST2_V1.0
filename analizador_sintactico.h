#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include <iostream>
#include <string>
#include <cctype>
#include <list>
#include "componente.h"


class analizador_sintactico
{
public:
    analizador_sintactico();
    bool validar_inicio(std::list<Componente>& tokens);
};

#endif // ANALIZADOR_SINTACTICO_H
