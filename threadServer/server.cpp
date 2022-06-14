#pragma execution_character_set("utf-8")
#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

void Server::stopServer()
{
   this->close();
}

void Server::incomingConnection(qintptr socketDescriptor)
{

    Thread *h =new Thread(socketDescriptor);
    connect(h,&Thread::finished,h,&Thread::deleteLater);//当线程完成后，释放内存
    h->start();//开启这个线程，后面他就会执行我们重写run函数，因为run函数是继承QThread下来的
}

bool Server::startServer(int port)
{
    if(this->isListening())//检查服务是不是本来就运行了
    {
        qDebug()<<"server is running";
    }

    else
    {
         if(this->listen(QHostAddress::Any,port))//listen是我们继Tcpserver,的函数
         {
              return true;
         }
    }

    return false;
}
