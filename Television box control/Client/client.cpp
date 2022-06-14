#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
        ui->setupUi(this);
       socket = new QTcpSocket();

        //连接信号槽
        QObject::connect(socket, &QTcpSocket::readyRead, this, &Client::socket_Read_Data);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &Client::socket_Disconnected);

        ui->pushButton_Send->setEnabled(false);
        ui->lineEdit_IP->setText("127.0.0.1");
        ui->lineEdit_Port->setText("8765");
        on_pushButton_Connect_clicked();

}

Client::~Client()
{
    delete this->socket;
    delete ui;
}

void Client::on_pushButton_Connect_clicked()
{
    if(ui->pushButton_Connect->text() == tr("连接"))
    {
        ui->textEdit_Recv->append("连接成功" );
        QString IP;
        int port;

        //获取IP地址
        IP = ui->lineEdit_IP->text();
        //获取端口号
        port = ui->lineEdit_Port->text().toInt();

        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(300))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";

        //发送按键使能
        ui->pushButton_Send->setEnabled(true);
        //修改按键文字
        ui->pushButton_Connect->setText("断开连接");
    }
    else
    {
        //断开连接
        socket->disconnectFromHost();
        //修改按键文字
        ui->pushButton_Connect->setText("连接");
        ui->pushButton_Send->setEnabled(false);
    }
}

void Client::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
     //获取文本框内容并以ASCII码形式发送
    socket->write(ui->textEdit_Send->toPlainText().toUtf8().data());
    socket->flush();
    ui->textEdit_Send->clear();
}

void Client::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
//        QString str = ui->textEdit_Recv->toPlainText();
//        str+=tr(buffer);
        //刷新显示
        //ui->textEdit_Recv->setText(str);
        ui->textEdit_Recv->append("服务器say: " + buffer);
    }
}
bool key=true;
void Client::socket_Disconnected()
{
    //发送按键失能
    ui->pushButton_Send->setEnabled(false);
    //修改按键文字
    ui->pushButton_Connect->setText("连接");
    qDebug() << "Disconnected!";
}

void Client::on_toolButton_clicked()
{
    if(key)
    {
        socket->write("0");
        socket->flush();
    }

}
void Client::on_toolButton_3_clicked()
{
    if(key)
    {

        socket->write("1");
        socket->flush();
     }
}

void Client::on_toolButton_4_clicked()
{
    if(ui->toolButton_4->text()=="开机")
    {
       socket->write("2");
       socket->flush();
       ui->toolButton_4->setText("关机");
        key=true;
    }
    else
    {
        socket->write("3");
        socket->flush();
        ui->toolButton_4->setText("开机");
        key=false;

    }
}


