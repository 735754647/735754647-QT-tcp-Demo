
#include "server.h"
#include "ui_server.h"



Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->lineEdit_Port->setText("8765");
       ui->pushButton_Send->setEnabled(false);

       server = new QTcpServer();

       //连接信号槽
       connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);
       on_pushButton_Listen_clicked();

               QPixmap pixmap(":/Image/II.png");
                   pixmap = pixmap.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                   ui->label_3->setPixmap(pixmap);

                   QPixmap pixmap2(":/Image/PP.png");
                       pixmap2 = pixmap2.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                       ui->label_4->setPixmap(pixmap2);

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

int Tai=1;


void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
      ui->textEdit_Recv->append("客户端say: " + buffer);
      QString str = QString(buffer);

       if(str=="0") //加台
        {

           QPixmap pixmap(":/Image/UU.png");
           pixmap = pixmap.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
               ui->label_3->setPixmap(pixmap);

           sleep(500);
 QPixmap pixmap2(":/Image/II.png");
           pixmap2 = pixmap2.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放

               ui->label_3->setPixmap(pixmap2);
               Tai++;
              ui->label_5->setText("频道"+QString::number(Tai));
        }
       if(str=="1") //减台
        {
           if(Tai>1)
           {
  QPixmap pixmap3(":/Image/OO.png");

                   pixmap3 = pixmap3.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                   ui->label_4->setPixmap(pixmap3);

               sleep(500);

 QPixmap pixmap4(":/Image/PP.png");
                   pixmap4 = pixmap4.scaled(31, 31, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                   ui->label_4->setPixmap(pixmap4);

                   Tai--;
               ui->label_5->setText("频道"+QString::number(Tai));
           }
        }
       if(str=="2")
       {
           ui->label_5->setText("频道"+QString::number(Tai));
       }

       if(str=="3")
       {
           ui->label_5->setText("关机");
       }
    }
}

void Server::socket_Disconnected()
{
    //发送按键失能
    ui->pushButton_Send->setEnabled(false);
    qDebug() << "Disconnected!";
}


//延时功能
void Server::sleep(unsigned int msec){
//currnentTime 返回当前时间 用当前时间加上我们要延时的时间msec得到一个新的时刻
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    //用while循环不断比对当前时间与我们设定的时间
    while(QTime::currentTime()<reachTime){

        QApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
