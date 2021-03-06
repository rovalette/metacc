#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <vector>
#include "src/model/classwriter.hpp"
#include "ui/fieldmemberwindow.hpp"
#include "ui/methodview.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addFieldMember(FieldMember fm);
    void addMethod(Method m);

private slots:
    void on_pushButton_Quit_clicked();

    void on_pushButton_OK_clicked();

    void on_pushButton_Browse_clicked();

    void on_checkBox_Destructor_stateChanged(int arg1);

    void on_checkBox_OpRelational_stateChanged(int arg1);

    void on_checkBox_OpComparison_stateChanged(int arg1);

    void on_pushButton_Add_clicked();

    void on_pushButton_AddMethod_clicked();

    void on_lineEdit_ClassName_textChanged(const QString &arg1);

    void on_pushButton_Erase_clicked();

private:
    Ui::MainWindow *ui;

    ClassWriter     _writer;
    ClassDefinition _definition;

    FieldMemberWindow       *   _fmw;
    std::vector<FieldMember>    _fms;

    MethodView              *   _mv;
    std::vector<Method>         _methods;

    void init();
    bool checkFields();
    void createClassDefintionObject();

};

#endif // MAINWINDOW_HPP
