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

        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost("127.0.0.1", 8765);

        //等待连接成功
        if(!socket->waitForConnected(300))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";


}

Client::~Client()
{
    delete this->socket;
    delete ui;

}



void Client::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
    }
}

void Client::socket_Disconnected()
{
    qDebug() << "Disconnected!";
}




void Client::on_pushButton_clicked()
{
    socket->write("0");
    socket->flush();
}

void Client::on_pushButton_2_clicked()
{

    socket->write("1");
    socket->flush();
}

void Client::on_pushButton_3_clicked()
{
    socket->write("2");
    socket->flush();
}
