#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "websocketclient_control.h"
#include "rest.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WebSocketClient_Control* client = new WebSocketClient_Control();
    client->createWebsocketClient("","","");
    client->setMainPage(this);

}

int MainWindow::led_on = 0;
int MainWindow::kongtiao_on = 0;
int MainWindow::fengming_on = 0;
int MainWindow::model = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_led_btn_clicked(){
    if(led_on==0)
    {
        Rest *open_light = new Rest();
        open_light->command = 600;
        open_light->message = "开灯";
        open_light->success = true;
        open_light->type = 2;
        WebSocketClient_Control::socketCLient->sendTextMessage(open_light->toJson());

    }
    else
    {
        Rest *open_light = new Rest();
        open_light->command = 601;
        open_light->message = "关灯";
        open_light->success = true;
        open_light->type = 2;
        WebSocketClient_Control::socketCLient->sendTextMessage(open_light->toJson());
    }
}

void MainWindow::on_ac_btn_clicked(){
    if(kongtiao_on==0)
    {

        Rest *kongtiao = new Rest();
        kongtiao->command = 700;
        kongtiao->message = "打开空调";
        kongtiao->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(kongtiao->toJson());
        kongtiao_on = 1;

    }
    else
    {

        Rest *kongtiao = new Rest();
        kongtiao->command = 701;
        kongtiao->message = "关闭空调";
        kongtiao->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(kongtiao->toJson());
        kongtiao_on = 0;

    }
}

void MainWindow::on_bee_clicked(){
    if(fengming_on==0)
    {

        Rest *kongtiao = new Rest();
        kongtiao->command = 702;
        kongtiao->message = "打开蜂鸣";
        kongtiao->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(kongtiao->toJson());
    }
    else
    {

        Rest *kongtiao = new Rest();
        kongtiao->command = 703;
        kongtiao->message = "关闭蜂鸣";
        kongtiao->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(kongtiao->toJson());
    }
}

void MainWindow::on_led_mod_btn_clicked(){
    if(led_on==0)
    {
        QMessageBox::warning(this, "逻辑错误", "灯光未被打开");
        QString data1="需要开灯才能调换模式\n";
    }
    if(led_on==1){
    Rest *mod = new Rest();

    if(model%3==0)
    {
        mod->command = 610;
        mod->message = "切换模式一";
        mod->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(mod->toJson());

    }
    if(model%3==1)
    {
        mod->command = 620;
        mod->message = "切换模式二";
        mod->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(mod->toJson());
    }
    if(model%3==2)
    {

        mod->command = 630;
        mod->message = "切换模式三";
        mod->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(mod->toJson());
    }
    }
}

void MainWindow::on_ac_add_btn_clicked(){
    if(kongtiao_on == 1){

        Rest *command = new Rest();
        command->command = 8;
        command->message = "温度增加";
        command->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(command->toJson());
    }else{
        QMessageBox::warning(this, "逻辑错误", "请先打开空调");
    }
}
void MainWindow::on_ac_sub_btn_clicked(){
    if(kongtiao_on == 1){
        Rest *command = new Rest();
        command->command = 2;
        command->message = "温度降低";
        command->success = true;
        WebSocketClient_Control::socketCLient->sendTextMessage(command->toJson());
    }else{
        QMessageBox::warning(this, "逻辑错误", "请先打开空调");
    }
}

void MainWindow::led_opened(){
    ui->led_display->setText("灯已开启");
}

void MainWindow::led_closed(){
    ui->led_display->setText("灯已关闭");
}

void MainWindow::model_change(QString m){
    ui->model_display->setText(m);
}

void MainWindow::ac_changed(QString str){
    ui->ac_display->setText(str);
}

void MainWindow::tp_change(QString tp){
    ui->tp_display->setText(tp+"℃");
}

void MainWindow::bee_changed(QString str){
    ui->bee_display->setText(str);
}




