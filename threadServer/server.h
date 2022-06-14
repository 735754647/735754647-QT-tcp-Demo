#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "thread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:
    bool startServer(int port=8888);//port=8888默认不传参的话就等千8888
    void stopServer();

   //重写函数，这个函数在有新的用户连接时会调用并传入一个用户的标识符，我们要在线程中新建一个socket并设置为这个标识符

    void incomingConnection(qintptr socketDescriptor);


};

#endif // SERVER_H
