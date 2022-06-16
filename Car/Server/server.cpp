#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

       server = new QTcpServer();

       //连接信号槽
       connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);

       //监听指定的端口
       if(!server->listen(QHostAddress::Any,8765))
       {
           //若出错，则输出错误信息
           qDebug()<<server->errorString();
           return;
       }

       ui->label_3->setGeometry(10,10,51,51);


}

Server::~Server()
{
    server->close();
    server->deleteLater();
    delete ui;
}



void Server::server_New_Connect()
{
    //获取客户端连接
    socket = server->nextPendingConnection();
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Server::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Server::socket_Disconnected);

    qDebug() << "A Client connect!";
}

int X=10;
int Y=10;
int c=10;
void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {

      QString str = QString(buffer);


      if(str=="4")
       {
          c+=10;
          if(c<=0)
          {
              c=10;
          }
       }

      if(str=="5")
       {
          c-=10;
          if(c<=0)
          {
              c=10;
          }
       }

       if(str=="1") //上
        {

           ui->label_3->setGeometry(X,Y=Y+c,51,51);
        }

       if(str=="0") //下
        {
           ui->label_3->setGeometry(X,Y=Y-c,51,51);
        }

       if(str=="2") //左
       {

          ui->label_3->setGeometry(X=X-c,Y,51,51);

       }

       if(str=="3") //右
       {

          ui->label_3->setGeometry(X=X+c,Y,51,51);

       }

    }
}

void Server::socket_Disconnected()
{
    //发送按键失能
    qDebug() << "Disconnected!";
}
