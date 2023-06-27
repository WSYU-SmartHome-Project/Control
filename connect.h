#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Connect;
}

class Connect : public QDialog
{
    Q_OBJECT

public:
    explicit Connect(QWidget *parent = 0);
    ~Connect();

public slots:
    void on_btn_clicked();

private:
    Ui::Connect *ui;
    MainWindow * main;
};

#endif // CONNECT_H
