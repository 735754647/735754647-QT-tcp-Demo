#include "server.h"
#include "ui_server.h"
#include<QTimer>
int number=0;
Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->lineEdit_Port->setText("8765");
       ui->pushButton_Send->setEnabled(false);
   this->_time=new QTimer(this);//初始化定时器事件
       server = new QTcpServer();

       //连接信号槽
       connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);
       on_pushButton_Listen_clicked();

               QPixmap pixmap(":/Image/Cold.png");
                   // 510,40 当前label大小
                   pixmap = pixmap.scaled(161, 161, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                   ui->label_3->setPixmap(pixmap);
                       connect(_time,&QTimer::timeout,[=](){
                           number++;
                           if (number>=ui->lineEdit->text().toInt())
                           {
                              ui->label_4->setText("热水保温中，可关闭烧水");
                           }
                           else
                           {
                            ui->label_4->setText("烧水中..."+QString::number(number));

                           }


                                             });

}

Server::~Server()
{
    server->close();
       server->deleteLater();
    delete ui;
}

//监听
void Server::on_pushButton_Listen_clicked()
{
    if(ui->pushButton_Listen->text() == tr("侦听"))
    {
        ui->textEdit_Recv->append("开启监听成功 " );
        //从输入框获取端口号
        int port = ui->lineEdit_Port->text().toInt();

        //监听指定的端口
        if(!server->listen(QHostAddress::Any, port))
        {
            //若出错，则输出错误信息
            qDebug()<<server->errorString();
            return;
        }
        //修改按键文字
        ui->pushButton_Listen->setText("取消侦听");
        qDebug()<< "Listen succeessfully!";
    }
    else
    {

        socket->abort();
        //取消侦听
        server->close();
        //修改按键文字
        ui->pushButton_Listen->setText("侦听");
        //发送按键失能
        ui->pushButton_Send->setEnabled(false);
    }

}
//发送按钮
void Server::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
    //获取文本框内容并以ASCII码形式发送
    socket->write(ui->textEdit_Send->toPlainText().toUtf8().data());
    socket->flush();
    ui->textEdit_Send->clear();
}

void Server::server_New_Connect()
{
    //获取客户端连接
    socket = server->nextPendingConnection();
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Server::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Server::socket_Disconnected);
    //发送按键使能
    ui->pushButton_Send->setEnabled(true);

    qDebug() << "A Client connect!";
}

void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
      ui->textEdit_Recv->append("客户端say: " + buffer);
      QString str = QString(buffer);

       if(str=="0")
        {

               QPixmap pixmap(":/Image/Hot.png");
               // 510,40 当前label大小
               pixmap = pixmap.scaled(161, 161, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_3->setPixmap(pixmap);
                 _time->start(1000);//启动定时器
        }

       if(str=="1")
        {

               QPixmap pixmap(":/Image/Cold.png");
               // 510,40 当前label大小
               pixmap = pixmap.scaled(161, 161, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_3->setPixmap(pixmap);
               ui->label_4->setText("加热关闭...");
               _time->stop();
               number=0;
        }
    }

}

void Server::socket_Disconnected()
{
    //发送按键失能
    ui->pushButton_Send->setEnabled(false);
    qDebug() << "Disconnected!";
}
