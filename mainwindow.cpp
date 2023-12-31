#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    lexical = analizador_lexico();
    checker = analizador_semantico();
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
    componentes.clear();
    componentes = lexical.analizar_lexicamente(cadena);  // Se inicializa componentes con los analizados
    mostrar_elementos(componentes);
}
void MainWindow::mostrar_elementos(std::list<Componente> cpts){  // Recibe la lista de componentes del analizador lex
    // Establece el número de filas en la tabla
    ui->tw_componentes->setRowCount(cpts.size());

    // Establece el número de columnas en la tabla
    int numColumnas = 4; // Número de columnas, incluyendo la nueva columna
    ui->tw_componentes->setColumnCount(numColumnas);
    auto it = cpts.begin();
    int fila = 0;
    while (it != cpts.end()) {
        Componente componente = *it;

        // Asigna los valores a las celdas de las primeras tres columnas
        ui->tw_componentes->setItem(fila, 0, new QTableWidgetItem(QString::fromStdString(componente.get_lexema())));
        ui->tw_componentes->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(componente.get_token())));
        ui->tw_componentes->setItem(fila, 2, new QTableWidgetItem(QString::number(componente.get_id())));

        // Añade un elemento vacío a la cuarta columna
        ui->tw_componentes->setItem(fila, 3, new QTableWidgetItem(""));

        // Alinea el texto en el centro de las celdas
        for (int columna = 0; columna < numColumnas; ++columna) {
            ui->tw_componentes->item(fila, columna)->setTextAlignment(Qt::AlignCenter);
        }
        ++it;
        ++fila;
    }

    // Ajusta automáticamente el ancho de las columnas
    ui->tw_componentes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::validar_asignacion(){
    std::string salida = syntax.validar_inicio(componentes);    // Salida del sintactico
    // Convertir el std::string a QString
    QString qSalida = QString::fromStdString(salida);
    // ui->pte_segundo->setPlainText(qSalida);
    // Se inicializa el semantico con componentes del sintactico
    checker.set_componentes(syntax.obtener_lista_componentes()); // Se inicializa el semantico con componentes del sintactico
    std::string salida2 = checker.analizar_declaraciones();   // Se analizan las declaraciones
    // Convertir el std::string a QString
    qSalida += QString::fromStdString(salida2);
    ui->pte_segundo->setPlainText(qSalida);
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
