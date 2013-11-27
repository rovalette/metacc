#ifndef FIELDMEMBERWINDOW_HPP
#define FIELDMEMBERWINDOW_HPP

#include <QDialog>

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

private:
    Ui::FieldMemberWindow *ui;

    bool checkFields();
};

#endif // FIELDMEMBERWINDOW_HPP
