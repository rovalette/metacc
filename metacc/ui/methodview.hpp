#ifndef METHODVIEW_HPP
#define METHODVIEW_HPP

#include <QDialog>

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

private slots:
    void on_pushButton_Cancel_clicked();

private:
    Ui::MethodView *ui;
};

#endif // METHODVIEW_HPP
