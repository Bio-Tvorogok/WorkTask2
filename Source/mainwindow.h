#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamAttribute>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>
#include <QDebug>
#include <QString>
#include "dialog_add.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void recursive_tree_print(QTreeWidgetItem* item, QXmlStreamWriter& writer, bool isTop);
    void update_facility(QTreeWidgetItem* item);
    bool global_check(QString name);
    void tree_dialog_facility(bool isAdd);
    void tree_dialog_employee(bool isAdd);

private slots:
    void on_exit_clicked();
    void on_open_clicked();
    void on_save_clicked();
    void popup_menu(QPoint point);
    void edit_record();
    void remove_record();
    void add_employee();
    void add_facility();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
