#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include <iostream>
#include <string>
#include <cctype>
#include <list>
#include <utility>
#include "componente.h"
#include <stack>
#include <functional>

class Regla{
public:
    Regla(std::string rl, int idx) : regla(std::move(rl)), id(idx) {}
    std::string regla;
    int id;
    std::string obtener_info(){
        return "Nombre: " + regla + ", ID: " + std::to_string(id);
    }
};


class analizador_sintactico
{
public:
    analizador_sintactico();
    std::string validar_inicio(std::list<Componente>& tokens);
    static void print_elemento(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);

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
    bool ope_case(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);
    bool llamada_funcion(std::list<Componente>::iterator& it, std::list<Componente>::iterator end);

    void capturar_error(std::list<Componente>::iterator& it, std::string regla, std::string token_esperado);

    std::string mostrar_tokens_en_lista();

    static Regla crea_regla(std::string rl, int idx);

    std::list<Componente> obtener_lista_componentes();

private:
    std::string regla;
    std::string token_esp;
    std::string ultimo_token_recibido;
    std::list<Componente> lista_componentes;
    std::list<Regla> reglas_validas;
    std::list<Regla> reglas_invalidas;
    int id_regla;
};

#endif // ANALIZADOR_SINTACTICO_H
