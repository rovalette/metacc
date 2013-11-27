#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "src/model/classwriter.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Quit_clicked();

    void on_pushButton_OK_clicked();

    void on_pushButton_Browse_clicked();

    void on_checkBox_Destructor_stateChanged(int arg1);

    void on_checkBox_OpRelational_stateChanged(int arg1);

    void on_checkBox_OpComparison_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    ClassWriter     _writer;
    ClassDefinition _definition;

    bool checkFields();
    void createClassDefintionObject();
};

#endif // MAINWINDOW_HPP
