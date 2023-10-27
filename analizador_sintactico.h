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
    bool analizar(std::string cadena);
    bool declarar_variable();
    bool analizar_asignacion(std::list<Componente>& tokens);
    bool validar_inicio(std::list<Componente>& tokens);

private:
    size_t posicion;
};

#endif // ANALIZADOR_SINTACTICO_H
