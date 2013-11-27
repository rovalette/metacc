#include "fieldmemberwindow.hpp"
#include "ui_fieldmemberwindow.h"
#include <QMessageBox>

FieldMemberWindow::FieldMemberWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FieldMemberWindow)
{
    ui->setupUi(this);
}

FieldMemberWindow::~FieldMemberWindow()
{
    delete ui;
}

void FieldMemberWindow::init()
{
    ui->checkBox_Const->setChecked(false);
    ui->checkBox_Get->setChecked(false);
    ui->checkBox_Set->setChecked(false);
    ui->checkBox_Static->setChecked(false);
    ui->comboBox_Range->setCurrentIndex(0);
    ui->lineEdit_Default->setText("");
    ui->lineEdit_Name->setText("");
    ui->lineEdit_Type->setText("");
}

void FieldMemberWindow::on_pushButton_Cancel_clicked()
{
    close();
}

void FieldMemberWindow::on_pushButton_OK_clicked()
{
    // check everything is ok
    if (checkFields())
    {

        close();
    }
}

bool FieldMemberWindow::checkFields()
{
    if (ui->lineEdit_Name->text().isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le nom de l'attribut doit être renseigné."),
                        0, this);
        msg.exec();
        return false;
    }

    if (ui->lineEdit_Type->text().isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le type doit être renseigné."),
                        0, this);
        msg.exec();
        return false;
    }

    if (ui->checkBox_Const->isChecked() && ui->lineEdit_Default->text().isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Une valeur par défaut doit être renseignée lorsque l'attribut est constant."),
                        0, this);
        msg.exec();
        return false;
    }

    return true;
}
