#ifndef DIALOG_ADD_H
#define DIALOG_ADD_H

#include <QDialog>
#include <QMessageBox>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRegExp>

class dialog_add : public QDialog
{
    Q_OBJECT
public:
    explicit dialog_add(QTreeWidget* tree, QString name = "", QWidget* parent = 0);
    explicit dialog_add(QString name = "", QString position = "", QString salary = "", QWidget* parent = 0);
    ~dialog_add();

private:
    QLineEdit* name_edit;
    QLineEdit* position_edit;
    QLineEdit* salary_edit;
    QTreeWidget* tree_global;
    bool isFacility;

public:
    QString get_name() const;
    QString get_position() const;
    QString get_salary() const;

private slots:
    void accept_func();

signals:
    void accept_signal();
};

#endif // DIALOG_ADD_H
