#pragma execution_character_set("utf-8")
#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any,8888);
}


void Server::incomingConnection(qintptr handle)
{
    qDebug()<<"连接成功";
    TcpSocket=new QTcpSocket(this);
    TcpSocket->setSocketDescriptor(handle);
    connect(TcpSocket,&QTcpSocket::readyRead,this,&Server::receiveMessage);

}

void Server::receiveMessage()
{

        QByteArray buffer;
        //读取缓冲区数据
        buffer = TcpSocket->readAll();

        if(!buffer.isEmpty())
        {
                qDebug()<<buffer;

                emit buf(buffer.data());
        }

}




