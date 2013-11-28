#ifndef FIELDMEMBERWINDOW_HPP
#define FIELDMEMBERWINDOW_HPP

#include <QDialog>
#include "src/model/fieldmember.hpp"

namespace Ui {
class FieldMemberWindow;
}

class FieldMemberWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FieldMemberWindow(QWidget *parent = 0);
    ~FieldMemberWindow();

    void init();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

    void on_lineEdit_Name_textChanged(const QString &arg1);

    void on_lineEdit_Type_textChanged(const QString &arg1);

    void on_checkBox_Const_stateChanged(int arg1);

    void on_lineEdit_Default_textChanged(const QString &arg1);

private:
    Ui::FieldMemberWindow *ui;

    bool checkFields();
};

#endif // FIELDMEMBERWINDOW_HPP
