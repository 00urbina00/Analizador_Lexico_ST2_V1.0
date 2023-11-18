#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Interfaz
#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <Qt>
// Manejo de archivos en interfaz
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
// Procesamiento
#include "componente.h"
#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "analizador_semantico.h"

#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void resize_table();
    void analizar_lexicamente();
    void abrir_archivo();
    void mostrar_elementos(std::list<Componente> componentes);
    void validar_asignacion();

signals:
    void centralWidgetResized();


private:
    analizador_lexico lexical;
    analizador_sintactico syntax;
    analizador_semantico checker;
    Ui::MainWindow *ui;
    std::list<Componente> componentes;

protected:
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
