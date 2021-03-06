#include "src/views/mainwindow.hpp"
#include "ui_mainwindow.h"
#include "src/utils/LogManager.hpp"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _fmw = new FieldMemberWindow(this);
    _mv = new MethodView(this);

    QPalette pal = ui->lineEdit_ClassName->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_ClassName->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _fmw;
    delete _mv;
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

    _definition.fms = _fms;
    _definition.ms = _methods;
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

void MainWindow::on_pushButton_Add_clicked()
{
    _fmw->init();
    _fmw->show();
}

void MainWindow::addFieldMember(FieldMember fm)
{
    int row = ui->listWidget_FieldMember->count();
    _fms.push_back(fm);

    std::string label = (fm.Range==PRIVATE?"- ":(fm.Range==PROTECTED?"# ":"+ "));
    label += fm.Name;
    label += " (" + fm.Type + ") ";
    if (fm.isStatic)
    {
        label += "[static";
        label += (fm.isConst?", const]":"]");
    }
    else if (fm.isConst)
        label += "[const]";

    ui->listWidget_FieldMember->insertItem(
                row,
                QString(label.c_str()));
}

void MainWindow::addMethod(Method m)
{
    int row = ui->listWidget_Methods->count();
    _methods.push_back(m);

    std::string label = (m.Range==PRIVATE?"- ":(m.Range==PROTECTED?"# ":"+ "));
    label += m.Name + "(";

    if (m.Parameters.empty())
    {
        label += "void";
    }
    else
    {
        std::vector<Parameter>::const_iterator it = m.Parameters.begin();
        label += (it->isConst?"const ":"") + it->Type;
        ++it;
        for (; it != m.Parameters.end() ; ++it)
        {
            label += ", ";
            label += (it->isConst?"const ":"") + it->Type;
        }
    }

    label += ") : ";
    label += m.ReturnedValue;

    ui->listWidget_Methods->insertItem(
                row,
                QString(label.c_str()));
}

void MainWindow::on_pushButton_AddMethod_clicked()
{
    _mv->init();
    _mv->show();
}

void MainWindow::on_lineEdit_ClassName_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || arg1.contains(' '))
    {
        QPalette pal = ui->lineEdit_ClassName->palette();
        pal.setColor(QPalette::Base, QColor(255,50,50));
        ui->lineEdit_ClassName->setPalette(pal);
    }
    else
    {
        QPalette pal = ui->lineEdit_ClassName->palette();
        pal.setColor(QPalette::Base, QColor(255,255,255));
        ui->lineEdit_ClassName->setPalette(pal);
    }
}

void MainWindow::init()
{
    if (_fmw)
    {
        delete _fmw;
    }
    if (_mv)
    {
        delete _mv;
    }
    _fmw = new FieldMemberWindow(this);
    _mv = new MethodView(this);

    ui->lineEdit_ClassName->setText("");
    ui->lineEdit_Path->setText("/tmp/");
    QPalette pal = ui->lineEdit_ClassName->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_ClassName->setPalette(pal);

    ui->checkBox_CopyConstructor->setChecked(false);
    ui->checkBox_DefaultConstructor->setChecked(true);
    ui->checkBox_Destructor->setChecked(true);
    ui->checkBox_OpComparison->setChecked(false);
    ui->checkBox_OpCopy->setChecked(false);
    ui->checkBox_OpRelational->setChecked(false);
    ui->checkBox_VirtualDestructor->setChecked(false);

    ui->listWidget_FieldMember->clear();
    ui->listWidget_Methods->clear();

    _fms.clear();
    _methods.clear();
}

void MainWindow::on_pushButton_Erase_clicked()
{
    init();
}
