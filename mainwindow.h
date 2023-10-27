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
#include "componente.h"

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
    void analizar();
    void mostrar_elementos();
    void Validar_Sentencia();

signals:
    void centralWidgetResized();


private:
    Ui::MainWindow *ui;
    std::list<Componente> componentes;

protected:
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
