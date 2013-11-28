#include "fieldmemberwindow.hpp"
#include "ui_fieldmemberwindow.h"
#include "src/views/mainwindow.hpp"
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
    ui->lineEdit_Name->setFocus();
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
        FieldMember fm;

        fm.Name = ui->lineEdit_Name->text().toStdString();
        fm.Type = ui->lineEdit_Type->text().toStdString();
        fm.Default = ui->lineEdit_Default->text().toStdString();
        fm.isConst = ui->checkBox_Const->isChecked();
        fm.isStatic = ui->checkBox_Static->isChecked();
        fm.hasGet = ui->checkBox_Get->isChecked();
        fm.hasSet = ui->checkBox_Set->isChecked();
        fm.range = (RANGE) ui->comboBox_Range->currentIndex();

        MainWindow * mw = dynamic_cast<MainWindow*>(parent());

        mw->addFieldMember(fm);
        close();
    }
}

bool FieldMemberWindow::checkFields()
{
    // Name
    if (ui->lineEdit_Name->text().isEmpty() || ui->lineEdit_Name->text().contains(' '))
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le nom de l'attribut doit être renseigné. Il ne doit pas contenir d'espace."),
                        0, this);
        msg.exec();
        return false;
    }

    // Type
    if (ui->lineEdit_Type->text().isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le type doit être renseigné."),
                        0, this);
        msg.exec();
        return false;
    }

    // default value for const field member
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

void FieldMemberWindow::on_lineEdit_Name_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || arg1.contains(' '))
    {
        QPalette pal = ui->lineEdit_Name->palette();
        pal.setColor(QPalette::Base, QColor(255,30,30));
        ui->lineEdit_Name->setPalette(pal);
    }
    else
    {
        QPalette pal = ui->lineEdit_Name->palette();
        pal.setColor(QPalette::Base, QColor(30,255,30));
        ui->lineEdit_Name->setPalette(pal);
    }
}

void FieldMemberWindow::on_lineEdit_Type_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        QPalette pal = ui->lineEdit_Type->palette();
        pal.setColor(QPalette::Base, QColor(255,50,50));
        ui->lineEdit_Type->setPalette(pal);
    }
    else
    {
        QPalette pal = ui->lineEdit_Type->palette();
        pal.setColor(QPalette::Base, QColor(50,255,50));
        ui->lineEdit_Type->setPalette(pal);
    }
}

void FieldMemberWindow::on_checkBox_Const_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        if (ui->lineEdit_Default->text().isEmpty())
        {
            QPalette pal = ui->lineEdit_Default->palette();
            pal.setColor(QPalette::Base, QColor(255,50,50));
            ui->lineEdit_Default->setPalette(pal);
        }
        else
        {
            QPalette pal = ui->lineEdit_Default->palette();
            pal.setColor(QPalette::Base, QColor(50,255,50));
            ui->lineEdit_Default->setPalette(pal);
        }
    }
    else if (arg1 == Qt::Unchecked)
    {
        QPalette pal = ui->lineEdit_Default->palette();
        pal.setColor(QPalette::Base, QColor(255,255,255));
        ui->lineEdit_Default->setPalette(pal);
    }
}

void FieldMemberWindow::on_lineEdit_Default_textChanged(const QString &arg1)
{
    if (ui->checkBox_Const->isChecked())
    {
        if (arg1.isEmpty())
        {
            QPalette pal = ui->lineEdit_Default->palette();
            pal.setColor(QPalette::Base, QColor(255,50,50));
            ui->lineEdit_Default->setPalette(pal);
        }
        else
        {
            QPalette pal = ui->lineEdit_Default->palette();
            pal.setColor(QPalette::Base, QColor(50,255,50));
            ui->lineEdit_Default->setPalette(pal);
        }
    }
}
