#ifndef COMPONENTE_H
#define COMPONENTE_H

#include <iostream>
#include <unordered_set>
#include <unordered_map>

class Componente{
private:
    /*
        nucleo es el contenedor de lo que regresa el lexico.
        Se compone de un lexema, token y un id
    */
    std::unordered_map<std::string, std::string> nucleo;
    int id;
public:
    // Definición estática de los diccionarios
    static void inicializar_diccionarios();   
    // Constructor
    Componente(const std::string& lexema, const std::string& token);
    // Setters
    void set_id();
    void set_token();
    // Getters
    std::string get_lexema();
    std::string get_token();
    int get_id();

};
#endif // COMPONENTE_H
