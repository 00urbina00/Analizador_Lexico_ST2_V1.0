#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    // Obtén una referencia al encabezado horizontal de la tabla
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
    std::cout<<"Analizando..."<<std::endl;
    QString  plain_text = ui->pte_codigo->toPlainText();
    std::string cadena = plain_text.toStdString();
    std::cout<<cadena<<std::endl;

    componentes.clear();

    int indice = 0;
    int estado = 0;
    while(indice <= (cadena.length()-1) && estado == 0){
        std::cout<<"Estado: "<<estado<<" - Caracter numero "<<indice<<std::endl;
        std::string lexema = "";
        std::string token = "error";
        while(indice <= (cadena.length()-1) && estado != 20){
            std::cout<<"Estado: "<<estado<<" - 20Caracter numero "<<indice<<std::endl;
            if(estado == 0){ // Si el estado actual es 0: (inicial) -------------------------------------------->
                if(isspace(cadena[indice])){
                    estado = 0;
                }else if(isalpha(cadena[indice]) || (cadena[indice] == '_')){ // \w, '_'
                    estado = 4;             // Saltamos al estado 4
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "id";           // Este lexema es un identificador
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
                    token = "opAsignacion"; // Este lexema es un operador asignacion =
                }else if(cadena[indice] == '<'){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opMayor";      // Este lexema es un operador mayor que
                }else if(cadena[indice] == '>'){                                //
                    estado = 7;             // Saltamos al estado 7
                    char caracter = cadena[indice];      // Guardamos el caracter actual
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opMenor";      // Este lexema es un operador menor que
                }else if(isdigit(cadena[indice])){                             //
                    estado = 18;            // Saltamos al estado 19
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "constante";    // Este lexema es
                }else if(cadena[indice] == '('){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "parIzq";       // Este lexema es
                }else if(cadena[indice] == ')'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "parDer";       // Este lexema es
                }else if(cadena[indice] == '{'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "llaveIzq";     // Este lexema es
                }else if(cadena[indice] == '}'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "llaveDer";     // Este lexema es
                }else if(cadena[indice] == ';'){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "puntoComa";    // Este lexema es
                }else if(cadena[indice] == ','){                                //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "coma";         // Este lexema es
                }else if(cadena[indice] == '+' || cadena[indice] == '-'){       //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opSuma";       // Este lexema es
                }else if(cadena[indice] == '*' || cadena[indice] == '/'){       //
                    estado = 20;            // Saltamos al estado 20
                    char caracter = cadena[indice];      // guardamos el caracter
                    lexema += caracter;     // Concatenamos el caracter
                    token = "opMul";        // Este lexema es
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
                }else{      // Se leyó otro caracter, se termina la cadena
                    estado = 20;
                }
            }else if(estado == 5){
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
            }else if(estado == 6){
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
            }else if(estado == 7){
                if(cadena[indice] == '='){
                    estado = 20;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "opRelacional";
                    ++indice;
                }else{
                    estado = 20;
                }
            }else if(estado == 18){
                if(isdigit(cadena[indice])){
                    estado = 18;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "constante";
                    ++indice;
                }else if(cadena[indice] == '.'){
                    estado = 19;
                    char caracter = cadena[indice];
                    lexema += caracter;
                    token = "real";
                    ++indice;
                }else{
                    estado = 20;
                }
            }else if(estado == 19){
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
        std::cout<<"Se creo el componente..."<<std::endl;
    }
}
void MainWindow::mostrar_elementos(){
    std::cout<<"Inicia analisis"<<std::endl;
    analizar();
    std::cout<<"Mostrando elementos..."<<std::endl;
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