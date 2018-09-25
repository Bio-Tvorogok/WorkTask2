#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    ui->treeWidget->clear();
    connect(ui->Exit, SIGNAL(clicked()), this, SLOT(on_exit_clicked()));
    connect(ui->Open, SIGNAL(clicked()), this, SLOT(on_open_clicked()));
    connect(ui->Save, SIGNAL(clicked()), this, SLOT(on_save_clicked()));
    connect(ui->MenuOpen, SIGNAL(triggered()), this, SLOT(on_open_clicked()));
    connect(ui->MenuExit, SIGNAL(triggered()), this, SLOT(on_exit_clicked()));
    connect(ui->MenuSave, SIGNAL(triggered()), this, SLOT(on_save_clicked()));

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(popup_menu(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_open_clicked()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), "Xml File (*.xml)");

    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this, "File Error", "file not open", QMessageBox::Ok);
    else {
        QXmlStreamReader reader(&file);

        ui->treeWidget->clear();
        auto prev_item = new QTreeWidgetItem();
        while (!reader.atEnd()) {
            if (reader.isStartElement() && (reader.name() != "company")){
                auto attrib = reader.attributes();
                if (reader.name() == "facility"){
                    auto item = new QTreeWidgetItem(ui->treeWidget);
                    item->setText(0, attrib.value("name").toString());
                    prev_item = item;
                }
                else if (reader.name() == "employee"){
                    auto item = new QTreeWidgetItem(prev_item);
                    item->setText(0, attrib.value("name").toString());
                    reader.readNextStartElement();
                    item->setText(1, reader.readElementText());
                    reader.readNextStartElement();
                    auto salary = reader.readElementText();
                    item->setText(2, salary);
                }
            } else if (reader.isEndElement() && (reader.name() == "facility") && prev_item){
                update_facility(prev_item);
                prev_item->setBackgroundColor(2, Qt::gray);
                prev_item->setTextColor(2, Qt::white);
            }
            reader.readNext();
        }
        if (reader.hasError())
            QMessageBox::warning(this, "Xml Error", "file not read", QMessageBox::Ok);
    }
    file.close();
}

void MainWindow::on_save_clicked()
{
    if (ui->treeWidget->topLevelItemCount() != 0) {
        auto path = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), "Xml File (*.xml)");
        QFile file(path);
        if (!file.open(QFile::WriteOnly))
            QMessageBox::warning(this, "File Error", "file not open", QMessageBox::Ok);
        else {
            QXmlStreamWriter writer(&file);
            writer.setAutoFormatting(true);
            writer.writeStartDocument();
            writer.writeStartElement("company");

            for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
                recursive_tree_print(ui->treeWidget->topLevelItem(i), writer, true);
            writer.writeEndElement();
        }
        file.close();
    } else
        QMessageBox::warning(this, "Save error", "Tree empty", QMessageBox::Ok);
}

void MainWindow::recursive_tree_print(QTreeWidgetItem* item, QXmlStreamWriter& writer, bool isTop){
    if (isTop) {
        writer.writeStartElement("facility");
        writer.writeAttribute("name", item->text(0));
    }
    else {
        writer.writeStartElement("employee");
        writer.writeAttribute("name", item->text(0));

        writer.writeTextElement("position", item->text(1));
        writer.writeTextElement("salary", item->text(2));

        writer.writeEndElement();
    }
    for (int i = 0; i < item->childCount(); i++){
        recursive_tree_print(item->child(i), writer, false);
    }
    if (isTop)
        writer.writeEndElement();
}

void MainWindow::popup_menu(QPoint point){
    QMenu* menu = new QMenu(this);
    QAction* editDevice = new QAction("Edit", this);
    QAction* deletDevice = new QAction("Delete", this);
    QAction* addEmployeeDevice = new QAction("Add Employee", this);
    QAction* addFacilityDevice = new QAction("Add Facility", this);
    connect(editDevice, SIGNAL(triggered()), this, SLOT(edit_record()));
    connect(deletDevice, SIGNAL(triggered()), this, SLOT(remove_record()));
    connect(addEmployeeDevice, SIGNAL(triggered()), this, SLOT(add_employee()));
    connect(addFacilityDevice, SIGNAL(triggered()), this, SLOT(add_facility()));
    menu->addAction(editDevice);
    menu->addAction(deletDevice);
    menu->addAction(addEmployeeDevice);
    menu->addAction(addFacilityDevice);
    menu->popup(ui->treeWidget->viewport()->mapToGlobal(point));
}

