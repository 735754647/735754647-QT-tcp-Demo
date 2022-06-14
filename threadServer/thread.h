#ifndef THREAD_H
#define THREAD_H

#include <QObject>

//这里就开始重点了多线程
//QThread只有一个run函数是子线程，也就是我们新建的线程
//run（）是QThread,的一个虚函数，所以我们可重写他，执行我们想要执行的代妈
#include <QThread>
#include<QTcpSocket>//这个才是用来通信的，QTcpserver只是用来接收新用户的
#include<QHostAddress>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(int socketID,QObject *parent = nullptr);

signals:

public slots:
    void run();

private:

    int socketdescription;

    QTcpSocket *socket;//创建一个指针

private slots:

    void read();//新建一个槽是用来读取数据的
    void disconnected();//这个是对方断开连接后，用来释放内存的函数

};





#endif // THREAD_H
