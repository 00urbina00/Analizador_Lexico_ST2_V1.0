/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_8;
    QPlainTextEdit *pte_codigo;
    QFrame *frame_5;
    QGridLayout *gridLayout_7;
    QPushButton *btn_analizar;
    QFrame *frame_4;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QPlainTextEdit *pte2;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QTableWidget *tw_componentes;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1340, 885);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(220, 220, 220);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_2);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName("groupBox_2");
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(10);
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);\n"
"color: rgb(0, 0, 255);"));
        gridLayout_8 = new QGridLayout(groupBox_2);
        gridLayout_8->setObjectName("gridLayout_8");
        pte_codigo = new QPlainTextEdit(groupBox_2);
        pte_codigo->setObjectName("pte_codigo");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Courier")});
        font1.setPointSize(12);
        pte_codigo->setFont(font1);
        pte_codigo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 255);"));

        gridLayout_8->addWidget(pte_codigo, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 1);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setMaximumSize(QSize(180, 16777215));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_5);
        gridLayout_7->setObjectName("gridLayout_7");
        btn_analizar = new QPushButton(frame_5);
        btn_analizar->setObjectName("btn_analizar");
        btn_analizar->setFont(font);
        btn_analizar->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	\n"
"	background-color: rgb(220, 220, 220);\n"
"	\n"
"	color: rgb(0, 0, 255);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"	\n"
"	background-color: rgb(200, 200, 200);\n"
"	color: rgb(0, 255, 0);\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"	\n"
"	background-color: rgb(211, 211, 211);\n"
"	\n"
"	\n"
"\n"
"}"));

        gridLayout_7->addWidget(btn_analizar, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_5, 0, 1, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setMaximumSize(QSize(500, 16777215));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_4);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(frame_4);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(500, 16777215));
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setObjectName("gridLayout_9");
        pte2 = new QPlainTextEdit(groupBox_3);
        pte2->setObjectName("pte2");
        pte2->setMaximumSize(QSize(500, 16777215));
        pte2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_9->addWidget(pte2, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_4, 0, 2, 1, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setMaximumSize(QSize(16777215, 350));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(frame_3);
        groupBox->setObjectName("groupBox");
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        tw_componentes = new QTableWidget(groupBox);
        if (tw_componentes->columnCount() < 3)
            tw_componentes->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tw_componentes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tw_componentes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tw_componentes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tw_componentes->rowCount() < 1)
            tw_componentes->setRowCount(1);
        tw_componentes->setObjectName("tw_componentes");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(12);
        tw_componentes->setFont(font2);
        tw_componentes->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"       \n"
"	background-color: rgb(255, 255, 255);\n"
"    }\n"
"    \n"
"    QHeaderView::section {\n"
"        \n"
"	\n"
"	background-color: rgb(180, 180, 180);\n"
"   \n"
"	color: rgb(0, 85, 255);\n"
"    }\n"
"    \n"
"    QTableWidget::item {\n"
"        \n"
"	background-color: rgb(200, 200, 200);\n"
"    \n"
"	\n"
"	color: rgb(0, 0, 255);\n"
"    }"));
        tw_componentes->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tw_componentes->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tw_componentes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tw_componentes->setDragDropOverwriteMode(false);
        tw_componentes->setAlternatingRowColors(false);
        tw_componentes->setSelectionMode(QAbstractItemView::MultiSelection);
        tw_componentes->setTextElideMode(Qt::ElideMiddle);
        tw_componentes->setSortingEnabled(false);
        tw_componentes->setRowCount(1);
        tw_componentes->horizontalHeader()->setVisible(true);
        tw_componentes->horizontalHeader()->setMinimumSectionSize(400);
        tw_componentes->horizontalHeader()->setDefaultSectionSize(420);
        tw_componentes->horizontalHeader()->setHighlightSections(true);
        tw_componentes->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tw_componentes->horizontalHeader()->setStretchLastSection(false);
        tw_componentes->verticalHeader()->setVisible(false);

        gridLayout_4->addWidget(tw_componentes, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_3, 1, 0, 1, 3);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1340, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Analizador Lexico", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "C\303\263digo", nullptr));
        pte_codigo->setPlaceholderText(QCoreApplication::translate("MainWindow", "int void(){while(true){if(true)return;}}", nullptr));
        btn_analizar->setText(QCoreApplication::translate("MainWindow", "Analizar", nullptr));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Componentes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tw_componentes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Lexema", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tw_componentes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Token", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tw_componentes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "#", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
