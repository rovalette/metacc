#include "methodview.hpp"
#include "ui_methodview.h"
#include "src/views/mainwindow.hpp"
#include <QMessageBox>

MethodView::MethodView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodView)
{
    ui->setupUi(this);

    _pw = new ParamWindow(this);
}

MethodView::~MethodView()
{
    delete ui;
    delete _pw;
}

void MethodView::init()
{
    ui->checkBox_Abstract->setChecked(false);
    ui->checkBox_Const->setChecked(false);
    ui->checkBox_Static->setChecked(false);
    ui->checkBox_Virtual->setChecked(false);
    ui->checkBox_Inline->setChecked(false);
    ui->lineEdit_Name->setText("");
    ui->lineEdit_ReturnType->setText("");
    ui->comboBox_Range->setCurrentIndex(0);
    ui->listWidget_Param->clear();

    _params.clear();

    QPalette pal = ui->lineEdit_Name->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_Name->setPalette(pal);
    pal = ui->lineEdit_ReturnType->palette();
    pal.setColor(QPalette::Base, QColor(255,50,50));
    ui->lineEdit_ReturnType->setPalette(pal);
}

void MethodView::on_pushButton_Cancel_clicked()
{
    close();
}

void MethodView::on_lineEdit_Name_textChanged(const QString &arg1)
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

void MethodView::on_lineEdit_ReturnType_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || arg1.contains(' '))
    {
        QPalette pal = ui->lineEdit_ReturnType->palette();
        pal.setColor(QPalette::Base, QColor(255,50,50));
        ui->lineEdit_ReturnType->setPalette(pal);
    }
    else
    {
        QPalette pal = ui->lineEdit_ReturnType->palette();
        pal.setColor(QPalette::Base, QColor(255,255,255));
        ui->lineEdit_ReturnType->setPalette(pal);
    }
}

void MethodView::on_checkBox_Abstract_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->checkBox_Virtual->setChecked(true);
    }
}

void MethodView::on_checkBox_Virtual_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
    {
        ui->checkBox_Abstract->setChecked(false);
    }
}

bool MethodView::checkFields()
{
    // Name
    if (ui->lineEdit_Name->text().isEmpty() || ui->lineEdit_Name->text().contains(' '))
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le nom de la méthode doit être renseigné. Il ne doit pas contenir d'espace."),
                        0, this);
        msg.exec();
        return false;
    }

    // ReturnType
    if (ui->lineEdit_ReturnType->text().isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("MetaCC"),
                        tr("Le type de retour doit être renseigné."),
                        0, this);
        msg.exec();
        return false;
    }

    return true;
}

void MethodView::on_pushButton_OK_clicked()
{
    if (checkFields())
    {
        Method m;

        m.Name = ui->lineEdit_Name->text().toStdString();
        m.ReturnedValue = ui->lineEdit_ReturnType->text().toStdString();
        m.isAbstract = ui->checkBox_Abstract->isChecked();
        m.isConst = ui->checkBox_Const->isChecked();
        m.isStatic = ui->checkBox_Static->isChecked();
        m.isVirtual = ui->checkBox_Virtual->isChecked();
        m.isInline = ui->checkBox_Inline->isChecked();
        m.Parameters = _params;
        m.Range = (RANGE) ui->comboBox_Range->currentIndex();

        MainWindow * mw = dynamic_cast<MainWindow*>(parent());
        mw->addMethod(m);
        close();
    }
}

void MethodView::on_pushButton_Add_clicked()
{
    _pw->init();
    _pw->show();
}

void MethodView::addParameter(Parameter p)
{
    int row = ui->listWidget_Param->count();
    _params.push_back(p);

    std::string label = (p.isConst?"const ":"");
    label += p.Type + " " + p.Name;

    if (!p.Default.empty())
    {
        label += " = " + p.Default;
    }

    ui->listWidget_Param->insertItem(
                row,
                QString(label.c_str()));
}
