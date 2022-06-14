#include "server.h"
#include "ui_server.h"
#include<QTimer>
int number=0;
Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

       this->_time=new QTimer(this);//初始化定时器事件
       server = new QTcpServer();

       //连接信号槽
       connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);
       //监听指定的端口
       if(!server->listen(QHostAddress::Any, 8765))
       {
           //若出错，则输出错误信息
           qDebug()<<server->errorString();
           return;
       }

       qDebug()<< "Listen succeessfully!";


       connect(_time,&QTimer::timeout,[=](){
           number++;
           if (number>=ui->spinBox->text().toInt())
           {
              ui->label_4->setText("已烧开,请关闭烧水");
              ui->progressBar->setValue(number);
           }
           else
           {
            ui->label_4->setText("烧水中");
            ui->progressBar->setValue(number);
           }


       });



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

void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {

      QString str = QString(buffer);

       if(str=="0")
        {
               ui->label_3->setPixmap(QPixmap(":/Image/Hot.png"));
                 _time->start(1000);//启动定时器
                 int l=ui->spinBox->text().toInt();
                 ui->progressBar->setMaximum(l);
        }

       if(str=="1")
        {

               ui->label_3->setPixmap(QPixmap(":/Image/Cold.png"));
               ui->label_4->setText("加热关闭...");
               _time->stop();
               number=0;
               ui->progressBar->setValue(0);
        }
    }

}

void Server::socket_Disconnected()
{

    qDebug() << "Disconnected!";
}
