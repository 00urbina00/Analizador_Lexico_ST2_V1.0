#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cctype>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_analizar, SIGNAL(clicked()), this, SLOT(mostrar_elementos()));
    connect(this, SIGNAL(centralWidgetResized()), this, SLOT(resize_table()));
}
void MainWindow::resize_table()
{
    QHeaderView* headerView = ui->tw_componentes->horizontalHeader();

    // Establece el modo de redimensionamiento de las columnas para que se estiren automáticamente
    headerView->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    emit centralWidgetResized(); // Emitir la señal cuando cambie el tamaño
    QMainWindow::resizeEvent(event); // Llamar a la implementación base
}
void MainWindow::analizar(){
    QString  plain_text = ui->pte_codigo->toPlainText();
    std::string cadena = plain_text.toStdString();
    componentes.clear();
    if(cadena.empty()){
        std::cout<<"La cadena esta vacia...\n";
    }
    cadena += "$";
    int indice = 0;
    int estado = 0;
    while(indice <= (cadena.length()-1) && estado == 0 && !cadena.empty()){
        std::string lexema = "";
        std::string token = "error";
        while(indice <= (cadena.length()-1) && estado != 20){
            if(estado == 0){ // Si el estado actual es 0: (inicial) -------------------------------------------->
                if(isspace(cadena[indice])){
                    estado = 0;
                }else if(isalpha(cadena[indice]) || (cadena[indice] == '_')){ // \w, '_'
                    estado = 4;             // Saltamos al estado 4
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "id";           // Este lexema es un identificador
                }else if(cadena[indice] == '"'){
                    estado = 8;             // Saltamos al estado
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    // Este lexema puede ser cadena
                }else if(cadena[indice] == '&'){                                //
                    estado = 5;             // Saltamos al estado 5
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opAnd";           // Este lexema es un operador and
                }else if(cadena[indice] == '|'){                                //
                    estado = 6;             // Saltamos al estado 6
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opOr";           // Este lexema es un operador or
                }else if(cadena[indice] == '!'){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opNot";        // Este lexema es un operador not
                }else if(cadena[indice] == '='){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "=";             // Este lexema es un operador asignacion =
                }else if(cadena[indice] == '<'){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opRelac";      // Este lexema es un operador mayor que
                }else if(cadena[indice] == '>'){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opRelac";      // Este lexema es un operador menor que
                }else if(isdigit(cadena[indice])){                             //
                    estado = 18;            // Saltamos al estado 19
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "entero";       // Este lexema es un entero
                }else if(cadena[indice] == '('){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "parIzq";       // Este lexema es parentesis izquierdo
                }else if(cadena[indice] == ')'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "parDer";       // Este lexema es parentesis derecho
                }else if(cadena[indice] == '{'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "llaveIzq";     // Este lexema es llave izquierda
                }else if(cadena[indice] == '}'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "llaveDer";     // Este lexema es llave derecha
                }else if(cadena[indice] == ';'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "puntoComa";    // Este lexema es punto y coma
                }else if(cadena[indice] == ','){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "coma";         // Este lexema es coma
                }else if(cadena[indice] == '+' || cadena[indice] == '-'){       //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opSuma";       // Este lexema es operador suma
                }else if(cadena[indice] == '*' || cadena[indice] == '/'){       //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opMul";        // Este lexema es op multiplicacion
                }else if(cadena[indice] == '$'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "pesos";        // Este lexema es un signo de pesos
                }++indice;   // Se terminó de leer el caracter, se incrementa el indice
            }else if(estado == 4){
                if(isalpha(cadena[indice]) || isdigit(cadena[indice]) || cadena[indice] == '_'){
                    estado = 4;             // Saltamos al estado 4
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "id";           // Este lexema es un identificador
                    ++indice;
                    //else if()
                }else{      // Se recibe otro caracter, se termina la cadena
                    estado = 20;
                }
            }else if(estado == 5){  // Se recibe un '&'
                if(cadena[indice] == '&'){
                    estado = 20;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "opAnd";
                    ++indice;
                }else{
                    estado = 20;
                    token = "error";
                }
            }else if(estado == 6){  // Se recibe un '|'
                if(cadena[indice] == '|'){
                    estado = 20;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "opOr";
                    ++indice;
                }else{
                    estado = 20;
                    token = "error";
                }
            }else if(estado == 7){  // Se recibe un operador "=, <, >, !"
                if(cadena[indice] == '='){  // La cadena es "==, <=, >=, !="
                    estado = 20;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "opRelac";
                    ++indice;
                }else{                      // La cadena es un operador "=, <, >, !"
                    estado = 20;
                }
            }else if(estado == 8){  // Se recibe una comilla en el estado 0
                if(isalpha(cadena[indice]) || isdigit(cadena[indice])){     // la cadena contiene numeros o letras
                    estado = 8; // Nos quedamos en el mismo estado
                    char caracter = cadena[indice];
                    lexema += caracter;
                    ++indice;
                }
                else if(cadena[indice] == '\n'){    // La cadena tiene un salto de linea (se omite)
                    estado = 8; // Nos quedamos en el mismo estado
                    ++indice;
                }
                else if(isspace(cadena[indice])){   // la cadena contiene espacios o tabulaciones
                    estado = 8;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    ++indice;
                }
                else if(cadena[indice] == '"'){     // Se recibe la comilla de cierre
                    estado = 20;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "cadena";
                    ++indice;
                }
                else{
                    estado = 20;
                }
            }else if(estado == 18){     // Se recibe un número
                if(isdigit(cadena[indice])){
                    estado = 18;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "entero";
                    ++indice;
                }else if(cadena[indice] == '.'){    // Se recibe un punto
                    estado = 19;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "real";
                    ++indice;
                }else{
                    estado = 20;
                }
            }else if(estado == 19){     // Se recibió un número seguido de un punto
                if(isdigit(cadena[indice])){
                    estado = 19;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "real";
                    ++indice;
                }else{
                    estado = 20;
                }
            }
        }
        estado = 0;
        Componente componente = Componente(lexema, token);
        componentes.push_back(componente);
    }
}
void MainWindow::mostrar_elementos(){
    analizar();
    // Establece el número de filas en la tabla
    ui->tw_componentes->setRowCount(componentes.size());
    std::list<Componente>::iterator it = componentes.begin();
    int fila = 0;
    while(it != componentes.end()){
        Componente componente = *it;
        // Asigna los valores a las celdas de la fila
        ui->tw_componentes->setItem(fila, 0, new QTableWidgetItem(QString::fromStdString(componente.get_lexema())));
        ui->tw_componentes->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(componente.get_token())));
        ui->tw_componentes->setItem(fila, 2, new QTableWidgetItem(QString::number(componente.get_id())));
        // Alinea el texto en el centro de las celdas
        ui->tw_componentes->item(fila, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_componentes->item(fila, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_componentes->item(fila, 2)->setTextAlignment(Qt::AlignCenter);
        ++it;
        ++fila;
    }
    // Ajusta automáticamente el ancho de las columnas
    ui->tw_componentes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
MainWindow::~MainWindow()
{
    delete ui;
}
