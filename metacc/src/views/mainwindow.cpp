#include "src/views/mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkFields()
{
    // check ClassName field
    std::string className = ui->lineEdit_ClassName->text().toStdString();
    if (className.empty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le nom de la classe doit être renseigné."),
                        0, this);
        msg.exec();
        return false;
    }

    return true;
}

void MainWindow::createClassDefintionObject()
{
    _definition.twoFiles = ui->checkBox_TwoFiles->isChecked();

    _definition.ClassName = ui->lineEdit_ClassName->text().toStdString();
    if (!ui->lineEdit_Path->text().isEmpty() && !ui->lineEdit_Path->text().endsWith('/'))
        ui->lineEdit_Path->setText(ui->lineEdit_Path->text() + '/');
    _definition.FileName = ui->lineEdit_Path->text().toStdString() +
            QString(_definition.ClassName.c_str()).toLower().toStdString();
    _definition.Guardian = "__" +
            QString(_definition.ClassName.c_str()).toUpper().toStdString() + "_HPP__";

    _definition.DefaultConstructor = ui->checkBox_DefaultConstructor->isChecked();
    _definition.CopyConstructor = ui->checkBox_CopyConstructor->isChecked();
    _definition.Destructor = ui->checkBox_Destructor->isChecked();
    _definition.VirtualDestructor = ui->checkBox_VirtualDestructor->isChecked();

    _definition.ComparisonOperator = ui->checkBox_OpComparison->isChecked();
    _definition.RelationalOperator = ui->checkBox_OpRelational->isChecked();
    _definition.CopyOperator = ui->checkBox_OpCopy->isChecked();

}

void MainWindow::on_pushButton_Quit_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_OK_clicked()
{
    // check for every field is correctly filled
    if (checkFields())
    {
        createClassDefintionObject();
        _writer.setClassDefinition(_definition);
        if (ui->checkBox_TwoFiles->isChecked())
            _writer.write();
        else
            _writer.writeHPP();
    }
}

void MainWindow::on_pushButton_Browse_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Chemin"),
                                                          "/tmp/",
                                                          QFileDialog::DontResolveSymlinks);

    if (!directory.isEmpty())
    {
        ui->lineEdit_Path->setText(directory);
    }
}

void MainWindow::on_checkBox_Destructor_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
    {
        ui->checkBox_VirtualDestructor->setEnabled(false);
    }
    else
    {
        ui->checkBox_VirtualDestructor->setEnabled(true);
    }
}

void MainWindow::on_checkBox_OpRelational_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->checkBox_OpComparison->setChecked(true);
    }
}

void MainWindow::on_checkBox_OpComparison_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
    {
        ui->checkBox_OpRelational->setChecked(false);
    }
}
