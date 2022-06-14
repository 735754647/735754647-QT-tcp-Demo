#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
        ui->setupUi(this);
       socket = new QTcpSocket();

       //连接服务器
       socket->connectToHost("127.0.0.1", 8765);

}

Client::~Client()
{
    delete this->socket;
    delete ui;

}


void Client::on_toolButton_clicked()
{
   if(ui->toolButton->text()=="打开光源")
      {
       socket->write("1");
       socket->flush();
       ui->toolButton->setText("关闭光源");
      }
    else
      {
       socket->write("0");
       socket->flush();
       ui->toolButton->setText("打开光源");
     }

}

void Client::on_toolButton_2_clicked()
{
    if(ui->toolButton_2->text()=="打开通风")
    {

        socket->write("3");
        socket->flush();
         ui->toolButton_2->setText("关闭通风");
    }
    else
    {

        socket->write("2");
        socket->flush();
        ui->toolButton_2->setText("打开通风");

    }


}

void Client::on_toolButton_3_clicked()
{

    num+=10;

    QString data=QString::number(num);

    char *dataA=data.toLatin1().data();
    socket->write(dataA);
    socket->flush();
}


void Client::on_toolButton_4_clicked()
{
    num-=10;

    QString data=QString::number(num);

    char *dataB=data.toLatin1().data();
    socket->write(dataB);
    socket->flush();
}

