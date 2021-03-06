#ifndef METHODVIEW_HPP
#define METHODVIEW_HPP

#include <QDialog>
#include "src/model/method.hpp"
#include "ui/paramwindow.hpp"

namespace Ui {
class MethodView;
}

class MethodView : public QDialog
{
    Q_OBJECT

public:
    explicit MethodView(QWidget *parent = 0);
    ~MethodView();

    void init();

    void addParameter(Parameter p);

private slots:
    void on_pushButton_Cancel_clicked();

    void on_lineEdit_Name_textChanged(const QString &arg1);

    void on_lineEdit_ReturnType_textChanged(const QString &arg1);

    void on_checkBox_Abstract_stateChanged(int arg1);

    void on_checkBox_Virtual_stateChanged(int arg1);

    void on_pushButton_OK_clicked();

    void on_pushButton_Add_clicked();

private:
    Ui::MethodView *ui;

    ParamWindow          *  _pw;

    std::vector<Parameter>  _params;

    bool checkFields();
};

#endif // METHODVIEW_HPP
