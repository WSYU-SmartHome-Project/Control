#ifndef WEBSOCKETCLIENT_CONTROL_H
#define WEBSOCKETCLIENT_CONTROL_H
#include <QtWebSockets/QWebSocket>
#include <QWidget>
#include "mainwindow.h"


class WebSocketClient_Control : public QWidget
{
public:
    WebSocketClient_Control();
    static QWebSocket *socketCLient;     //-<websocket类 静态，
    MainWindow *mainPage = nullptr;
    void setMainPage(MainWindow *page){
        mainPage = page;
    }

public slots:
    void createWebsocketClient(QString ip,QString port,QString api);

private slots:
    void onConnected();                 /*-<socket建立成功后，触发该函数 */
    void onTextReceived(QString msg);   /*-<收到Sev端的数据时，触发该函数 */
    void onDisConnected();
};


#endif // WEBSOCKETCLIENT_CONTROL_H
