#include "dialog_add.h"

dialog_add::dialog_add(QTreeWidget* tree, QString name, QWidget* parent) : QDialog (parent) {
    tree_global = tree;
    isFacility = true;
    name_edit = new QLineEdit(name);
    QLabel* name_lable = new QLabel("name");
    name_lable->setBuddy(name_edit);

    QPushButton* buttonOk = new QPushButton("&Ok");
    QPushButton* buttonCancel = new QPushButton("&Cancel");

    connect(buttonOk, SIGNAL(clicked()), SLOT(accept_func()));
    connect(buttonCancel, SIGNAL(clicked()), SLOT(reject()));
    connect(this, SIGNAL(accept_signal()), SLOT(accept()));

    QGridLayout* glayout = new QGridLayout;
    glayout->addWidget(name_lable, 0, 0);
    glayout->addWidget(name_edit, 0, 1);
    glayout->addWidget(buttonOk, 1, 0);
    glayout->addWidget(buttonCancel, 1, 1);
    setLayout(glayout);
}

dialog_add::dialog_add(QString name, QString position, QString salary, QWidget* parent) : QDialog (parent) {

    isFacility = false;
    name_edit = new QLineEdit(name);
    position_edit = new QLineEdit(position);
    salary_edit = new QLineEdit(salary);
    QLabel* name_lable = new QLabel("name");
    QLabel* position_lable = new QLabel("position");
    QLabel* salary_lable = new QLabel("salary");
    name_lable->setBuddy(name_edit);
    position_lable->setBuddy(position_edit);
    salary_lable->setBuddy(salary_edit);

    QPushButton* buttonOk = new QPushButton("&Ok");
    QPushButton* buttonCancel = new QPushButton("&Cancel");

    connect(buttonOk, SIGNAL(clicked()), SLOT(accept_func()));
    connect(buttonCancel, SIGNAL(clicked()), SLOT(reject()));
    connect(this, SIGNAL(accept_signal()), SLOT(accept()));

    QGridLayout* glayout = new QGridLayout;
    glayout->addWidget(name_lable, 0, 0);
    glayout->addWidget(name_edit, 0, 1);
    glayout->addWidget(position_lable, 1, 0);
    glayout->addWidget(position_edit, 1, 1);
    glayout->addWidget(salary_lable, 2, 0);
    glayout->addWidget(salary_edit, 2, 1);
    glayout->addWidget(buttonOk, 3, 0);
    glayout->addWidget(buttonCancel, 3, 1);
    setLayout(glayout);

}

dialog_add::~dialog_add() {
}

QString dialog_add::get_name() const {
    return name_edit->text();
}

QString dialog_add::get_position() const {
    return position_edit->text();
}

QString dialog_add::get_salary() const {
    return salary_edit->text();
}

void dialog_add::accept_func() {
    if (isFacility) {
        if (!name_edit->text().isEmpty()) {
            bool isOnly = true;
            for (int i = 0; i < tree_global->topLevelItemCount(); i++)
                if (tree_global->topLevelItem(i)->text(0) == name_edit->text()) {
                    isOnly = false;
                    break;
                }
            if (isOnly)
                emit accept_signal();
        }
    } else {
        if (!name_edit->text().isEmpty() && !position_edit->text().isEmpty() && !salary_edit->text().isEmpty()) {
            //if (salary_edit->text().toInt())
            QRegExp re("\\d*");
            if (re.exactMatch(salary_edit->text()))
                emit accept_signal();
        }
    }
}
