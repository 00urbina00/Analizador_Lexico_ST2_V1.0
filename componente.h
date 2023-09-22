#ifndef COMPONENTE_H
#define COMPONENTE_H

#include <map>
#include <iostream>
#include <unordered_set>
#include <unordered_map>


class Componente{


private:
    std::unordered_set<std::string> tipos_de_datos;
    std::unordered_set<std::string> palabras_reservadas;
    std::unordered_set<std::string> operadores_logicos;
    std::unordered_set<std::string> estructuras_de_control;
    std::unordered_set<std::string> condicionales;
    std::unordered_set<std::string> operadores_relacionales;
    std::unordered_set<std::string> signos;
    std::unordered_map<std::string, std::string> nucleo;
    int id;
public:
    Componente(const std::string& lexema, const std::string& token);
    void set_id();
    void set_token();
    std::string get_lexema();
    std::string get_token();
    int get_id();

};
#endif // COMPONENTE_H
