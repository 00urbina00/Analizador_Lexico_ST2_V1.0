#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <Qt>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "componente.h"
#include "analizador_lexico.h"
#include "Analizador_sintactico.h"

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
    void Validar_Sentencia();
    void validar_asignacion();

signals:
    void centralWidgetResized();


private:
    analizador_lexico lexical;
    analizador_sintactico syntax;
    Ui::MainWindow *ui;
    std::list<Componente> componentes;

protected:
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
