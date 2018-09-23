/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *MenuOpen;
    QAction *MenuSave;
    QAction *MenuExit;
    QAction *MenuTest;
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget;
    QHBoxLayout *Button_layout;
    QPushButton *Open;
    QPushButton *Save;
    QPushButton *Exit;
    QMenuBar *menuBar;
    QMenu *menuOpen;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(732, 630);
        MenuOpen = new QAction(MainWindow);
        MenuOpen->setObjectName(QStringLiteral("MenuOpen"));
        MenuSave = new QAction(MainWindow);
        MenuSave->setObjectName(QStringLiteral("MenuSave"));
        MenuExit = new QAction(MainWindow);
        MenuExit->setObjectName(QStringLiteral("MenuExit"));
        MenuTest = new QAction(MainWindow);
        MenuTest->setObjectName(QStringLiteral("MenuTest"));
        MainWidget = new QWidget(MainWindow);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        verticalLayout_2 = new QVBoxLayout(MainWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        treeWidget = new QTreeWidget(MainWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout_2->addWidget(treeWidget);

        Button_layout = new QHBoxLayout();
        Button_layout->setSpacing(6);
        Button_layout->setObjectName(QStringLiteral("Button_layout"));
        Open = new QPushButton(MainWidget);
        Open->setObjectName(QStringLiteral("Open"));

        Button_layout->addWidget(Open);

        Save = new QPushButton(MainWidget);
        Save->setObjectName(QStringLiteral("Save"));

        Button_layout->addWidget(Save);

        Exit = new QPushButton(MainWidget);
        Exit->setObjectName(QStringLiteral("Exit"));

        Button_layout->addWidget(Exit);


        verticalLayout_2->addLayout(Button_layout);

        MainWindow->setCentralWidget(MainWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 732, 20));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuOpen->menuAction());
        menuOpen->addAction(MenuOpen);
        menuOpen->addAction(MenuSave);
        menuOpen->addAction(MenuExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        MenuOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        MenuSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        MenuExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        MenuTest->setText(QApplication::translate("MainWindow", "Test", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "salary", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "position", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "name", nullptr));
        Open->setText(QApplication::translate("MainWindow", "Open", nullptr));
        Save->setText(QApplication::translate("MainWindow", "Save", nullptr));
        Exit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        menuOpen->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
