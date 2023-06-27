#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int led_on;//0 关灯 1开灯
    static int kongtiao_on;// 0关闭 1开启
    static int fengming_on;
    static int model;
    void led_opened();
    void led_closed();
    void model_change(QString m);
    void ac_changed(QString str);
    void tp_change(QString tp);
    void bee_changed(QString str);


public slots:
    void on_led_btn_clicked();//灯按钮槽函数
    void on_bee_clicked();//蜂鸣器
    void on_ac_btn_clicked();//空调开关
    void on_ac_add_btn_clicked();
    void on_ac_sub_btn_clicked();
    void on_led_mod_btn_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
