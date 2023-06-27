#include "websocketclient_control.h"
#include "rest.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include "mainwindow.h"

WebSocketClient_Control::WebSocketClient_Control()
{

}
int connecting = 0;
QWebSocket *WebSocketClient_Control::socketCLient = nullptr;

void WebSocketClient_Control::createWebsocketClient(QString ip,QString port,QString api){

    socketCLient = new QWebSocket();
    qDebug()<<"create websocket!";
    connecting = 1;
    connect(socketCLient,&QWebSocket::disconnected,this,&WebSocketClient_Control::onDisConnected);
    connect(socketCLient,&QWebSocket::textMessageReceived,this,&WebSocketClient_Control::onTextReceived);
    connect(socketCLient,&QWebSocket::connected,this,&WebSocketClient_Control::onConnected);
    socketCLient->open(QUrl("ws://"+ip+":"+port+"/control"));

    MainWindow::led_on = 0;
}

void WebSocketClient_Control::onTextReceived(QString msg){
    qDebug() << msg;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    Rest * rest = new Rest();
    rest->message = jsonObject["message"].toString();
    rest->command = jsonObject["command"].toInt();
    rest->success = jsonObject["success"].toBool();

    if(rest->command == 501){
        MainWindow::led_on = 1;
        mainPage->led_opened();
    }

    if(rest->command == 502){
        //关灯返回
        MainWindow::led_on = 0;
        mainPage->led_closed();
    }

    if(rest->command == 511){
        //模式1
        MainWindow::model++;
        mainPage->model_change(rest->message);
    }

    if(rest->command == 512){
        //模式2
        MainWindow::model++;
        mainPage->model_change(rest->message);
    }

    if(rest->command == 513){
        //模式3
        MainWindow::model++;
        mainPage->model_change(rest->message);
    }

    if(rest->command == 521){
        MainWindow::kongtiao_on = 1;
        mainPage->ac_changed("  "+rest->message);
    }

    if(rest->command == 522){
        MainWindow::kongtiao_on = 0;
        mainPage->ac_changed("  "+rest->message);
    }

    if(rest->command == 101 ||rest->command == 102 ){
        //温度增加
        mainPage->tp_change("   "+rest->message);
        qDebug()<<msg;
    }

    if(rest->command == 666){
        MainWindow::fengming_on = 1;
        mainPage->bee_changed("  "+rest->message);
    }
    if(rest->command == 667){
        MainWindow::fengming_on = 0;
        mainPage->bee_changed("  "+rest->message);
    }


}

/**
 * @breaf 判断连接状态
 * @note  当连接成功后，触发该函数
 */
void WebSocketClient_Control::onConnected(){
    connecting = 0;
    Rest* rest = new Rest();
    rest->message = "connected";
    rest->command = 200;
    rest->success = true;
    rest->type = 2;

    QJsonDocument doc(rest->toJsonObject());
    QString jsonStr(doc.toJson(QJsonDocument::Compact));

    qDebug() << "服务器已连接!";
    socketCLient->sendTextMessage(jsonStr);
}

/**
 * @breaf 连接断开
 * @note  当连接断开时，触发该函数
 */
void WebSocketClient_Control::onDisConnected(){
    qDebug()<<"连接断开";
//    QMessageBox::warning(myhomep, "网络错误", "服务器连接失败");

//    if(myhomep->closeType!=1){
//        myhomep->on_pushButton_2_clicked();
//    }
//    myhomep->closeType = 0;

}
