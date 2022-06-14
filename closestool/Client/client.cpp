#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{

    ui->setupUi(this);

    socket = new QTcpSocket();

    socket->connectToHost("127.0.0.1", 8888);

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



void Client::on_pushButton_clicked()
{
    socket->write("1");
    socket->flush();
}

void Client::on_pushButton_2_clicked()
{
    socket->write("2");
    socket->flush();
}

void Client::on_pushButton_3_clicked()
{
    socket->write("3");
    socket->flush();
}

void Client::on_pushButton_4_clicked()
{
    socket->write("4");
    socket->flush();
}
