#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <Qt>
#include "analizador_lexico.h"

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
    void mostrar_elementos(std::list<Componente> componentes);
signals:
    void centralWidgetResized();
private:
    analizador_lexico analizador;
    Ui::MainWindow *ui;
protected:
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
