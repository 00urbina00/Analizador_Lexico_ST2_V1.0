#ifndef ANALIZADOR_SEMANTICO_H
#define ANALIZADOR_SEMANTICO_H

#include <iostream>
#include <string>
#include <any>
#include <map>
#include <utility>
#include <list>
#include <sstream>
#include "componente.h"


class Variable {
public:
    std::string tipo;
    std::string valor;
    Variable() = default;
    explicit Variable(std::string  tipo,std::string  valor="") :tipo(std::move(tipo)), valor(std::move(valor)) {}

};

class analizador_semantico {
private:
    std::map<std::string, Variable> variables;
    std::list<Componente> componentes;
    std::list<std::string> errores;
public:
    analizador_semantico()= default;
    void set_componentes(std::list<Componente> componentes_){
        componentes = std::move(componentes_);
    }
    bool tipo_valido(std::list<Componente>::iterator& it) {
        return it != componentes.end() && it->get_token() == "tipo";
    }
    bool id_valido(std::list<Componente>::iterator& it) {
        return it != componentes.end() && it->get_token() == "id";
    }
    bool punto_coma_valido(std::list<Componente>::iterator& it) {
        return it != componentes.end() && it->get_token() == "Separador" && it->get_id() == 25;
    }
    bool igual_valido(std::list<Componente>::iterator& it) {
        return it != componentes.end() && it->get_token() == "opRelacional" && it->get_id() == 29;
    }
    bool valor_valido(std::list<Componente>::iterator& it) {
        auto token = it->get_token();
        return it != componentes.end() && (token == "id" || token == "entero" || token == "real" || token == "cadena" ||
                token == "caracter" || token == "Palabra Reservada");
    }
    bool operador_valido(std::list<Componente>::iterator& it) {
        auto token = it->get_token();
        return it != componentes.end() && (token == "opAritmetico" || token == "opRelacional" || token == "opLogico" ||
                token == "opIgualdad");
    }
    std::string recuperar_errores(){
        std::string resultado;
        for(auto& error : errores){
            resultado += error + "\n";
        }
        return resultado;
    }
    std::string analizar_declaraciones(){
        errores.clear();
        variables.clear();
        auto it = componentes.begin();
        while(it != componentes.end()) {
            if(tipo_valido(it)){auto tipo = it->get_lexema();++it;    // Guardamos el tipo y avanzamos el componente
                if(id_valido(it)){auto identificador = it->get_lexema();++it;
                    if(punto_coma_valido(it)){ // Declaración simple válida (int var;)
                        if(variables.find(identificador) == variables.end()){
                            variables[identificador] = Variable(tipo);
                            std::cout<<"Declaración de variable: "<<identificador<<" de tipo "<<tipo<<std::endl;
                        }else{
                            errores.emplace_back("Error(Semantico): La variable "+identificador+" ya ha sido declarada.");
                            return recuperar_errores();
                            // std::cerr<<"Error(Semantico): La variable "<<identificador<<" ya ha sido declarada."<<std::endl;
                        }
                    }else if(igual_valido(it)){++it;
                        if(valor_valido(it)){auto valor = it->get_lexema();auto tipo_valor = it->get_token();++it;
                            if(operador_valido(it)){auto operador = it->get_lexema();++it;
                                if(valor_valido(it)){auto valor2 = it->get_lexema();auto tipo_valor2 = it->get_token();++it;
                                    if(punto_coma_valido(it)){ // Declaración Compleja válida (int var = 5 * 4;)
                                        if(variables.find(identificador) == variables.end()){
                                            try {
                                                if (tipo == "int" && tipo_valor == "entero" && tipo_valor2 == "entero") {
                                                    int valor_ = std::stoi(valor);
                                                    int valor2_ = std::stoi(valor2);
                                                    if (operador == "+") {
                                                        int res = valor_ + valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "-") {
                                                        int res = valor_ - valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "*") {
                                                        int res = valor_ * valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "/") {
                                                        int res = valor_ / valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    }
                                                } else if (tipo == "float" && tipo_valor == "real" && tipo_valor2 == "real") {
                                                    float valor_ = std::stof(valor);
                                                    float valor2_ = std::stof(valor2);
                                                    if (operador == "+") {
                                                        float res = valor_ + valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "-") {
                                                        float res = valor_ - valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "*") {
                                                        float res = valor_ * valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    } else if (operador == "/") {
                                                        float res = valor_ / valor2_;
                                                        variables[identificador] = Variable(tipo, std::to_string(res));
                                                    }
                                                }else{
                                                    errores.emplace_back("Error(Semantico): El valor asignado no corresponde al tipo de la variable.");
                                                    return recuperar_errores();
                                                }
                                                std::cout<<"Declaración de variable: "<<identificador<<" de tipo "<<tipo<<" y valor: "<< variables[identificador].valor<<std::endl;
                                            }catch (std::invalid_argument& e){
                                                errores.emplace_back("Error(Semantico): El valor asignado no corresponde al tipo de la variable.");
                                                return recuperar_errores();
                                                // std::cerr<<"Error(Semantico): El valor asignado no corresponde al tipo de la variable."<<std::endl;
                                            }
                                        }else{
                                            errores.emplace_back("Error(Semantico): La variable "+identificador+" ya ha sido declarada.");
                                            return recuperar_errores();
                                            // std::cerr<<"Error(Semantico): La variable "<<identificador<<" ya ha sido declarada."<<std::endl;
                                        }
                                    }else{
                                        errores.emplace_back("Error: Se esperaba un punto y coma después del valor.");
                                        return recuperar_errores();
                                        // std::cerr<<"Error: Se esperaba un punto y coma después del valor."<<std::endl;
                                    }
                                }
                            }else if(punto_coma_valido(it)){  // Declaración media válida (int var = 5;)
                                // Declaración válida
                                if (variables.find(identificador) == variables.end()) {
                                    variables[identificador] = Variable(tipo, valor); // Puedes asignar un valor adecuado a std::any
                                    if (valida_operacion(identificador, variables[identificador].valor, tipo_valor)) {
                                        std::cout << "Declaración de variable: " << identificador << " de tipo " << tipo << " y valor: " << valor << std::endl;
                                    }else{
                                        errores.emplace_back("Error(Semantico): El valor asignado no corresponde al tipo de la variable.");
                                        return recuperar_errores();
                                        // std::cerr<<"Error(Semantico): El valor asignado no corresponde al tipo de la variable."<<std::endl;
                                    }
                                } else {
                                    errores.emplace_back("Error(Semantico): La variable "+identificador+" ya ha sido declarada.");
                                    return recuperar_errores();
                                    // std::cerr << "Error(Semantico): La variable " << identificador << " ya ha sido declarada." << std::endl;
                                }
                            }else{
                                errores.emplace_back("Error: Se esperaba un punto y coma después del valor.");
                                return recuperar_errores();
                                // std::cerr<<"Error: Se esperaba un punto y coma después del valor."<<std::endl;
                            }
                        }else{
                            errores.emplace_back("Error: Se esperaba un valor después del operador de asignación.");
                            return recuperar_errores();
                            // std::cerr<<"Error: Se esperaba un valor después del operador de asignación."<<std::endl;
                        }
                    }else {
                        errores.emplace_back("Error: Se esperaba un punto y coma después del identificador.");
                        return recuperar_errores();
                        // std::cerr << "Error: Se esperaba asignación o punto y coma después del identificador." << std::endl;
                    }
                }else {
                    errores.emplace_back("Error: Se esperaba un identificador después del tipo.");
                    return recuperar_errores();
                    // std::cerr << "Error: Se esperaba un identificador después del tipo." << std::endl;
                }
            }
            ++it; // Mover al siguiente componente
        }
        return recuperar_errores();
    }
    int valida_valor_variable_tipo(const std::string& op1,const std::string& op2,const std::string& tipo_valor) {
        int v;
        float c;
        std::istringstream iss(op2);
        if (iss >> v || iss >> c) {
            if (!es_asignacion(op1, tipo_valor)) {
                return 1;
            }
        }else if (tipo_valor == "cadena" || tipo_valor == "caracter" || tipo_valor == "Palabra Reservada") {
            if (!es_asignacion(op1, tipo_valor)) {
                return 1;
            }
        }
        else if (!es_variable_valida(op1,op2)) {
            return 0;
        }
        else if (es_variable_valida(op1,op2)) {
            if (!son_tipos_validos(op1, op2)) {
                return 2;
            }
        }
        return 3;

    }
    bool valida_operacion(const std::string& op1, const std::string& op2, const std::string& tipo_valor) {
        switch (valida_valor_variable_tipo(op1,op2, tipo_valor))
        {
            case 0:
                // errores.emplace_back("Error(semantico): Las variables deben ser declaradas antes de realizar la operacion.");
                // std::cout << "Error: Las variables deben ser declaradas antes de realizar la operacion." << std::endl;
                return false;
            case 1:
                // errores.emplace_back("Error(semantico): El valor asignado no corresponde al tipo de la variable.");
                // std::cout << "Error: El valor asignado no corresponde al tipo de la variable." << std::endl;
                return false;
            case 2:
                // errores.emplace_back("Error(semantico): Los tipos de las variables no concuerdan entre si.");
                // std::cout << "Error: Los tipos de las variables no concuerdan entre si." << std::endl;
                return false;
            case 3:
                return true;
            default:
                errores.emplace_back("Error(semantico) desconocido;");
                // std::cout << "Error desconocido;";
                break;
        }

        return true;
    }
    bool es_variable_valida(const std::string& op1,const std::string& op2) {
        auto iter = variables.find(op1);
        auto iter2 = variables.find(op2);
        if (iter != variables.end()&&iter2!=variables.end()) {
            return true;
        }
        else {
            return false;
        }
    }
    bool es_asignacion(const std::string& op1, const std::string& tipo_valor) {
        auto iter = variables.find(op1);
        if (iter != variables.end()) {
            Variable& aux = iter->second;
            // Verificar el tipo y el valor asignado
            if (aux.tipo == "int" && tipo_valor=="entero") {
                // Es un entero válido
                return true;
            }
            else if (aux.tipo == "float" && tipo_valor == "real") {
                // Es un flotante válido
                return true;
            }
            else if (aux.tipo == "bool"&& tipo_valor == "Palabra Reservada") {
                // Es un booleano válido
                return true;
            }
            else if (aux.tipo == "char" && tipo_valor == "caracter") {
                // Es un carácter válido
                return true;
            }else if (aux.tipo == "string" && tipo_valor == "cadena") {
                return true;
            }
            else {
                // No coincide con el tipo declarado
                return false;
            }
        }
        return false;
    }
    bool son_tipos_validos(const std::string& op1, const std::string& op2) {
        if (variables[op1].tipo != variables[op2].tipo) {
            return false;
        }
        else {
            return true;
        }
    }
};
#endif //ANALIZADOR_LEXICO_ANALIZADOR_SEMANTICO_H
