#ifndef PARAMWINDOW_HPP
#define PARAMWINDOW_HPP

#include <QDialog>
#include "src/model/parameter.hpp"

namespace Ui {
class ParamWindow;
}

class ParamWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ParamWindow(QWidget *parent = 0);
    ~ParamWindow();

    void init();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

    void on_lineEdit_Name_textChanged(const QString &arg1);

    void on_lineEdit_Type_textChanged(const QString &arg1);

private:
    Ui::ParamWindow *ui;

    bool checkFields();
};

#endif // PARAMWINDOW_HPP
