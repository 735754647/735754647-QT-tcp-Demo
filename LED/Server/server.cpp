#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

       server = new QTcpServer();
       server->listen(QHostAddress::Any, 8765);
       //连接信号槽
       connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);

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

    qDebug() << "A Client connect!";
}

void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
      QString str = QString(buffer);

       if(str=="2")
        {

               QPixmap pixmap(":/Image/KK.png");
               // 510,40 当前label大小
               pixmap = pixmap.scaled(141, 141, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_3->setPixmap(pixmap);
        }

       if(str=="3")
        {

               QPixmap pixmap(":/Image/LL.png");
               // 510,40 当前label大小
               pixmap = pixmap.scaled(141, 141, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_3->setPixmap(pixmap);
        }

       if(str=="0")
       {

           QPixmap pixmap2(":/Image/MM.png");
               // 510,40 当前label大小
               pixmap2 = pixmap2.scaled(141, 141, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_4->setPixmap(pixmap2);


       }

       if(str=="1")
       {

           QPixmap pixmap2(":/Image/PP.png");
               // 510,40 当前label大小
               pixmap2 = pixmap2.scaled(141, 141, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_4->setPixmap(pixmap2);


       }


       if(str=="10")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/1.png"));

       }
       if(str=="20")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/2.png"));

       }
       if(str=="30")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/3.png"));

       }
       if(str=="40")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/4.png"));

       }
       if(str=="50")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/5.png"));

       }
       if(str=="60")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/6.png"));

       }

       if(str=="70")

       {

           ui->label_5->setPixmap(QPixmap(":/Image/7.png"));

       }



    }
}


