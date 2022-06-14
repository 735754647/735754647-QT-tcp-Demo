#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Server *s=new Server(this);
    s->startServer(8899);//随便监听一个端口，默认不填就是8888
}

MainWindow::~MainWindow()
{
    delete ui;
}

