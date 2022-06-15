#include "server.h"
#include "ui_server.h"
#include<QTimer>
#include<QDebug>
#include<QMessageBox>
int number=0;
Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

       this->time=new QTimer(this);//初始化定时器事件
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


       //设置初始时间
       timeSet=ui->timeEdit->time();
       ui->lineEdit->setText(timeSet.toString());

       hasSetTime=false;
       btnStartHasClick=false;
       isStop=false;




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

         isStop=false;
             if(btnStartHasClick){ ui->label_4->setText("烘烤中");

             }
             else
             {
                 if(hasSetTime)
                 {
                     timerId=startTimer(1000);//计时开始,每秒调用一次timerEvent函数，并获得这个定时器的Id
                     btnStartHasClick=true;

                     ui->label_3->setPixmap(QPixmap(":/Image/Hot.png"));
                     ui->label_4->setText("烘烤中");
                 }
                 else
                 {
                     QMessageBox::information(this,"提示","先设置时间");
                 }

             }

        }

       if(str=="1")
        {

               ui->label_3->setPixmap(QPixmap(":/Image/Cold.png"));
               ui->label_4->setText("");

               if(btnStartHasClick){
                       killTimer(timerId);//关闭计时器

                       //重置显示屏
                       timeSet.setHMS(0,0,0);
                       ui->lineEdit->setText(timeSet.toString());

                       //重置timeEdit时间
                       QTime time(0,0,0);
                       ui->timeEdit->setTime(time);
                       hasSetTime=false;
                       btnStartHasClick=false;
                   }
                   else
                   {
                       QMessageBox::information(this,"提示","未开始计时");
                   }



        }


       if(str=="2")
        {
           if(btnStartHasClick)
              {
                  isStop=true;
                  ui->label_4->setText("暂停烘烤");

              }
              else
              {
                  QMessageBox::information(this,"提示","未开始计时");
              }


       }

    }

}

void Server::socket_Disconnected()
{

    qDebug() << "Disconnected!";
}


void Server::on_timeEdit_userTimeChanged(const QTime &time)//设置时间
{
    ui->lineEdit->setText(time.toString());
    setSecond=time.hour()*3600+time.minute()*60+time.second();//储存设置的时间
    hasSetTime=true;
    btnStartHasClick=false;
}


void Server::timerEvent(QTimerEvent *)
{

    if(isStop){}
    else
    {

        setSecond-=1;

        //设置显示屏时间
        timeSet.setHMS(setSecond/3600,(setSecond-setSecond/3600*3600)/60,setSecond-setSecond/60*60);
        ui->lineEdit->setText(timeSet.toString());

        if(setSecond==0)
        {

            QMessageBox::information(this,"提示","时间到");
            ui->label_3->setPixmap(QPixmap(":/Image/keep.png"));
            ui->label_4->setText("保温中，请关闭烤箱");
            killTimer(timerId);//时间到,关闭计时器
        }
    }

}

