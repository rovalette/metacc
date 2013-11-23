#include "src/views/mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

void MainWindow::on_pushButton_Quit_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_OK_clicked()
{
    // check for every field is correctly filled
    if (checkFields())
    {
    }
}
