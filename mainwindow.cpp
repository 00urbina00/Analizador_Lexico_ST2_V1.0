#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cctype>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    analizador = analizador_lexico();
    ui->setupUi(this);
    connect(ui->btn_analizar, SIGNAL(clicked()), this, SLOT(analizar_lexicamente()));
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
void MainWindow::analizar_lexicamente(){
    QString  plain_text = ui->pte_codigo->toPlainText();        // Extrae el texto del PlainText a un QString.
    std::string cadena = plain_text.toStdString();              // Crea un string del QString.
    // Llama al analizador léxico(regresa una lista de componentes léxicos) y los muestra en la interfaz.
    mostrar_elementos(analizador.analizar_lexicamente(cadena));

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
MainWindow::~MainWindow(){
    delete ui;
}
