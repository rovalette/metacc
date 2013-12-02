#include "paramwindow.hpp"
#include "ui_paramwindow.h"
#include "ui/methodview.hpp"
#include <QMessageBox>

ParamWindow::ParamWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamWindow)
{
    ui->setupUi(this);
}

void ParamWindow::init()
{
    ui->lineEdit_Default->setText("");
    ui->lineEdit_Name->setText("");
    ui->lineEdit_Type->setText("");

    ui->checkBox_Const->setChecked(false);

    QPalette pal = ui->lineEdit_Name->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_Name->setPalette(pal);
    pal = ui->lineEdit_Type->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_Type->setPalette(pal);
}

ParamWindow::~ParamWindow()
{
    delete ui;
}

void ParamWindow::on_pushButton_Cancel_clicked()
{
    close();
}

bool ParamWindow::checkFields()
{
    if (ui->lineEdit_Name->text().isEmpty() || ui->lineEdit_Name->text().contains(' '))
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le nom du paramètre doit être renseigné. Il ne doit pas contenir d'espace."),
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

    return true;
}

void ParamWindow::on_pushButton_OK_clicked()
{
    if (checkFields())
    {
        Parameter p;

        p.Name = ui->lineEdit_Name->text().toStdString();
        p.Type = ui->lineEdit_Type->text().toStdString();
        p.Default = ui->lineEdit_Default->text().toStdString();

        p.isConst = ui->checkBox_Const->isChecked();

        MethodView * mv = dynamic_cast<MethodView*>(parent());
        mv->addParameter(p);

        close();
    }
}

void ParamWindow::on_lineEdit_Name_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || arg1.contains(' '))
    {
        QPalette pal = ui->lineEdit_Name->palette();
        pal.setColor(QPalette::Base, QColor(255,50,50));
        ui->lineEdit_Name->setPalette(pal);
    }
    else
    {
        QPalette pal = ui->lineEdit_Name->palette();
        pal.setColor(QPalette::Base, QColor(255,255,255));
        ui->lineEdit_Name->setPalette(pal);
    }
}

void ParamWindow::on_lineEdit_Type_textChanged(const QString &arg1)
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
        pal.setColor(QPalette::Base, QColor(255,255,255));
        ui->lineEdit_Type->setPalette(pal);
    }
}