void MainWindow::remove_record(){
    if (ui->treeWidget->topLevelItemCount() != 0)
        if (ui->treeWidget->currentItem()->isSelected()) {
            if (QMessageBox::warning(this, "Delete record", "Are you sure?",
                QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
                return;
             else {
                auto parent = ui->treeWidget->currentItem()->parent();
                delete ui->treeWidget->currentItem();
                if (parent)
                    update_facility(parent);
            }
        }
}

void MainWindow::edit_record(){
    if (ui->treeWidget->topLevelItemCount() > 0)
        if (ui->treeWidget->currentItem()->isSelected()) {
            if (ui->treeWidget->currentItem()->parent())
                tree_dialog_employee(false);
            else
                tree_dialog_facility(false);
        }

}

void MainWindow::add_employee(){
    if (ui->treeWidget->topLevelItemCount() != 0) {
        if (ui->treeWidget->currentItem()->isSelected())
            tree_dialog_employee(true);
        }
}

void MainWindow::add_facility() {
    tree_dialog_facility(true);
}

void MainWindow::update_facility(QTreeWidgetItem* item){
    if (item) {
        if (item->childCount() != 0) {
            int sum = 0;
            for (int i = 0; i < item->childCount(); i++)
                sum += item->child(i)->text(2).toInt();
            item->setText(2, QString::number(sum / item->childCount()));
        }
        else item->setText(2, "0");
        item->setBackgroundColor(2, Qt::gray);
        item->setTextColor(2, Qt::white);
    }
}

void MainWindow::tree_dialog_facility(bool isAdd){
    if (isAdd){
        dialog_add* dialog = new dialog_add(ui->treeWidget, "", this);
        switch (dialog->exec()) {
        case QDialog::Accepted: {
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            item->setText(0, dialog->get_name());
            break;
        }
        case QDialog::Rejected:
            break;
        }
    } else {
        if (ui->treeWidget->currentItem()->isSelected()) {
            dialog_add* dialog = new dialog_add(ui->treeWidget, ui->treeWidget->currentItem()->text(0), this);
            switch (dialog->exec()) {
            case QDialog::Accepted: {
                ui->treeWidget->currentItem()->setText(0, dialog->get_name());
                break;
            }
            case QDialog::Rejected:
                break;
            }
        }
    }
}

void MainWindow::tree_dialog_employee(bool isAdd){
    if (isAdd){
        dialog_add* dialog = new dialog_add("", "", "", this);
        switch (dialog->exec()) {
        case QDialog::Accepted: {
            if (ui->treeWidget->currentItem()->parent()) {
                QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget->currentItem()->parent());
                item->setText(0, dialog->get_name());
                item->setText(1, dialog->get_position());
                item->setText(2, dialog->get_salary());
                update_facility(ui->treeWidget->currentItem()->parent());
            } else {
                QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget->currentItem());
                item->setText(0, dialog->get_name());
                item->setText(1, dialog->get_position());
                item->setText(2, dialog->get_salary());
                update_facility(ui->treeWidget->currentItem());
            }
            break;
        }
        case QDialog::Rejected:
            break;
        }
    } else {
        if (ui->treeWidget->currentItem()->isSelected()){
            dialog_add* dialog = new dialog_add(ui->treeWidget->currentItem()->text(0),
                                                ui->treeWidget->currentItem()->text(1), ui->treeWidget->currentItem()->text(2), this);
            switch (dialog->exec()) {
            case QDialog::Accepted: {
                ui->treeWidget->currentItem()->setText(0, dialog->get_name());
                ui->treeWidget->currentItem()->setText(1, dialog->get_position());
                ui->treeWidget->currentItem()->setText(2, dialog->get_salary());
                update_facility(ui->treeWidget->currentItem()->parent());
                break;
            }
            case QDialog::Rejected:
                break;
            }
        }
    }
}
