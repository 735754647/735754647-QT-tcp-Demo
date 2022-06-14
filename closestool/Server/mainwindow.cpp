#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server=new Server(this);

    connect(server,&Server::buf,this,&MainWindow::operate);
    ui->label_5->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::operate(QString str)
{

    if(str=="1")
    {
      ui->label_1->setPixmap(QPixmap(":/Image/illumine.png"));
      ui->label_2->setPixmap(QPixmap(":/Image/dry.png"));
      ui->label_3->setPixmap(QPixmap(":/Image/nightstool.png"));
      ui->label_4->show();
      ui->label_5->hide();
      ui->label_6->setText("马桶已自动打开");


    }

    if(str=="2")
    {
       ui->label_1->setPixmap(QPixmap(":/Image/illumine.png"));
       ui->label_2->setPixmap(QPixmap(":/Image/dry.png"));
       ui->label_3->setPixmap(QPixmap(":/Image/wc.png"));
       ui->label_4->hide();
       ui->label_5->hide();       
       ui->label_6->setText("马桶自动按摩打开");

    }


    if(str=="3")
    {
        ui->label_3->setPixmap(QPixmap(":/Image/faeces.png"));
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->setText("自动清洁中");

        sleep(2000);
        ui->label_3->setPixmap(QPixmap(":/Image/water.png"));
        sleep(2000);
        ui->label_3->setPixmap(QPixmap(":/Image/clean.png"));

}

    if(str=="4")
    {

       ui->label_1->setPixmap(QPixmap(":/Image/LED.png"));
       ui->label_2->setPixmap(QPixmap(":/Image/conditioner.png"));
       ui->label_3->setPixmap(QPixmap(":/Image/start.png"));
       ui->label_4->hide();
       ui->label_5->show();
       ui->label_6->setText("清洁完毕");
    }

}

//延时功能
void MainWindow::sleep(unsigned int msec){
//currnentTime 返回当前时间 用当前时间加上我们要延时的时间msec得到一个新的时刻
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    //用while循环不断比对当前时间与我们设定的时间
    while(QTime::currentTime()<reachTime){

        QApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
