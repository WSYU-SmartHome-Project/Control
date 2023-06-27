#include "connect.h"
#include "ui_connect.h"
#include "websocketclient_control.h"

Connect::Connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);
    main = new MainWindow();

}

Connect::~Connect()
{
    delete ui;
}
void Connect::on_btn_clicked(){
    QString ip = ui->ip->text();
    QString port = ui->port->text();

    WebSocketClient_Control* client = new WebSocketClient_Control();
    client->createWebsocketClient(ip,port,"");
    client->setMainPage(main);

    main->show();
    this->close();
}
