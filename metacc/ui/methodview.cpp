#include "methodview.hpp"
#include "ui_methodview.h"

MethodView::MethodView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodView)
{
    ui->setupUi(this);
}

MethodView::~MethodView()
{
    delete ui;
}

void MethodView::init()
{
    ui->checkBox_Abstract->setChecked(false);
    ui->checkBox_Const->setChecked(false);
    ui->checkBox_Static->setChecked(false);
    ui->checkBox_Virtual->setChecked(false);
    ui->lineEdit_Name->setText("");
    ui->lineEdit_ReturnType->setText("");
    ui->comboBox_Range->setCurrentIndex(0);
    ui->listWidget_Param->clear();
}

void MethodView::on_pushButton_Cancel_clicked()
{
    close();
}
