#pragma execution_character_set("utf-8")
#include "thread.h"

Thread::Thread(int socketID,QObject *parent) : QThread(parent)
{
    this->socketdescription =socketID;//保存这个标识，因为等一下要用到

}

void Thread::run()
{
    //然后在这里实例化一个指针，因为这里就是新建的线程
    this->socket =new QTcpSocket();

    //这里我们就把刚刚新鲜出炉实例化的socket设置成传入来的标识并且判断是不是成功了
    if(socket->setSocketDescriptor(this->socketdescription)==false)
    {
            qDebug()<<"setsocketDescriptor false";
            return;
    //下面代表没问题了，可以开始逻辑业务部分了
    }

    qDebug() <<QString("[ip:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());

    //这里我们连接信号槽，对方客户发消息的时候我们这里进行处理，又因为是多线程所以用到了最后一个参数
    connect(socket,&QTcpSocket::readyRead,this,&Thread::read,Qt::DirectConnection);
    connect(socket,&QTcpSocket::disconnected,this,&Thread::disconnected,Qt::DirectConnection);//同要也需要连接对方断开的信号

    this->exec();
    //因为涉及线程，这里需要执行这个函数，循环监听
}

void Thread::read()
{
    //连接了信号槽，执行这里的时候代表是可以读取的，所以我们读取
    QByteArray buff =this->socket->readAll();
    //因为这个是演示用，没什么可以做所以我们把他发过来的消息发回去吧

    if(!buff.isEmpty())
           {
                qDebug()<<buff;
           }

    this->socket->write(buff);
}

void Thread::disconnected()
{
    this->socket->disconnectFromHost(); //断开主机
    this->socket->close();//关闭这个类
    this->socket->deleteLater();//释放这个类
    this->exit();//退出当前线程
}

