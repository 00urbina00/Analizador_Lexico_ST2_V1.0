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
    std::string validar_inicio(std::list<Componente>& tokens);
    void print_elemento(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool directiva(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool entero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool real(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool verdadero(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool falso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool tipo(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_aritmeticos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_relacional(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_igualdad(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_logicos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool cadena(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool caracter(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool identificador(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool valor(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool op_igual(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool condicional_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool condicional_else(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool punto_coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool llave_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool llave_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool parentesis_izq(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool parentesis_der(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool asignacion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool declarar_variable(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool romper(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool retorno(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool coma(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool parametro(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool secuencia_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool condicion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool instruccion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool bloque(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool secuencia_if(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool secuencia_while(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool caso(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool dos_puntos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool defecto(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool casos(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool ope_switch(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);

    void capturar_error(std::list<Componente>::iterator& it, std::string regla, std::string token_esperado);

private:
    std::string regla;
    std::string token_esp;
    std::string ultimo_token_recibido;
};

#endif // ANALIZADOR_SINTACTICO_H
