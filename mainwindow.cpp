#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <cctype>
#include "AnalizadorSintactico.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    lexical = analizador_lexico();
    ui->setupUi(this);

    connect(ui->btn_analizar, SIGNAL(clicked()), this, SLOT(analizar_lexicamente()));
    connect(this, SIGNAL(centralWidgetResized()), this, SLOT(resize_table()));

    connect(ui->btn_analizar, SIGNAL(clicked()), this, SLOT(validar_asignacion()));

    connect(ui->action_abrir, &QAction::triggered, this, &MainWindow::abrir_archivo);
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
void MainWindow::analizar_lexicamente(){
    QString  plain_text = ui->pte_codigo->toPlainText();        // Extrae el texto del PlainText a un QString.
    std::string cadena = plain_text.toStdString();              // Crea un string del QString.
    // Llama al analizador léxico(regresa una lista de componentes léxicos) y los muestra en la interfaz.
    componentes = lexical.analizar_lexicamente(cadena);  // Se inicializa componentes con los analizados
    mostrar_elementos(componentes);

}
void MainWindow::mostrar_elementos(std::list<Componente> componentes){  // Recibe la lista de componentes del analizador lex
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
void MainWindow::Validar_Sentencia(){
    QString aux=ui->pte_codigo->toPlainText();
    std::string codigo=aux.toStdString();
    AnalizadorSintactico analizador(codigo);
    if(analizador.declarar_variable()){
        ui->pte_segundo->setPlainText("La entrada proporcionada es valida!!!");
    }
    else{
        ui->pte_segundo->setPlainText("La entrada proporcionada no cuenta con la sintaxis correcta!!!");
    }

}
void MainWindow::validar_asignacion(){
    if(syntax.analizar_asignacion(componentes)){
        ui->pte_segundo->setPlainText("La entrada proporcionada es valida!!!");
    }
    else{
        ui->pte_segundo->setPlainText("La entrada proporcionada no cuenta con la sintaxis correcta!!!");
    }
}

void MainWindow::abrir_archivo(){
    QString archivo = QFileDialog::getOpenFileName(this, "Abrir archivo de código fuente", QDir::homePath(), "Archivos de código fuente (*.cpp *.h *.hpp)");

    if (!archivo.isEmpty()) {
        // Abre y procesa el archivo seleccionado.
        QFile file(archivo);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString contenido = in.readAll();

            ui->pte_codigo->clear();
            // Coloca el contenido del archivo en el PlainText
            ui->pte_codigo->setPlainText(contenido);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
